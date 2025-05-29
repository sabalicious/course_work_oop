#include "QueryExecutor.h"
#include "SQLQueryCommand.h"

// Конструктор QueryExecutor
QueryExecutor::QueryExecutor(QObject *parent)
    : QObject(parent)
{
}

// Выполнение SQL-запроса
// queryText - Текст SQL-запроса для выполнения
// return - true, если запрос выполнен успешно
bool QueryExecutor::executeQuery(const QString& queryText)
{
    // Создаем новую команду для выполнения запроса
    currentCommand = std::make_unique<SQLQueryCommand>(queryText);
    
    // Выполняем команду и обрабатываем результат
    if (currentCommand->execute()) {
        emit queryExecuted(true);
        return true;
    } else {
        // Сохраняем и отправляем информацию об ошибке
        lastError = currentCommand->getError().text();
        emit errorOccurred(lastError);
        emit queryExecuted(false);
        return false;
    }
}

// Получение текста последней ошибки
QString QueryExecutor::getLastError() const
{
    return lastError;
}
