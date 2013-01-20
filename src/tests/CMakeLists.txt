################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

## example

add_executable(test-lol EXCLUDE_FROM_ALL udp.cpp)
target_link_libraries(test-lol system ${SFML_LIBRARIES})

## your tests

add_executable(thread_test thread_test.cpp)
target_link_libraries(thread_test system)

add_executable(client_before_game
		client_test.cpp
		PreGame.cpp
		PreGame.hh
)

target_link_libraries(client_before_game system csv-parser ${SFML_LIBRARIES})


# add_executable(archiver_test archiver_test.cpp)
# target_link_libraries(archiver_test system)

# add_executable(sprite 
# sprites/AnimationInfos.cpp
# sprites/AnimationInfos.hh
# sprites/test_sprite.cpp
# sprites/Animation.cpp
# sprites/Animation.hh
# sprites/Board.cpp
# sprites/Board.hh
# )

# target_link_libraries(sprite system csv-parser ${SFML_LIBRARIES})

#test_sprite.cpp
#SpriteLoader.cpp
#SpriteLoader.hh
#Animation.hh
#Animation.cpp
