cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
	main.c
	machine.c
	mem.c
)

foreach(ARCH ${ARCH_LIST})
	set(TGT vvm-${ARCH})
	add_executable(${TGT} ${SOURCE_FILES})
	add_dependencies(${TGT} isa-${ARCH})
	target_include_directories(${TGT} PRIVATE
		"include"
		"${CMAKE_SOURCE_DIR}/generated/${ARCH}")
	target_compile_definitions(${TGT} PRIVATE
		ARCH="${ARCH}"
		VERSION="${VERSION}")
	install(TARGETS ${TGT})
endforeach()

