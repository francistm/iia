set(EXEC_SOURCES WIN32 "main.cpp" "main_window.cpp" "data_table.cpp")

set(CMAKE_AUTOMOC ON)

add_executable(iia ${EXEC_SOURCES})

find_package(Qt5 REQUIRED COMPONENTS Widgets Gui)
target_link_libraries(iia PRIVATE Qt5::Widgets Qt5::Gui)