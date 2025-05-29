#include "QueryHistory.h"

// Конструктор QueryHistory
// parent - Родительский объект (для Qt)
QueryHistory::QueryHistory(QObject* parent) : QObject(parent) {}

// Добавить запрос в историю
// query - Текст SQL-запроса
void QueryHistory::addQuery(const QString& query) {
    if (!query.isEmpty()) {
        history.append(query);
    }
}

// Получить все запросы из истории
// return - Вектор строк с запросами
QVector<QString> QueryHistory::getHistory() const {
    return history;
}
