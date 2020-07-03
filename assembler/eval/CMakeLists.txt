cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)


set(EVAL_TYPEDEFS
	YYSTYPE=int64_t
	YYSTYPE_PR=PRId64
)


BISON_TARGET(eval-parse eval.y
	${CMAKE_CURRENT_BINARY_DIR}/eval.tab.c
	DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/eval.tab.h
)
FLEX_TARGET(eval-lex eval.l
	${CMAKE_CURRENT_BINARY_DIR}/eval.lex.c
	DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/eval.lex.h
)
ADD_FLEX_BISON_DEPENDENCY(eval-lex eval-parse)


add_library(eval
	eval.c
	${BISON_eval-parse_OUTPUTS}
	${FLEX_eval-lex_OUTPUTS}
)
target_compile_definitions(eval PRIVATE ${EVAL_TYPEDEFS})
target_include_directories(eval PRIVATE ${CMAKE_CURRENT_BINARY_DIR})


add_executable(eval-test test.c)
target_compile_definitions(eval-test PRIVATE ${EVAL_TYPEDEFS})
target_include_directories(eval-test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(eval-test eval)

