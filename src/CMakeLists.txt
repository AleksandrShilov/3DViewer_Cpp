cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 0.1 LANGUAGES CXX C)

include_directories("${PROJECT_SOURCE_DIR}/qtgifimage/src/gifimage")
include_directories("${PROJECT_SOURCE_DIR}/qtgifimage/src/3rdParty/giflib")
include_directories("${PROJECT_SOURCE_DIR}/view")

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(example test.cc model/model.cc)
target_link_libraries(example gtest_main)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 QtCore COMPONENTS Widgets REQUIRED OpenGL GLUT)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED OpenGL)

set(PROJECT_SOURCES
        main.cc
        view/mainwindow.cc
        view/mainwindow.h
        view/mainwindow.ui
        view/widget.h
        view/widget.cc
        model/model.h
        model/model.cc
        controller/controller.cc
        controller/controller.h
        view/strategy.h
        view/command.h
        qtgifimage/src/gifimage/qgifglobal.h
        qtgifimage/src/gifimage/qgifimage.h
        qtgifimage/src/gifimage/qgifimage_p.h
        qtgifimage/src/gifimage/qgifimage.cpp
        qtgifimage/src/3rdParty/giflib/dgif_lib.c
        qtgifimage/src/3rdParty/giflib/egif_lib.c
        qtgifimage/src/3rdParty/giflib/gifalloc.c
        qtgifimage/src/3rdParty/giflib/gif_err.c
        qtgifimage/src/3rdParty/giflib/gif_font.c
        qtgifimage/src/3rdParty/giflib/gif_hash.c
        qtgifimage/src/3rdParty/giflib/gif_hash.c
        qtgifimage/src/3rdParty/giflib/quantize.c
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL glut GL GLU gtest_main)

set_target_properties(3DViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer)
endif()
