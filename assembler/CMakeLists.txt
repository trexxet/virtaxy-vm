cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
	main.c
	asm.c
	argtypes.c
	symtable.c
)

foreach(ARCH ${ARCH_LIST})
	set(TGT vasm-${ARCH})
	add_executable(${TGT} ${SOURCE_FILES})
	add_dependencies(${TGT} isa-${ARCH})
	target_include_directories(${TGT} PRIVATE
		"include"
		"${CMAKE_SOURCE_DIR}/generated/${ARCH}")
	target_link_libraries(${TGT} m)
	target_compile_definitions(${TGT} PRIVATE
		ARCH="${ARCH}"
		VERSION="${VERSION}")
	install(TARGETS ${TGT})
endforeach()
