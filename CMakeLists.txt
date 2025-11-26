cmake_minimum_required(VERSION 3.28)
project (finlite)

include_directories(${CMAKE_SOURCE_DIR}/ext/sqlite)

#//////////////////////////
# source files 
#//////////////////////////

set(src ${src})
set(src ${src} src/finmart.h)
set(src ${src} ext/sqlite/sqlite3.c)
set(src ${src} src/lite.hh)
set(src ${src} src/lite.cc)
set(src ${src} src/server.hh)
set(src ${src} src/server.cc)
set(src ${src} src/generator.hh)
set(src ${src} src/generator.cc)
set(src ${src} src/http_client.cc)
add_executable(finlite ${src})

#//////////////////////////
# link with libraries
#//////////////////////////

set(lib_dep ${lib_dep})
if (MSVC)
  set(lib_dep ${lib_dep} Ws2_32.lib)
endif()

target_link_libraries(finlite ${lib_dep})
