cmake_minimum_required(VERSION 3.5)

project(Assign4Ell783 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(Assign4Ell783 SHARED
    main.cpp
    common.h
    mysem.cpp
    mysem.h
    msgq.cpp
    msgq.h
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    mainwindow1.cpp
    mainwindow1.h
    mainwindow1.ui
    mainwindow2.cpp
    mainwindow2.h
    mainwindow2.ui
  )
else()
  add_executable(Assign4Ell783
    main.cpp
    common.h
    mysem.cpp
    mysem.h
    msgq.cpp
    msgq.h
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    mainwindow2.cpp
    mainwindow2.h
    mainwindow2.ui
    mainwindow3.cpp
    mainwindow3.h
    mainwindow3.ui
    mainwindow4.cpp
    mainwindow4.h
    mainwindow4.ui
  )
endif()

target_link_libraries(Assign4Ell783 PRIVATE Qt5::Widgets)
