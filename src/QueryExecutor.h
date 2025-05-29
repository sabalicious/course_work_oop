// ===== QueryExecutor.h =====
#pragma once

#include <QObject>
#include <QString>
#include "QueryCommand.h"

// Класс QueryExecutor отвечает за выполнение SQL-запросов
// Использует паттерн Command для инкапсуляции запросов
class QueryExecutor : public QObject {
    Q_OBJECT

public:
    // Конструктор
    explicit QueryExecutor(QObject* parent = nullptr);
    // Деструктор
    ~QueryExecutor();

    // Выполнение SQL-запроса
    void executeQuery(const QString& query);
    // Отмена последнего запроса
    void undoLastQuery();
    // Проверка, есть ли запросы для отмены
    bool canUndo() const;

signals:
    // Сигнал успешного выполнения запроса
    void queryExecuted(bool success);
    // Сигнал ошибки выполнения запроса
    void queryError(const QString& error);

private:
    QueryCommand* currentCommand; // Текущая выполняемая команда
}; 