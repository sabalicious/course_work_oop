#include "Logger.h"
#include <QDateTime>
#include <QDebug>

// Получить единственный экземпляр Logger (Singleton)
Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

// Конструктор Logger. Открывает файл лога для записи.
// Если файл не удаётся открыть, выводит предупреждение в консоль.
Logger::Logger()
    : logFile("app.log"), logStream(&logFile) {
    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл лога";
    }
}

// Деструктор Logger
Logger::~Logger() {
    if (logFile.isOpen()) {
        logFile.close();
    }
}

// Записать сообщение в лог-файл с временной меткой.
// message - Текст сообщения
void Logger::log(const QString& message) {
    QMutexLocker locker(&mutex);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    logStream << timestamp << " - " << message << "\n";
    logStream.flush();
}
