set(EXEC_SOURCES "main.cpp" "main_window.cpp" "data_table.cpp" "json_converter.cpp")

set(CMAKE_AUTOMOC ON)

if (WIN32)
    add_executable(iia WIN32 ${EXEC_SOURCES})
elseif (APPLE)
    add_executable(iia ${EXEC_SOURCES})
endif()

find_package(json-c CONFIG REQUIRED)
target_link_libraries(iia PRIVATE json-c::json-c)

find_package(Qt5 REQUIRED COMPONENTS Widgets Gui)
target_link_libraries(iia PRIVATE Qt5::Widgets Qt5::Gui)