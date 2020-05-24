#add_executable(Server app/server.c app/server.h)
#target_include_directories(Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/app)

add_executable(WindowServer windows/server.c windows/server.h)
target_include_directories(WindowServer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/windows)