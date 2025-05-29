#include "LastDbPathManager.h"
#include <QFile>
#include <QTextStream>

// Получить имя файла для хранения пути
QString LastDbPathManager::getFileName() {
    return "last_db_path.txt";
}

// Сохранить путь к базе данных в файл
void LastDbPathManager::saveLastDbPath(const QString& path) {
    QFile file(getFileName());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << path; // Записываем путь в файл
    }
}

// Прочитать путь к базе данных из файла
QString LastDbPathManager::loadLastDbPath() {
    QFile file(getFileName());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        return in.readLine(); // Считываем путь из файла
    }
    return QString(); // Если файл не найден, возвращаем пустую строку
} 