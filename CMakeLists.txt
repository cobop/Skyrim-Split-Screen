cmake_minimum_required(VERSION 3.16)
project(SkyrimSplitScreen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

set(CMAKE_AUTOMOC ON)

set(SRC_FILES
    src/main.cpp
    src/Launcher.cpp
    src/Config.cpp
    src/GameInstance.cpp
    src/WindowManager.cpp
    src/UI/MainWindow.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)
