#include "DatabaseManager.h"
#include <QSqlError>
#include <QDebug>

// Получить единственный экземпляр DatabaseManager (Singleton)
DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

// Конструктор DatabaseManager. Создаёт объект базы данных.
DatabaseManager::DatabaseManager() : db(QSqlDatabase::addDatabase("QSQLITE")) {}

// Деструктор DatabaseManager. Закрывает соединение с БД.
DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

// Получить объект базы данных
QSqlDatabase& DatabaseManager::getDatabase() {
    return db;
}

// Открыть соединение с БД (если ещё не открыто)
// path - Путь к файлу базы данных
// return - true, если соединение успешно открыто
bool DatabaseManager::openDatabase(const QString& path) {
    QMutexLocker locker(&mutex);
    if (db.isOpen()) {
        return true;
    }
    db.setDatabaseName(path);
    if (!db.open()) {
        qDebug() << "Ошибка открытия базы данных:" << db.lastError().text();
        return false;
    }
    return true;
}

// Закрыть соединение с базой данных
void DatabaseManager::closeDatabase() {
    QMutexLocker locker(&mutex);
    if (db.isOpen()) {
        db.close();
    }
}
