// ===== ThemeManager.h =====
#pragma once

#include <QObject>
#include <QString>
#include <QPalette>
#include <QApplication>

// Класс ThemeManager реализует паттерн Strategy для управления темами оформления
// Позволяет динамически менять внешний вид приложения
class ThemeManager : public QObject {
    Q_OBJECT

public:
    // Конструктор
    explicit ThemeManager(QObject* parent = nullptr);
    // Деструктор
    ~ThemeManager();

    // Установка светлой темы
    void setLightTheme();
    // Установка темной темы
    void setDarkTheme();
    // Получение текущей темы
    QString getCurrentTheme() const;
    // Применение темы к виджету
    void applyTheme(QWidget* widget);

signals:
    // Сигнал, испускаемый при изменении темы
    void themeChanged(const QString& themeName);

private:
    QString currentTheme; // Название текущей темы
    QPalette lightPalette; // Палитра для светлой темы
    QPalette darkPalette; // Палитра для темной темы
}; 