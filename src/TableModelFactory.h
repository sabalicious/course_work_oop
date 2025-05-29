// ===== TableModelFactory.h =====
#pragma once

#include <QObject>
#include <QSqlQueryModel>
#include <QTableView>

// Класс TableModelFactory реализует паттерн Factory Method
// Отвечает за создание различных типов моделей для отображения данных в таблицах
class TableModelFactory : public QObject {
    Q_OBJECT

public:
    // Конструктор
    explicit TableModelFactory(QObject* parent = nullptr);
    // Деструктор
    ~TableModelFactory();

    // Создание модели для отображения результатов SQL-запроса
    QSqlQueryModel* createQueryModel();
    // Создание модели для отображения структуры таблицы
    QSqlQueryModel* createTableModel(const QString& tableName);
    // Создание модели для отображения списка таблиц
    QSqlQueryModel* createTablesListModel();

private:
    // Вспомогательный метод для настройки модели
    void setupModel(QSqlQueryModel* model);
}; 