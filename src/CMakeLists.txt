set(EXEC_SOURCES "main.cpp" "main_window.cpp" "data_table.cpp" "json_converter.cpp")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if (WIN32)
    add_executable(iia WIN32 ${EXEC_SOURCES})
elseif (APPLE)
    add_executable(iia MACOSX_BUNDLE ${EXEC_SOURCES})
    set_target_properties(iia PROPERTIES MACOSX_BUNDLE YES)
endif()

find_package(json-c CONFIG REQUIRED)
target_link_libraries(iia PRIVATE json-c::json-c)

find_package(Qt5 REQUIRED COMPONENTS Widgets Gui)
target_link_libraries(iia PRIVATE Qt5::Widgets Qt5::Gui)