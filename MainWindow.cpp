// ===== MainWindow.cpp =====

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QDebug>
#include <QFileDialog>
#include "Logger.h"

// Конструктор главного окна приложения.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbManager(DatabaseManager::instance()),
    executor(new QueryExecutor(this)),
    history(new QueryHistory(this)),
    modelFactory(new TableModelFactory(this)),
    themeManager(new ThemeManager(this)),
    model(nullptr)
{
    qDebug() << "Initializing MainWindow...";
    ui->setupUi(this);

    // Устанавливаем светлый стиль для таблицы по умолчанию
    QString lightTableStyle = R"(
QTableView {
    background-color: #fff;
    color: #222;
    gridline-color: #ccc;
    selection-background-color: #e0e0e0;
    selection-color: #222;
}
QHeaderView::section {
    background-color: #f0f0f0;
    color: #222;
    border: 1px solid #ccc;
}
QTableCornerButton::section {
    background-color: #f0f0f0;
    border: 1px solid #ccc;
}
)";
    ui->tableView->setStyleSheet(lightTableStyle);

    // Проверяем наличие основных кнопок интерфейса
    if (ui->executeButton) {
        qDebug() << "executeButton found";
    } else {
        qDebug() << "executeButton NOT found!";
    }
    if (ui->themeButton) {
        qDebug() << "themeButton found";
    } else {
        qDebug() << "themeButton NOT found!";
    }

    // Открываем тестовую базу данных (или создаём новую)
    if (!dbManager.openDatabase("test_database.db")) {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных");
        return;
    }

    // Создаём модель данных для таблицы и подключаем её к QTableView
    model = modelFactory->createModel(this);
    ui->tableView->setModel(model);

    // Подключаем сигналы от кнопок к соответствующим слотам
    connect(ui->executeButton, &QPushButton::clicked, this, &MainWindow::onExecuteQuery);
    connect(ui->initTestDbButton, &QPushButton::clicked, this, &MainWindow::onInitTestDatabase);
    connect(ui->openDbButton, &QPushButton::clicked, this, &MainWindow::onOpenDatabase);
    connect(ui->themeButton, &QPushButton::clicked, this, &MainWindow::onChangeTheme);

    // Подключаем сигналы от QueryExecutor для обработки результата выполнения запроса
    connect(executor, &QueryExecutor::queryExecuted, this, &MainWindow::onQueryExecuted);
    connect(executor, &QueryExecutor::errorOccurred, this, &MainWindow::onQueryError);
    
    qDebug() << "MainWindow initialization completed";
}

// Деструктор главного окна
MainWindow::~MainWindow() {
    delete ui;
}

// Слот для выполнения SQL-запроса из текстового поля.
// Добавляет запрос в историю и логирует его выполнение.
void MainWindow::onExecuteQuery() {
    QString query = ui->queryEdit->toPlainText();
    if (executor->executeQuery(query)) {
        history->addQuery(query);
        Logger::instance().log("Выполнен запрос: " + query);
        QVector<QString> hist = history->getHistory();
        qDebug() << "История запросов:";
        for (const QString& q : hist) {
            qDebug() << q;
        }
    } else {
        Logger::instance().log("Ошибка выполнения запроса: " + query);
    }
}

// Слот для смены темы приложения (светлая/тёмная).
// Меняет стиль таблицы и вызывает ThemeManager для смены темы.
void MainWindow::onChangeTheme() {
    auto current = themeManager->getCurrentTheme();
    if (current == ThemeManager::Theme::Light) {
        themeManager->setTheme(ThemeManager::Theme::Dark);
        // Тёмный стиль для QTableView
        QString darkTableStyle = R"(
QTableView {
    background-color: #232323;
    color: #f0f0f0;
    gridline-color: #444;
    selection-background-color: #444;
    selection-color: #fff;
}
QHeaderView::section {
    background-color: #232323;
    color: #f0f0f0;
    border: 1px solid #444;
}
QTableCornerButton::section {
    background-color: #232323;
    border: 1px solid #444;
}
)";
        ui->tableView->setStyleSheet(darkTableStyle);
    } else {
        themeManager->setTheme(ThemeManager::Theme::Light);
        // Светлый стиль для QTableView
        QString lightTableStyle = R"(
QTableView {
    background-color: #fff;
    color: #222;
    gridline-color: #ccc;
    selection-background-color: #e0e0e0;
    selection-color: #222;
}
QHeaderView::section {
    background-color: #f0f0f0;
    color: #222;
    border: 1px solid #ccc;
}
QTableCornerButton::section {
    background-color: #f0f0f0;
    border: 1px solid #ccc;
}
)";
        ui->tableView->setStyleSheet(lightTableStyle);
    }
}

// Слот для инициализации тестовой базы данных из SQL-скрипта.
// Выполняет все команды из файла init_test_db.sql по одной, логирует ошибки и успех.
void MainWindow::onInitTestDatabase() {
    QFile file("init_test_db.sql");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::instance().log("Не удалось открыть файл инициализации БД");
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл инициализации БД");
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString sql = in.readAll();
    file.close();

    QSqlQuery query(dbManager.getDatabase());
    QStringList statements = sql.split(';', Qt::SkipEmptyParts);
    bool allOk = true;
    for (QString statement : statements) {
        statement = statement.trimmed();
        if (statement.isEmpty()) continue;
        if (!query.exec(statement)) {
            allOk = false;
            Logger::instance().log("Ошибка инициализации БД: " + query.lastError().text() + ", SQL: " + statement);
            QMessageBox::critical(this, "Ошибка", "Не удалось инициализировать тестовую БД: " + query.lastError().text() + "\nSQL: " + statement);
            break;
        }
    }
    if (allOk) {
        Logger::instance().log("Тестовая база данных успешно инициализирована");
        if (executor->executeQuery("SELECT * FROM test_table")) {
            QMessageBox::information(this, "Успех", "Тестовая база данных успешно инициализирована");
        }
    }
}

// Слот вызывается после выполнения SQL-запроса.
// Обновляет таблицу результатом последнего запроса.
void MainWindow::onQueryExecuted(bool success) {
    if (success) {
        // Обновляем модель данными из последнего запроса
        QSqlQuery result = executor->getCurrentCommand()->getResult();
        model->setQuery(result);
    }
}

// Слот вызывается при ошибке выполнения SQL-запроса.
// Показывает сообщение об ошибке пользователю.
void MainWindow::onQueryError(const QString& error) {
    QMessageBox::warning(this, "Ошибка", "Ошибка выполнения запроса: " + error);
}

// Слот для открытия новой базы данных через диалог выбора файла.
// После открытия показывает первую таблицу из базы (если есть).
void MainWindow::onOpenDatabase() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть базу данных", "", "SQLite DB (*.db *.sqlite);;Все файлы (*)");
    if (fileName.isEmpty())
        return;

    dbManager.closeDatabase();
    if (!dbManager.openDatabase(fileName)) {
        Logger::instance().log("Не удалось открыть выбранную базу данных: " + fileName);
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть выбранную базу данных!");
        return;
    }

    Logger::instance().log("Открыта база данных: " + fileName);
    // Попробуем показать первую таблицу, если есть
    QSqlQuery query(dbManager.getDatabase());
    if (query.exec("SELECT name FROM sqlite_master WHERE type='table' LIMIT 1;")) {
        if (query.next()) {
            QString tableName = query.value(0).toString();
            executor->executeQuery("SELECT * FROM " + tableName);
            Logger::instance().log("Открыта таблица: " + tableName);
            QMessageBox::information(this, "Успех", "База данных успешно открыта!\nТаблица: " + tableName);
        } else {
            Logger::instance().log("База данных открыта, но таблицы не найдены: " + fileName);
            QMessageBox::information(this, "Успех", "База данных открыта, но таблицы не найдены.");
        }
    }
}