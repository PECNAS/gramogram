cmake_minimum_required(VERSION 3.5)

project(messanger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(messanger
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        chat.h chat.cpp
    )

else()
    if(ANDROID)
        add_library(messanger SHARED
            ${PROJECT_SOURCES}
        )
        add_executable(messanger
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set(CURL_LIBRARY "C:/vcpkg/installed/x64-windows/bin/libcul.dll ")
set(CURL_INCLUDE_DIRS "C:/vcpkg/installed/x64-windows/include")
set(CURL_LIBRARIES "C:/vcpkg/installed/x64-windows/lib")
find_package(CURL REQUIRED)
#if(CURL_FOUND)
#    include_directories(${CURL_INCLUDE_DIRS})
#    target_link_libraries(messanger ${CURL_LIBRARIES})
#else()
#    message(FATAL_ERROR "Не удалось найти библиотеку CURL")
#endif()

target_include_directories(messanger PUBLIC ${CURL_INCLUDE_DIRS})
target_link_libraries(messanger ${CURL_LIBRARIES})

target_link_libraries(messanger PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(messanger PRIVATE Qt${QT_VERSION_MAJOR}::Network)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.messanger)
endif()
set_target_properties(messanger PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS messanger
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(messanger)
endif()

