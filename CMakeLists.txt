cmake_minimum_required(VERSION 3.5)

project(gram VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)

set(MSYS2_ROOT "C:/msys64")
set(CURL_LIBRARY_DIRS "${MSYS2_ROOT}/mingw64/lib")
set(CURL_INCLUDE_DIRS "${MSYS2_ROOT}/mingw64/include/curl")
find_package(CURL REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(gram
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        chat.h chat.cpp
        css/backGround.png css/busov.png css/contactFrame.png css/infoFrame.png css/infoFrame1.png css/mesFrame.png css/send.png css/style.css json/json.hpp json/json_fwd.hpp
        mainwindow.ui
    )
else()
    if(ANDROID)
        add_library(gram SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(gram
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(gram PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(gram PRIVATE Qt6::Network)

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(gram PUBLIC ${CURL_LIBRARIES})
    message("CURL is found")
else()
    message(FATAL_ERROR "libcurl not found")
endif()

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.gram)
endif()
set_target_properties(gram PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS gram
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gram)
endif()
