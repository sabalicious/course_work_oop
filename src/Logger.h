// ===== Logger.h =====
#pragma once

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

// Класс Logger реализует паттерн Singleton для логирования событий приложения
// Обеспечивает запись логов в файл с временными метками
class Logger : public QObject {
    Q_OBJECT

public:
    // Получение единственного экземпляра логгера (Singleton)
    static Logger& getInstance();

    // Запрещаем копирование и присваивание для Singleton
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Инициализация логгера с указанием файла для записи
    bool init(const QString& filename);
    // Запись информационного сообщения в лог
    void info(const QString& message);
    // Запись сообщения об ошибке в лог
    void error(const QString& message);
    // Запись отладочного сообщения в лог
    void debug(const QString& message);

private:
    // Приватный конструктор (часть паттерна Singleton)
    Logger(QObject* parent = nullptr);
    // Приватный деструктор
    ~Logger();

    // Вспомогательный метод для записи сообщения в лог
    void writeLog(const QString& level, const QString& message);

    QFile logFile; // Файл для записи логов
    QTextStream logStream; // Поток для записи в файл
    static Logger* instance; // Указатель на единственный экземпляр
}; 