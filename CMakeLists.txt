cmake_minimum_required(VERSION 3.16)

project(TowerDefense LANGUAGES CXX)

# ===== Qt 自动处理 =====
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ===== C++ 标准 =====
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===== 查找 Qt =====
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ===== 源文件 =====
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/gamepage.cpp
    src/mainmenupage.cpp
    src/gamemanager.cpp
    src/enemy.cpp
    src/gameentity.cpp
    src/tower.cpp
    src/bullet.cpp
    src/resourcemanager.cpp
    src/placementvalidator.cpp
)

# ===== 头文件 =====
set(HEADERS
    include/mainwindow.h
    include/gamepage.h
    include/mainmenupage.h
    include/gamemanager.h
    include/enemy.h
    include/gameentity.h
    include/tower.h
    include/bullet.h
    include/resourcemanager.h
    include/placementvalidator.h
    include/config.h
)

# ===== UI 文件 =====
set(UIS
    ui/mainwindow.ui
)

# ===== 资源文件 =====
set(RESOURCES
    res/res.qrc
)

# ===== 可执行文件 =====
add_executable(TowerDefense
    ${SOURCES}
    ${HEADERS}
    ${UIS}
    ${RESOURCES}
)

# ===== include 目录 =====
target_include_directories(TowerDefense PRIVATE
    include
)

# ===== 链接 Qt =====
target_link_libraries(TowerDefense PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

# ===== Windows 设置 =====
if(WIN32)
    set_target_properties(TowerDefense PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
