#pragma once

#include "QueryCommand.h"
#include "DatabaseManager.h"

// Конкретная реализация команды для выполнения SQL-запросов
// Используется для инкапсуляции одного SQL-запроса и его выполнения через паттерн Command
class SQLQueryCommand : public QueryCommand {
public:
    // Конструктор принимает текст SQL-запроса
    explicit SQLQueryCommand(const QString& queryText);
    
    // Выполнить SQL-запрос, вернуть true при успехе
    bool execute() override;
    // Отменить выполнение запроса (не реализовано, возвращает false)
    bool undo() override;
    // Получить результат выполнения запроса (QSqlQuery)
    QSqlQuery getResult() const override;
    // Получить ошибку выполнения запроса
    QSqlError getError() const override;
    // Получить текст SQL-запроса
    QString getQueryText() const override;

private:
    QString queryText;   // Текст SQL-запроса
    QSqlQuery query;     // Результат выполнения запроса
    QSqlError lastError; // Последняя ошибка выполнения
}; 