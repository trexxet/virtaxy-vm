cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
	main.c
	machine.c
	mem.c
)

set(TGT vvm-${ARCH})
add_executable(${TGT} ${SOURCE_FILES})
add_dependencies(${TGT} ${ARCH})
target_include_directories(${TGT} PRIVATE "include" "${CMAKE_SOURCE_DIR}/generated/${ARCH}")

