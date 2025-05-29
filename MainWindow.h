// ===== MainWindow.h =====
#pragma once

#include <QMainWindow>
#include <QSqlQueryModel>
#include "DatabaseManager.h"
#include "QueryExecutor.h"
#include "Logger.h"
#include "QueryHistory.h"
#include "TableModelFactory.h"
#include "ThemeManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Главное окно программы
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Конструктор MainWindow
    // parent — родительский виджет (по умолчанию nullptr)
    MainWindow(QWidget *parent = nullptr);
    // Деструктор MainWindow
    ~MainWindow();

private slots:
    // Выполнить SQL-запрос из текстового поля
    void onExecuteQuery();
    // Сменить тему приложения (светлая/тёмная)
    void onChangeTheme();
    // Инициализировать тестовую базу данных из SQL-скрипта
    void onInitTestDatabase();
    // Открыть новую базу данных через диалог выбора файла
    void onOpenDatabase();
    // Обработать успешное выполнение запроса (success — true, если запрос выполнен успешно)
    void onQueryExecuted(bool success);
    // Обработать ошибку выполнения запроса (error — текст ошибки)
    void onQueryError(const QString& error);

private:
    Ui::MainWindow *ui; // Указатель на UI, сгенерированный Qt Designer

    DatabaseManager& dbManager;      // Менеджер базы данных (Singleton)
    QueryExecutor* executor;         // Исполнитель SQL-запросов
    QueryHistory* history;           // История выполненных запросов
    TableModelFactory* modelFactory; // Фабрика моделей таблиц
    ThemeManager* themeManager;      // Менеджер тем оформления
    QSqlQueryModel* model;           // Модель данных для отображения в таблице
};