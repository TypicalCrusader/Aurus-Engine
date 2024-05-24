cmake_minimum_required(VERSION 3.29)

project(
  AurusEngine
  VERSION 0.1.0.0
  LANGUAGES C
  DESCRIPTION "An C based SRPG FE-GBA Like engine"
  HOMEPAGE_URL "https://github.com/TypicalCrusader/Aurus-Engine"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

if (WIN32)
  message("Detected Windows as OS")
  if (NOT CMAKE_SIZEOF_VOID_P EQUAL ( 8 OR 4)) #fallback to detect architecture if somehow CMAKE_SIZEOF_VOID_P is of wrong value
    message(WARNING "CMAKE_SIZEOF_VOID_P doesnt have expected value, implying we build for 64 bit")
    set(CMAKE_SIZEOF_VOID_P "8")
  endif()  
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("Detected 64 bit OS")
  elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message("Detected 32 bit OS")  
  else()
    message(FATAL_ERROR "CMAKE_SIZEOF_VOID_P is neither 4 or 8 this should never happen,\nCMAKE_SIZEOF_VOID_P value is:" ${CMAKE_SIZEOF_VOID_P} )
    message(FATAL_ERROR "Cannot Detect OS Architecture")   
  endif()
    #set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
elseif(LINUX)
  message("Detected Linux as OS")
  set(LIBXML2_INCLUDE_DIR "/usr/include/libxml2")
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    #set(LIBXML2_LIBRARIES /usr/lib64/libxml2.so.2.10.4)
    message("Detected 64 bit OS")
  elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    #set(LIBXML2_LIBRARIES /usr/lib/libxml2.so.2.10.4) 
    message("Detected 32 bit OS") 
  else()
    message(FATAL_ERROR "Cannot Detect OS Architecture")   
  endif()
else()
  Message("Your OS is not supported")
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU" OR "Clang" OR "ARMCC" OR "TinyCC" OR "ARMClang")
  set(CMAKE_C_FLAGS "-O2")
  set(CMAKE_C_FLAGS_DEBUG "-O0")
  set(CMAKE_C_FLAGS_RELEASE "-O2")
  if(WIN32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
      message("Setting -m64 flag")   
      set(CMAKE_C_FLAGS_INIT "-m64")  
      set(CMAKE_EXE_LINKER_FLAGS_INIT    "-m64")
      set(CMAKE_MODULE_LINKER_FLAGS_INIT "-m64")
      set(CMAKE_SHARED_LINKER_FLAGS_INIT "-m64")  
    elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
      message("Setting -m32 flag")   
      set(CMAKE_C_FLAGS_INIT "-m32")  
      set(CMAKE_EXE_LINKER_FLAGS_INIT    "-m32")
      set(CMAKE_MODULE_LINKER_FLAGS_INIT "-m32")
      set(CMAKE_SHARED_LINKER_FLAGS_INIT "-m32")           
    endif()
  endif()  
  if(CMAKE_C_COMPILER_ID MATCHES "GNU")
    Message("Detected GCC as compiler")  
  elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
    Message("Detected Clang as compiler")   
  elseif(CMAKE_C_COMPILER_ID MATCHES "TinyCC") #if you are a madman then sure fuckin do it....
    Message("Detected TinyCC as compiler")          
  elseif(CMAKE_C_COMPILER_ID MATCHES "ARMCC") #if you are a madman then sure fuckin do it....
    Message("Detected ARMCC as compiler")     
  elseif(CMAKE_C_COMPILER_ID MATCHES "ARMClang") #if you are a madman then sure fuckin do it....
    Message("Detected ARMClang as compiler")     
  endif() 
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC") #as always only they have different flags....
  set(CMAKE_C_FLAGS "/O2")
  set(CMAKE_C_FLAGS_DEBUG "/OD")
  set(CMAKE_C_FLAGS_RELEASE "/O2")  
  Message("Detected MSVC as compiler")   
  message(WARNING "For your own sanity i recommend NOT using MSVC") 
else()
  message(FATAL_ERROR "Trying to build project with unsupported/esoteric compiler\nWhy do you do it?")   
endif()

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")
set(CMAKE_C_STANDARD_REQUIRED 17)

#SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED PACKAGE_FIND_VERSION_MIN 2.0.0 )
find_package(SDL2_ttf  REQUIRED)
find_package(SDL2_mixer REQUIRED)

#LIBXML
find_package(LibXml2 REQUIRED)
include_directories(
  ${PROJECT_NAME} 
  ${SDL2MIXER_INCLUDE_DIRS}
  ${SDL2IMAGE_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
) 

add_executable(AurusEngine 
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/main.c 
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/misc.c  
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/filehandler.c
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/battle.c
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/aurusscript.c
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/char.c  
  ${CMAKE_CURRENT_SOURCE_DIR}/.src/skills.c  
)
target_link_libraries(
  ${PROJECT_NAME} 
  #${SDL2_LIBRARY} 
  #${SDL2IMAGE_LIBRARIES} 
  SDL2
  SDL2_image
  SDL2_mixer
  SDL2_ttf
  ${LIBXML2_LIBRARIES}
)
