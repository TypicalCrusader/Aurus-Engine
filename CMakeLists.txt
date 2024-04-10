cmake_minimum_required(VERSION 3.20)

#since on windows this piece of shit refuses to compile shit properly DESPITE it actually working i need to add this monstrocity, god has mercy on my soul

if (WIN32)
  list(APPEND CMAKE_PREFIX_PATH "C:/cygwin64/lib/cmake/SDL2")
  set(SDL2_INCLUDE_DIR /usr/include/SDL2)
  set(SDL2_LIBRARY /usr/lib/libSDL2.so)  
  set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
endif (WIN32)

set(CMAKE_C_COMPILER "GCC")
set(CMAKE_C_FLAGS "-O2")
set(CMAKE_C_FLAGS_DEBUG "-O0")
set(CMAKE_C_FLAGS_RELEASE "-O2")

project(
  AurusEngine
  VERSION 0.1
  LANGUAGES C
  DESCRIPTION "An C based SRPG FE-GBA Like engine"
  HOMEPAGE_URL "https://github.com/TypicalCrusader/Aurus-Engine"
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")
set(CMAKE_C_STANDARD_REQUIRED 17)

#SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED PACKAGE_FIND_VERSION_MIN 2.0.0 )
find_package(SDL2_mixer REQUIRED)

#LIBXML
find_package(LibXml2 REQUIRED)
include_directories(
  ${PROJECT_NAME} 
  ${SDL2MIXER_INCLUDE_DIRS}
  ${SDL2IMAGE_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIRS}
) 

add_executable(AurusEngine ${CMAKE_CURRENT_SOURCE_DIR}/.src/main.c)
target_link_libraries(
  ${PROJECT_NAME} 
  ${SDL2_LIBRARY} 
  #${SDL2IMAGE_LIBRARIES} 
  #SDL2
  SDL2_image
  SDL2_mixer
  LibXml2
)
