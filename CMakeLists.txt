cmake_minimum_required(VERSION 3.16)

project(database_viewer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    Sql
    REQUIRED
)


include_directories(${Qt5Core_INCLUDE_DIRS}
                  ${Qt5Gui_INCLUDE_DIRS}
                  ${Qt5Widgets_INCLUDE_DIRS}
                  ${Qt5Sql_INCLUDE_DIRS})


set(UI_FILES
    MainWindow.ui
)

# Явно указываем исходные файлы
set(SOURCES
    main.cpp
    MainWindow.cpp
    DatabaseManager.cpp
    QueryExecutor.cpp
    Logger.cpp
    QueryHistory.cpp
    TableModelFactory.cpp
    ThemeManager.cpp
    SQLQueryCommand.cpp
    LastDbPathManager.cpp
)

# Явно указываем заголовочные файлы
set(HEADERS
    MainWindow.h
    DatabaseManager.h
    QueryExecutor.h
    Logger.h
    QueryHistory.h
    TableModelFactory.h
    ThemeManager.h
    QueryCommand.h
    SQLQueryCommand.h
    LastDbPathManager.h
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Sql
)

# Устанавливаем выходную директорию
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
