cmake_minimum_required(VERSION 3.16)

add_executable(program1
    main.cpp
    Buffer.cpp
    Buffer.h
    Producer.cpp
    Producer.h
    Consumer.cpp
    Consumer.h
    IBuffer.h
)

target_link_libraries(program1 PRIVATE my_library)

if(WIN32)
    target_link_libraries(program1 PRIVATE ws2_32)
endif()

add_custom_command(TARGET program1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:my_library>
    $<TARGET_FILE_DIR:program1>
)