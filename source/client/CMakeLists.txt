#add_executable(Client app/client.c app/client.h)
#target_include_directories(Client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/app)

add_executable(WindowClient windows/client.c windows/client.h)
target_include_directories(WindowClient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/windows)