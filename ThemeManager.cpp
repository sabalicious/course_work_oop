#include "ThemeManager.h"
#include <QApplication>

// Конструктор ThemeManager с установкой светлой темы по умолчанию
ThemeManager::ThemeManager(QObject* parent) : QObject(parent), currentTheme(Theme::Light) {
    applyTheme(currentTheme);
}

// Установка новой темы оформления
// theme - Новая тема для установки
void ThemeManager::setTheme(Theme theme) {
    if (theme != currentTheme) {
        currentTheme = theme;
        applyTheme(theme);
    }
}

// Получение текущей темы оформления
ThemeManager::Theme ThemeManager::getCurrentTheme() const {
    return currentTheme;
}

// Применение темы к приложению
// theme - Тема для применения
void ThemeManager::applyTheme(Theme theme) {
    QString styleSheet;
    if (theme == Theme::Dark) {
        // Стили для темной темы
        styleSheet = R"(
            QWidget {
                background-color: #2b2b2b;
                color: #ffffff;
            }

            QLineEdit, QTextEdit, QTableView {
                background-color: #3c3f41;
                color: #ffffff;
                border: 1px solid #555;
            }

            QPushButton {
                background-color: #555;
                border: 1px solid #888;
                padding: 4px;
            }

            QPushButton:hover {
                background-color: #666;
            }
        )";
    } else {
        // Стандартная светлая тема Qt
        styleSheet = "";
    }

    qApp->setStyleSheet(styleSheet);
}
