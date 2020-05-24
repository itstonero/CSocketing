add_library(WindowManager windows/window_manager.h windows/window_manager.c)

target_include_directories(WindowManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/windows)

target_link_libraries(WindowManager PUBLIC Ws2_32 Mswsock Advapi32)