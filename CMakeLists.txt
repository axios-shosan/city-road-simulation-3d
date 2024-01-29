cmake_minimum_required(VERSION 3.22.1)
project(city_road_simulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(app main.cpp shader/shader.cpp model/objload.cpp
        utils/camera.h
        utils/mesh.h
        utils/model.h
)

find_package(glfw3 3.3.8 REQUIRED)
target_link_libraries(app glfw)
include_directories( SYSTEM "glad/include" )

add_library(glad glad/include/glad/glad.h glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include/)

add_library(shader shader/shader.hpp shader/shader.cpp)
target_include_directories(shader PUBLIC shader/)

add_library(model model/objload.hpp model/objload.cpp)
target_include_directories(model PUBLIC model/)
#target_include_directories(test PRIVATE ${YOUR_DIRECTORY})


target_link_libraries( app glad )


