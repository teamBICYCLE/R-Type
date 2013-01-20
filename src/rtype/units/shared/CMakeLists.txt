project(shared_monsters)

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/resources/shared/")

add_library(DefaultMonster SHARED
	${CMAKE_CURRENT_LIST_DIR}/DefaultMonster.cpp
)

add_library(DumbMonster SHARED
	${CMAKE_CURRENT_LIST_DIR}/DumbMonster.cpp
)

