#pragma once

#include <QString>

// Класс для сохранения и восстановления пути к последней открытой базе данных
class LastDbPathManager {
public:
    // Сохранить путь к базе данных в файл
    static void saveLastDbPath(const QString& path);

    // Прочитать путь к базе данных из файла
    static QString loadLastDbPath();

private:
    static QString getFileName(); // Имя файла для хранения пути
}; 