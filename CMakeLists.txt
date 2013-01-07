cmake_minimum_required(VERSION 2.6)
project (RType)

################################################################################
# Resolve dependancies
################################################################################

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# SFML
find_package(SFML 2.0 REQUIRED system window graphics audio)
include_directories(${SFML_INCLUDE_DIR})

################################################################################
# Build configuration
################################################################################

set(CMAKE_BUILD_TYPE Debug)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/libs
)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/libs/")
if(${UNIX})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x -ggdb")
endif()
if(${WIN32})
    set(GUI_TYPE WIN32)
endif()

################################################################################
# Build project
################################################################################

add_subdirectory(src)

################################################################################
# doc
################################################################################

#TODO Exporter ca dans un dossier doc/ et remplacer par add_subdirectory
#find_package(Doxygen)
#if(DOXYGEN_FOUND)
    #configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
        #${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    #add_custom_target(doc
        #${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        #COMMENT "Generating API documentation with Doxygen" VERBATIM
        #)
#endif(DOXYGEN_FOUND)
