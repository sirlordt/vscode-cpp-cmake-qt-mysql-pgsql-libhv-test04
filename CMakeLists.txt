cmake_minimum_required(VERSION 3.14)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(test04) # LANGUAGES CXX

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a") # <--- Change the preference to .a and not .so

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARIES_FOLDER_PREFIX "/home/dsistemas/Desktop/CPP/libraries/") #<== THIS PATH MUST BE EXISTS

#message("LIBRARIES_FOLDER_PREFIX => " status ${LIBRARIES_FOLDER_PREFIX})

#sudo apt-get install mc \
#                     htop \
#                     build-essential \
#                     cmake \
#                     git \
#                     valgrind \
#                     redis-server \
#                     mysql-client \
#                     mysql-server \
#                     mongodb-server \
#                     binutils-gold \
#                     icu-devtools \
#                     freeglut3 \
#                     libtool \
#                     libbrotli1 \
#                     mesa-common-dev \
#                     freeglut3-dev \
#                     unixodbc-dev \
#                     uuid-dev \
#                     zlib1g-dev \
#                     libglew-dev \
#                     libglew1.5-dev \
#                     libglm-dev \
#                     libegl-dev \
#                     libicu-dev \
#                     libpng-dev \
#                     libjpeg-dev \
#                     libssl-dev \
#                     libopengl-dev \
#                     libmysqlclient-dev \
#                     libltdl-dev \
#                     libhiredis-dev \
#                     libfreetype-dev \
#                     libcppdb-dev \
#                     libpq-dev \  #<-- To much dependencies like ldap in ubuntu 20.04. The libpgcommon.a, libpgport.a are missing. 
#                     libsqlite3-dev \
#                     libbrotli-dev \
#                     libcurl4-openssl-dev \  
#                     libmongoc-dev \
#                     clang \  

# install mysql-workbench 
# install google-chrome
# install vscode
# Update version of cmake https://apt.kitware.com/ (to compile QT require most updated version of default cmake form ubuntu oficial repo )

# I used the graphical installer downloaded from qt.io
# My installation path is
# /home/dsistemas/Desktop/CPP/libraries/qt/
# My custom STATIC compiled QT 6.2.2 path is
# /home/dsistemas/Desktop/CPP/libraries/qt/6.2.2/build_static_2
#
# 1:
# ./configure -prefix /home/dsistemas/Desktop/CPP/libraries/qt/6.2.2/build_static_2 -confirm-license -release -optimize-size -static -opensource
# 2:
# make -j 4
# 3:
# make install
# 4: 
# In the path /home/dsistemas/Desktop/CPP/libraries/qt/6.2.2/build_static_2/static_external_libraries. I have the .a libraries
# libpgcommon.a <-- This library not come with pgsql-dev from ubuntu 20.04. You need download the source code from postgresql and compile manually
# libpgport.a <-- This library not come with pgsql-dev from ubuntu 20.04. You need download the source code from postgresql and compile manually
# libpq.a

#move to z_backup_external_libraries folder. Not needed anymore, resolved with set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
# libmysqlclient.a
# libodbc.a
# librt.a
# libssl.a
# libz.a
# libicudata.a
# libicui18n.a
# libicuuc.a

#Need this files here because the find_library/find_package of cmake found in the path the same library file for example:
# /usr/lib/x86_64-linux-gnu/librt.a 
# /usr/lib/x86_64-linux-gnu/librt.so
# Always return the librt.so and i don't known how change this cmake behavior
#Update 2022-01-02
#Resolved with set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

set(CMAKE_GENERATOR "Ninja")
set(CMAKE_PREFIX_PATH ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2 
                      ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/static_external_libraries)
set(QT_QMAKE_EXECUTABLE ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/bin/qmake)
#set(CMAKE_PREFIX_PATH ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/gcc_64) #<-- Defult installation 
#set(QT_QMAKE_EXECUTABLE ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/gcc_64/bin/qmake) #<-- Defult installation 

add_library(HV_LIBRARY STATIC IMPORTED GLOBAL)
set_target_properties(HV_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}libhv/lib/libhv_static.a)
target_include_directories(HV_LIBRARY INTERFACE ${LIBRARIES_FOLDER_PREFIX}libhv/include)

#add_library(QT_SQL_LIBRARY STATIC IMPORTED GLOBAL)
#SET_TARGET_PROPERTIES(QT_SQL_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/lib/libQt6Sql.a)
#target_include_directories(QT_SQL_LIBRARY INTERFACE ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/include/QtSql)

#add_library(QT_MYSQL_LIBRARY STATIC IMPORTED GLOBAL)
#SET_TARGET_PROPERTIES(QT_MYSQL_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/plugins/sqldrivers/libqsqlmysql.a)

#add_library(QT_POSTGRESQL_LIBRARY STATIC IMPORTED GLOBAL)
#SET_TARGET_PROPERTIES(QT_POSTGRESQL_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/plugins/sqldrivers/libqsqlpsql.a)

#add_library(MYSQL_LIBRARY STATIC IMPORTED GLOBAL)
#SET_TARGET_PROPERTIES(MYSQL_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/static_external_libraries/libmysqlclient.a)
#target_include_directories(MYSQL_LIBRARY INTERFACE /usr/include/mysql)

add_library(POSTGRESQL_LIBRARY STATIC IMPORTED GLOBAL)
set_target_properties(POSTGRESQL_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/static_external_libraries/libpq.a )
target_include_directories(POSTGRESQL_LIBRARY INTERFACE /usr/include/postgresql/)

add_library(POSTGRESQL_COMMON_LIBRARY STATIC IMPORTED GLOBAL)
set_target_properties(POSTGRESQL_COMMON_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/static_external_libraries/libpgcommon.a )

add_library(POSTGRESQL_PORT_LIBRARY STATIC IMPORTED GLOBAL)
set_target_properties(POSTGRESQL_PORT_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/static_external_libraries/libpgport.a )

#${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/libpgport.a
#${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/libpgport_shlib.a )

# add_library(QT6_CORE_LIBRARY STATIC IMPORTED GLOBAL)
# set_target_properties(QT6_CORE_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/lib/libQt6Core.a)
# target_include_directories(QT6_CORE_LIBRARY INTERFACE ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/include/QtCore ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/include/)
# target_compile_options( QT6_CORE_LIBRARY INTERFACE -fPIC )

# add_library(QT6_PCRE2_LIBRARY STATIC IMPORTED GLOBAL)
# set_target_properties(QT6_PCRE2_LIBRARY PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_2/lib/libQt6BundledPcre2.a)
# target_compile_options( QT6_PCRE2_LIBRARY INTERFACE -fPIC )

#add_library(QMYSQL_DRIVER STATIC IMPORTED GLOBAL)
#set_target_properties(QMYSQL_DRIVER PROPERTIES IMPORTED_LOCATION ${LIBRARIES_FOLDER_PREFIX}qt/6.2.2/build_static_1/../libqmysql.a)

#set(LIBRT "/usr/lib/x86_64-linux-gnu/librt.so") #<-- Add this
#set(ZLIB_LIBRARY "/usr/lib/x86_64-linux-gnu/libz.a")
#set(ICU_I18N_LIBRARY "/usr/lib/x86_64-linux-gnu/libicui18n.a")
#set(ICU_DATA_LIBRARY "/usr/lib/x86_64-linux-gnu/libicudata.a")

##set(MySQL_LIBRARY "/usr/lib/x86_64-linux-gnu/libmysqlclient.a")
##set(PostgreSQL_LIBRARY "/usr/lib/x86_64-linux-gnu/libpq.a")
##set(ODBC_LIBRARY "/usr/lib/x86_64-linux-gnu/libodbc.a")

#message( "MySQL_LIBRARY 1 => " ${MySQL_LIBRARY})
#message( "ICU_I18N_LIBRARY 1 => " ${ICU_I18N_LIBRARY})
#message( "ICU_DATA_LIBRARY 1 => " ${ICU_DATA_LIBRARY})

#find_library(MYSQL_CLIENT NAMES libmysqlclient.a)

#set(CMAKE_FIND_DEBUG_MODE TRUE) #<-- Help too much to look where cmake is looking for files and the order of priorities in the path
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql REQUIRED)
#set(CMAKE_FIND_DEBUG_MODE FALSE) #<-- Help too much to look where cmake is looking for files and the order of priorities in the paths

#set_target_properties(Qt${QT_VERSION_MAJOR}::Sql PROPERTIES SUFFIX ".a")
#set_target_properties(Qt${QT_VERSION_MAJOR}::Core PROPERTIES SUFFIX ".a")

#set(ICU_I18N_LIBRARY "/usr/lib/x86_64-linux-gnu/libicui18n.a")

#message( "MySQL_LIBRARY 2 => " ${MySQL_LIBRARY})

#message( "ZLIB_LIBRARY 2 => " ${ZLIB_LIBRARY})
#message( "ICU_I18N_LIBRARY 2 => " ${ICU_I18N_LIBRARY})
#message( "ICU_DATA_LIBRARY 2 => " ${ICU_DATA_LIBRARY})

#if(ZLIB_FOUND)
#message( "ZLIB_LIBRARIES => " ${ZLIB_LIBRARY} )
#endif()

#set(ZLIB_LIBRARIES "/usr/lib/x86_64-linux-gnu/libz.a") #<-- Add this

#message( "LIBRARIES_FOLDER_PREFIX 2 => " ${LIBMYQLCLIENT})

#set(MY_VAR "/usr/lib/x86_64-linux-gnu/librt.a" CACHE FILEPATH "docs..." FORCE)

#message( status ${LIBRT} )
#message( status ${HV_LIBRARY} )

add_executable(test04
  main.cpp
  test01.h
  test01.cpp
)

# Avoid linker library order errors
# https://gitlab.kitware.com/cmake/cmake/-/issues/21511
# https://stackoverflow.com/questions/45135/why-does-the-order-in-which-libraries-are-linked-sometimes-cause-errors-in-gcc
#                       "-Wl,--start-group"
#                       "-Wl,--end-group"
target_link_options(test04 PRIVATE --static -static-libgcc -static-libstdc++ -Wl,--start-group) #Force full static linked binary, -Wl,--start-group fix error of library link order

#find_package(OpenSSL REQUIRED)

#find_package(PostgreSQL REQUIRED)
#find_package(libpqxx CONFIG REQUIRED)

#message("OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
#message("OpenSSL libraries: ${OPENSSL_LIBRARIES}")

#message("PostgreSQL include dir: ${PostgreSQL_INCLUDE_DIR}")
#message("PostgreSQL libraries: ${PostgreSQL_LIBRARIES}")

#message( "=>" Qt${QT_VERSION_MAJOR}::Sql )

#Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql ICU::i18n ZLIB::ZLIB

#target_link_libraries( Qt${QT_VERSION_MAJOR}::Sql INTERFACE OpenSSL::SSL OpenSSL::Crypto pthread )

                       #PRIVATE libpqxx::pqxx
                       #PRIVATE PostgreSQL::PostgreSQL

# Avoid linker library order errors
# https://gitlab.kitware.com/cmake/cmake/-/issues/21511
# https://stackoverflow.com/questions/45135/why-does-the-order-in-which-libraries-are-linked-sometimes-cause-errors-in-gcc
#                       "-Wl,--start-group"
#                       "-Wl,--end-group"
 
#target_link_options( test04 PRIVATE "-Wl,--start-group" )  # Magic linker option, To fix the linker library order

target_link_libraries( #The order is relevant ot avoid linker error. With stupid message of "Undefined reference to blablabla"
                       test04 
                       PRIVATE HV_LIBRARY
                       #PRIVATE QT_SQL_LIBRARY               #8
                       #PRIVATE QT_MYSQL_LIBRARY             #2
                       #PRIVATE QT_POSTGRESQL_LIBRARY        #3
                       #PRIVATE MYSQL_LIBRARY                #4
                       PRIVATE POSTGRESQL_LIBRARY           #5 1 libpq.a This is not very well documented. Recent postgre version need 3 libraies no only libpq.a
                       PRIVATE POSTGRESQL_COMMON_LIBRARY    #6 2 libpqcommon.a
                       PRIVATE POSTGRESQL_PORT_LIBRARY      #7 3 libpgport.a
                       PRIVATE Qt${QT_VERSION_MAJOR}::Core  #1 The order is required to avoid linker errors
                       PRIVATE Qt${QT_VERSION_MAJOR}::Sql   #X <--- This not work. Generate a lot of error with undefined references
                       PRIVATE ssl                          #9  <=== System libraries need stay here. Later of the mysql/pgsql/qt libraries
                       PRIVATE crypto                       #10
                       PRIVATE crypt                        #11
                       PRIVATE pthread                      #12
                       PRIVATE dl                           #13
                       PRIVATE ltdl                         #14
                       PRIVATE z                            #15
                     )

#ssl crypto m dl z pthread

#target_link_libraries(test04 PRIVATE QT6_CORE_LIBRARY QT6_PCRE2_LIBRARY HV_LIBRARY pthread ssl crypto m dl z icuuc icui18n icudata )

#target_link_libraries(test03 Qt${QT_VERSION_MAJOR}::Core)
