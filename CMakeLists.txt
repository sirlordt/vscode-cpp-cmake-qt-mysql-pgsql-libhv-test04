cmake_minimum_required(VERSION 3.14)

project(test03) # LANGUAGES CXX

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARIES_FOLDER_PREFIX "/home/dsistemas/Desktop/CPP/libraries/") #<== THIS PATH MUST BE EXISTS

message("LIBRARIES_FOLDER_PREFIX => " status ${LIBRARIES_FOLDER_PREFIX})

set(CMAKE_GENERATOR "Ninja")
set(CMAKE_PREFIX_PATH ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_1)
set(QT_QMAKE_EXECUTABLE ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_1/bin/qmake)

add_library(HV_LIBRARY STATIC IMPORTED GLOBAL)
set_target_properties(HV_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}libhv/lib/libhv_static.a)
target_include_directories(HV_LIBRARY INTERFACE ${LIBRARIES_FOLDER_PREFIX}libhv/include)

set(LIBRT "/usr/lib/x86_64-linux-gnu/librt.a") #<-- Add this

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

#set(MY_VAR "/usr/lib/x86_64-linux-gnu/librt.a" CACHE FILEPATH "docs..." FORCE)

#message( status ${LIBRT} )
#message( status ${HV_LIBRARY} )

add_executable(test03
  main.cpp
  test01.h
  test01.cpp
)

target_link_options(test03 PRIVATE --static -static-libgcc -static-libstdc++) #Force full static linked binary

target_link_libraries(test03 PRIVATE Qt${QT_VERSION_MAJOR}::Core HV_LIBRARY ssl crypto)

#target_link_libraries(test03 Qt${QT_VERSION_MAJOR}::Core)
