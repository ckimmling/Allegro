project(prog1)

add_executable(prog1 main.cpp)

target_link_libraries(prog1 alleg)

install(TARGETS prog1 RUNTIME DESTINATION bin)
