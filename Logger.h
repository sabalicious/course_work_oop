#pragma once

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>

// Класс Logger реализует Singleton для логирования событий и ошибок приложения.
// Позволяет централизованно записывать сообщения в лог-файл.
class Logger : public QObject {
    Q_OBJECT
public:
    // Получить единственный экземпляр Logger (Singleton)
    // return - Ссылка на экземпляр Logger
    static Logger& instance();

    // Записать сообщение в лог-файл
    // message - Текст сообщения
    void log(const QString& message);

private:
    Logger();  // Конструктор закрыт (Singleton)
    ~Logger();

    Logger(const Logger&) = delete;            // Запрет копирования
    Logger& operator=(const Logger&) = delete; // Запрет присваивания

    QFile logFile;         // Файл для записи лога
    QTextStream logStream; // Поток для записи в файл
    QMutex mutex;          // Мьютекс для потокобезопасности
};
