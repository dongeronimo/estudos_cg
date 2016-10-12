cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
project(nehe_05)

add_executable(nehe_05 utils.h geometry.h geometry.cpp nehe05.cpp shader.h shader.cpp myObjLoader.h myObjLoader.cpp)

#Adiciona o mylib
include_directories(nehe_05 PUBLIC ${MyLib_INCLUDE_DIRS})
target_link_libraries(nehe_05 mylib)


if(${UNIX})
    # Find OpenGL
    find_package(OpenGL REQUIRED)
    target_link_libraries(nehe_05 ${OPENGL_LIBRARIES})
    # Find Glut
    set (GLUT_INCLUDE_DIR "/usr/include/GL")
    set (GLUT_LIB "/usr/lib/x86_64-linux-gnu/libglut.so")
    target_include_directories(nehe_05 PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(nehe_05 ${GLUT_LIB})
    # Find Glew
    set (GLEW_INCLUDE_DIR "/usr/include/GL")
    set (GLEW_LIB "/usr/lib/x86_64-linux-gnu/libGLEW.so")
    target_include_directories(nehe_05 PUBLIC ${GLEW_INCLUDE_DIR})
    target_link_libraries(nehe_05 ${GLEW_LIB})
    # Find GLM
    set(GLM_INCLUDE_DIR "/usr/local/include/")
    # Find Assim
    set (ASSIMP_DIR "/home/geronimo/programacao/assimp-master/include")
    set (ASSIMP_LIB "/home/geronimo/programacao/assimp-master/lib/libassimp.so")
    target_include_directories(nehe_05 PUBLIC ${ASSIMP_DIR})
    target_link_libraries(nehe_05 ${ASSIMP_LIB})
else(${UNIX})
    # Find Glut
    set (GLUT_INCLUDE_DIR "C:/Program Files/freeglut/include/GL")
    set (GLUT_LIB "C:/Program Files/freeglut/lib/freeglutd.lib")
    target_include_directories(nehe_05 PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(nehe_05 ${GLUT_LIB} )
    # Find GLEW
    set (GLEW_INCLUDE_DIR "C:/lib2/glew-2.0.0/include/GL")
    set (GLEW_LIB "C:/lib2/glew-2.0.0/lib/Release/x64/glew32.lib")
    target_include_directories(nehe_05 PUBLIC ${GLEW_INCLUDE_DIR})
    target_link_libraries(nehe_05 ${GLEW_LIB} )
    # Find GLM
    set(GLM_INCLUDE_DIR "C:/libs/glm-0.9.7.1")
    target_include_directories(nehe_05 PUBLIC ${GLM_INCLUDE_DIR})
    # Find Assim
    set (ASSIMP_DIR "C:/Program Files/Assimp/include")
    set (ASSIMP_LIB "C:/Program Files/Assimp/lib/assimp-vc120-mt.lib")
    target_include_directories(nehe_05 PUBLIC ${ASSIMP_DIR})
    target_link_libraries(nehe_05 ${ASSIMP_LIB})
endif(${UNIX})
