#pragma once

#include <QString>
#include <QSqlQuery>
#include <QSqlError>

// Абстрактный класс команды для выполнения SQL-запросов
// Реализует паттерн Command
class QueryCommand {
public:
    virtual ~QueryCommand() = default;
    
    // Выполнить команду
    virtual bool execute() = 0;
    
    // Отменить выполнение команды
    virtual bool undo() = 0;
    
    // Получить результат выполнения
    virtual QSqlQuery getResult() const = 0;
    
    // Получить ошибку выполнения
    virtual QSqlError getError() const = 0;
    
    // Получить текст запроса
    virtual QString getQueryText() const = 0;
}; 