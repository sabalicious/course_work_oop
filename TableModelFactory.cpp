#include "TableModelFactory.h"

// Конструктор TableModelFactory
// parent - Родительский объект (для Qt)
TableModelFactory::TableModelFactory(QObject* parent) : QObject(parent) {}

// Фабричный метод для создания модели таблицы
// parent - Родительский объект для модели
// return - Указатель на созданную модель QSqlQueryModel
QSqlQueryModel* TableModelFactory::createModel(QObject* parent) {
    return new QSqlQueryModel(parent);
}
