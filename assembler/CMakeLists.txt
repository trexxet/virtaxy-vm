cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
	main.c
	asm.c
	arg_type.c
	instr.c
	symtable.c
)

set(EVAL_TYPEDEFS
	YYSTYPE=int64_t
	YYSTYPE_PR=PRId64
)

add_subdirectory(eval)

foreach(ARCH ${ARCH_LIST})
	set(TGT vasm-${ARCH})
	add_executable(${TGT} ${SOURCE_FILES})
	add_dependencies(${TGT} isa-${ARCH})
	target_include_directories(${TGT} PRIVATE
		"include"
		"${CMAKE_SOURCE_DIR}/generated/${ARCH}")
	target_link_libraries(${TGT} m eval)
	target_compile_definitions(${TGT} PRIVATE
		ARCH="${ARCH}"
		VERSION="${VERSION}"
		${EVAL_TYPEDEFS})
	if(DEBUG)
		target_compile_options(${TGT} PRIVATE -g)
	endif()
	install(TARGETS ${TGT})
endforeach()

