cmake_minimum_required(VERSION 3.12)

# Find subdirs with CMakeLists.txt
set(CURR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB SUBDIRS RELATIVE ${CURR_DIR} ${CURR_DIR}/*)
foreach(SUBDIR ${SUBDIRS})
	set(CURR_SUBDIR ${CURR_DIR}/${SUBDIR})
	if(IS_DIRECTORY ${CURR_SUBDIR} AND EXISTS ${CURR_SUBDIR}/CMakeLists.txt)
		message(STATUS "Found arch: ${SUBDIR}")
		add_subdirectory(${SUBDIR})
	endif()
endforeach()

