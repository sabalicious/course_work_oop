#pragma once

#include <QObject>
#include <QSqlQueryModel>

// Класс TableModelFactory реализует паттерн Factory Method для создания моделей таблиц.
class TableModelFactory : public QObject {
    Q_OBJECT
public:
    // Конструктор TableModelFactory
    // parent - Родительский объект (для Qt)
    explicit TableModelFactory(QObject* parent = nullptr);

    // Фабричный метод для создания модели таблицы
    // parent - Родительский объект для модели
    // return - Указатель на созданную модель QSqlQueryModel
    QSqlQueryModel* createModel(QObject* parent = nullptr);
};
