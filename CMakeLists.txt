cmake_minimum_required(VERSION 3.12)
project(Berry4D)
set(CMAKE_CXX_FLAGS "-O0")

set(CMAKE_CXX_STANDARD 17)
set(HEADERS /usr/local/include)
set(GLFW_LINK /usr/local/lib/libglfw3.a)
set(FRAMEWORKS_1 /System/Library/Frameworks/Cocoa.framework)
set(FRAMEWORKS_2 /System/Library/Frameworks/OpenGL.framework)
set(FRAMEWORKS_3 /System/Library/Frameworks/GLUT.framework)
set(FRAMEWORKS_4 /System/Library/Frameworks/CoreVideo.framework)
set(FRAMEWORKS_5 /System/Library/Frameworks/IOKit.framework)

include_directories(${HEADERS})
aux_source_directory(Berry4D src)

link_libraries(${GLFW_LINK} ${FRAMEWORKS_1} ${FRAMEWORKS_2} ${FRAMEWORKS_3} ${FRAMEWORKS_4} ${FRAMEWORKS_5})

add_executable(Berry4D main.cpp src/core.cpp include/core.h src/scene.cpp include/scene.h src/camera.cpp include/camera.h src/object.cpp include/object.h src/vec.cpp include/vec.h include/timestamp.h src/cube.cpp include/cube.h src/be4dLoader.cpp include/be4dLoader.h src/light.cpp include/light.h)