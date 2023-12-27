cmake_minimum_required (VERSION 2.8)

project (demo)

set (TAGET public_test)

add_definitions(-g)
add_definitions(-DNDEBUG -D__USE_FILE_OFFSET64)
aux_source_directory (./ TOP_SRC)
aux_source_directory (src SUB_SRC)

set (SRC_LIST 
	${TOP_SRC} 
	${SUB_SRC}
	)

include_directories (${PROJECT_SOURCE_DIR}
					 inc 
					 )

add_executable(${TAGET}
			${SRC_LIST}
			)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
target_link_libraries(${TAGET}
		pthread
		m
		)

  install(TARGETS ${TAGET}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include  # 头文件安装路径
)
