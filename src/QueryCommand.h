// ===== QueryCommand.h =====
#pragma once

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>

// Базовый класс для паттерна Command
// Определяет интерфейс для выполнения SQL-запросов
class QueryCommand : public QObject {
    Q_OBJECT

public:
    // Конструктор
    explicit QueryCommand(QObject* parent = nullptr);
    // Виртуальный деструктор
    virtual ~QueryCommand();

    // Виртуальный метод для выполнения команды
    virtual bool execute() = 0;
    // Виртуальный метод для отмены команды
    virtual void undo() = 0;
    // Получение текста запроса
    QString getQueryText() const;
    // Получение ошибки выполнения
    QString getError() const;

signals:
    // Сигнал успешного выполнения команды
    void executed(bool success);
    // Сигнал ошибки выполнения
    void error(const QString& errorText);

protected:
    QString queryText; // Текст SQL-запроса
    QString errorText; // Текст ошибки
};

// Конкретная реализация команды для выполнения SQL-запросов
class SQLQueryCommand : public QueryCommand {
    Q_OBJECT

public:
    // Конструктор с текстом запроса
    explicit SQLQueryCommand(const QString& query, QObject* parent = nullptr);
    // Деструктор
    ~SQLQueryCommand();

    // Выполнение SQL-запроса
    bool execute() override;
    // Отмена выполнения (в данном случае не реализована)
    void undo() override;

private:
    QSqlQuery query; // Объект для выполнения SQL-запроса
}; 