-- Создаем тестовую таблицу
CREATE TABLE IF NOT EXISTS test_table (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    age INTEGER,
    email TEXT
);

-- Добавляем тестовые данные
INSERT INTO test_table (name, age, email) VALUES
    ('Иван Иванов', 25, 'ivan@example.com'),
    ('Петр Петров', 30, 'petr@example.com'),
    ('Анна Сидорова', 28, 'anna@example.com'),
    ('Мария Кузнецова', 35, 'maria@example.com'),
    ('Алексей Смирнов', 22, 'alex@example.com'); 