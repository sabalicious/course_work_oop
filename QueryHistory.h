#pragma once

#include <QObject>
#include <QString>
#include <QVector>

// Класс QueryHistory хранит историю SQL-запросов пользователя.
// Позволяет добавлять новые запросы и получать список всех ранее выполненных запросов.
class QueryHistory : public QObject {
    Q_OBJECT
public:
    // Конструктор QueryHistory
    // parent - Родительский объект (для Qt)
    explicit QueryHistory(QObject* parent = nullptr);

    // Добавить запрос в историю
    // query - Текст SQL-запроса
    void addQuery(const QString& query);

    // Получить все запросы из истории
    // return - Вектор строк с запросами
    QVector<QString> getHistory() const;

private:
    QVector<QString> history; // Вектор для хранения истории запросов
};
