#include "SQLQueryCommand.h"

// Конструктор SQLQueryCommand
// queryText - Текст SQL-запроса для выполнения
SQLQueryCommand::SQLQueryCommand(const QString& queryText)
    : queryText(queryText)
{
}

// Выполнение SQL-запроса
// return - true, если запрос выполнен успешно
bool SQLQueryCommand::execute()
{
    // Получаем подключение к БД и создаем запрос
    query = QSqlQuery(DatabaseManager::instance().getDatabase());
    bool success = query.exec(queryText);
    if (!success) {
        // Сохраняем информацию об ошибке
        lastError = query.lastError();
    }
    return success;
}

// Отмена выполнения запроса
// return - false, так как отмена не реализована
bool SQLQueryCommand::undo()
{
    // В данном случае отмена операции не реализована,
    // так как SQL-запросы обычно необратимы
    return false;
}

// Получение результата выполнения запроса
QSqlQuery SQLQueryCommand::getResult() const
{
    return query;
}

// Получение информации об ошибке выполнения
QSqlError SQLQueryCommand::getError() const
{
    return lastError;
}

// Получение текста запроса
QString SQLQueryCommand::getQueryText() const
{
    return queryText;
} 