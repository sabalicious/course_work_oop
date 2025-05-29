#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QMutex>

// Класс DatabaseManager реализует Singleton для работы с базой данных SQLite.
// Гарантирует единственное подключение к базе данных на протяжении всей работы программы.
// Используется для открытия, закрытия и получения доступа к базе данных.
class DatabaseManager : public QObject {
    Q_OBJECT
public:
    // Получить единственный экземпляр DatabaseManager (Singleton)
    // return - Ссылка на экземпляр DatabaseManager
    static DatabaseManager& instance();

    // Получить объект базы данных
    // return - Ссылка на QSqlDatabase
    QSqlDatabase& getDatabase();

    // Открыть соединение с БД (если ещё не открыто)
    // path - Путь к файлу базы данных (по умолчанию "data.db")
    // return - true, если соединение успешно открыто
    bool openDatabase(const QString& path = "data.db");

    // Закрыть соединение с базой данных
    void closeDatabase();

private:
    DatabaseManager(); // Конструктор закрыт (Singleton)
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager&) = delete;            // Запрет копирования
    DatabaseManager& operator=(const DatabaseManager&) = delete; // Запрет присваивания

    QSqlDatabase db;   // Объект базы данных
    QMutex mutex;      // Мьютекс для потокобезопасности
};
