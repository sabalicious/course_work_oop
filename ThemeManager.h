#pragma once

#include <QString>
#include <QObject>

// Класс ThemeManager управляет текущей темой интерфейса.
// Использует паттерн Strategy для подмены стиля приложения (светлая/тёмная тема).
class ThemeManager : public QObject {
    Q_OBJECT
public:
    // Перечисление доступных тем
    enum class Theme {
        Light, // Светлая тема
        Dark   // Тёмная тема
    };

    // Конструктор ThemeManager
    // parent - Родительский объект (для Qt)
    explicit ThemeManager(QObject* parent = nullptr);

    // Установить тему интерфейса
    // theme - Новая тема (Light или Dark)
    void setTheme(Theme theme);

    // Получить текущую тему
    Theme getCurrentTheme() const;

private:
    Theme currentTheme; // Текущая тема
    // Применить стили к приложению в зависимости от выбранной темы
    void applyTheme(Theme theme);
};
