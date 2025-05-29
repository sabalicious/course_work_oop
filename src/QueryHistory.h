// ===== QueryHistory.h =====
#pragma once

#include <QObject>
#include <QStringList>
#include <QDateTime>

// Класс QueryHistory отвечает за хранение и управление историей SQL-запросов
// Позволяет сохранять, получать и очищать историю выполненных запросов
class QueryHistory : public QObject {
    Q_OBJECT

public:
    // Конструктор с указанием максимального размера истории
    explicit QueryHistory(int maxSize = 100, QObject* parent = nullptr);
    // Деструктор
    ~QueryHistory();

    // Добавление нового запроса в историю
    void addQuery(const QString& query);
    // Получение списка всех запросов из истории
    QStringList getQueries() const;
    // Очистка всей истории запросов
    void clear();
    // Получение размера истории
    int size() const;
    // Проверка, пуста ли история
    bool isEmpty() const;

signals:
    // Сигнал, испускаемый при изменении истории
    void historyChanged();

private:
    QStringList queries; // Список сохраненных запросов
    int maxHistorySize; // Максимальный размер истории
}; 