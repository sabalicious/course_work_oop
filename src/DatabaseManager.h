// ===== DatabaseManager.h =====
#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QString>

// Класс DatabaseManager реализует паттерн Singleton для управления подключением к базе данных
// Singleton гарантирует, что в приложении существует только один экземпляр менеджера БД
class DatabaseManager : public QObject {
    Q_OBJECT

public:
    // Получение единственного экземпляра класса (Singleton)
    static DatabaseManager& getInstance();

    // Запрещаем копирование и присваивание для Singleton
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // Открытие базы данных по указанному пути
    bool openDatabase(const QString& path);
    // Закрытие текущего подключения к базе данных
    void closeDatabase();
    // Проверка, открыта ли база данных
    bool isOpen() const;
    // Получение текущего подключения к базе данных
    QSqlDatabase getDatabase() const;

signals:
    // Сигнал, испускаемый при изменении состояния подключения
    void connectionChanged(bool connected);

private:
    // Приватный конструктор (часть паттерна Singleton)
    DatabaseManager(QObject* parent = nullptr);
    // Приватный деструктор
    ~DatabaseManager();

    QSqlDatabase db; // Объект подключения к базе данных
    static DatabaseManager* instance; // Указатель на единственный экземпляр
}; 