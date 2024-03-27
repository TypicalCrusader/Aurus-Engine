cmake_minimum_required(VERSION 3.20)

project(
  AurusEngine
  VERSION 0.1
  LANGUAGES C
  DESCRIPTION "An C based SRPG FE-GBA Like engine"
  HOMEPAGE_URL "https://github.com/TypicalCrusader/Aurus-Engine"
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")
set(CMAKE_C_STANDARD_REQUIRED C17)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/include/SDL2")


#SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED PACKAGE_FIND_VERSION_MIN 2.0.0 )
find_package(SDL2_mixer REQUIRED)
include_directories(
  ${PROJECT_NAME} 
  ${SDL2MIXER_INCLUDE_DIR}
  ${SDL2IMAGE_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIR}
) 

#LIBXML
find_package(LibXml2 REQUIRED)
include_directories(${PROJECT_NAME} ${LIBXML2_INCLUDE_DIRS}) 

add_executable(AurusEngine ${CMAKE_CURRENT_SOURCE_DIR}/.src/main.c)
target_link_libraries(
  ${PROJECT_NAME} 
  ${SDL2_LIBRARIES} 
  ${SDL2IMAGE_LIBRARIES} 
  ${SDL2MIXER_LIBRARIES} 
  ${LIBXML2_LIBRARIES}
)
