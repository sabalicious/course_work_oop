#pragma once

#include <QObject>
#include <QString>
#include <memory>
#include "QueryCommand.h"

// Класс QueryExecutor реализует выполнение SQL-запросов.
class QueryExecutor : public QObject {
    Q_OBJECT
public:
    // Конструктор QueryExecutor
    // parent - Родительский объект (для Qt)
    explicit QueryExecutor(QObject *parent = nullptr);
    
    // Выполнить SQL-запрос, возвращает true при успехе
    // queryText - Текст SQL-запроса
    bool executeQuery(const QString& queryText);
    
    // Получить последнюю ошибку выполнения запроса
    QString getLastError() const;

    // Получить текущую команду (QueryCommand)
    QueryCommand* getCurrentCommand() const { return currentCommand.get(); }
    
signals:
    // Сигнал об успешном выполнении запроса
    void queryExecuted(bool success);
    // Сигнал о возникновении ошибки
    void errorOccurred(const QString& error);
    
private:
    std::unique_ptr<QueryCommand> currentCommand; // Текущая команда для выполнения запроса
    QString lastError; // Последняя ошибка выполнения
};
