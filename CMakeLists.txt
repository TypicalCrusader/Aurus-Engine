cmake_minimum_required(VERSION 3.29)

find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)


#since on windows this piece of shit refuses to compile shit properly DESPITE it actually working i need to add this monstrocity, god has mercy on my soul

project(
  AurusEngine
  VERSION 0.1
  LANGUAGES C
  DESCRIPTION "An C based SRPG FE-GBA Like engine"
  HOMEPAGE_URL "https://github.com/TypicalCrusader/Aurus-Engine"
)

if (WIN32)
  message("Detected Windows as OS")
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("Detected 64 bit OS")
  elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message("Detected 32 bit OS")  
  else()
    message(FATAL_ERROR "Cannot Detect OS Architecture")   
  endif()
    list(APPEND CMAKE_PREFIX_PATH "C:/cygwin64/lib/cmake/SDL2")
    set(SDL2_INCLUDE_DIR /usr/include/SDL2)
    set(SDL2_LIBRARY /usr/lib/libSDL2.so)  
    set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
elseif(LINUX)
  message("Detected Linux as OS")
  set(LIBXML2_INCLUDE_DIR "/usr/include/libxml2")
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(LIBXML2_LIBRARIES /usr/lib64/libxml2.so.2.10.4)
    message("Detected 64 bit OS")
  elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(LIBXML2_LIBRARIES /usr/lib/libxml2.so.2.10.4) 
    message("Detected 32 bit OS") 
  else()
    message(FATAL_ERROR "Cannot Detect OS Architecture")   
  endif()
else()
  Message("Your OS is not supported")
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU")
  set(CMAKE_C_FLAGS "-O2")
  set(CMAKE_C_FLAGS_DEBUG "-O0")
  set(CMAKE_C_FLAGS_RELEASE "-O2")
  Message("Detected GCC as compiler")  
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(CMAKE_C_FLAGS "-O2")
  set(CMAKE_C_FLAGS_DEBUG "-O0")
  set(CMAKE_C_FLAGS_RELEASE "-O2")
  Message("Detected Clang as compiler")    
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_C_FLAGS "/O2")
  set(CMAKE_C_FLAGS_DEBUG "/OD")
  set(CMAKE_C_FLAGS_RELEASE "/O2")  
  Message("Detected MSVC as compiler")    
elseif(CMAKE_C_COMPILER_ID MATCHES "ARMCC")
  set(CMAKE_C_FLAGS "-O2")
  set(CMAKE_C_FLAGS_DEBUG "-O0")
  set(CMAKE_C_FLAGS_RELEASE "-O2")  
  Message("Detected ARMCC as compiler")    
else()
  message(FATAL_ERROR "Trying to build project with unsupported compiler")   
endif()

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
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
  ${LIBXML2_INCLUDE_DIR}
) 

add_executable(AurusEngine 
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/main.c 
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/filehandler.c
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/battlehandler.c
)
target_link_libraries(
  ${PROJECT_NAME} 
  ${SDL2_LIBRARY} 
  #${SDL2IMAGE_LIBRARIES} 
  #SDL2
  SDL2_image
  SDL2_mixer
  ${LIBXML2_LIBRARIES}
)
