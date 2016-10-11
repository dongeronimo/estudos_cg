cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
project(nehe_04b)


file(GLOB my_source_files "*.h" "*.cpp")
add_executable(nehe_04b utils.h geometry.h geometry.cpp nehe04b.cpp shader.h shader.cpp camera.cpp camera.h)

if(${UNIX})
    # Find OpenGL
    find_package(OpenGL REQUIRED)
    target_link_libraries(nehe_04b ${OPENGL_LIBRARIES})
    # Find Glut
    set (GLUT_INCLUDE_DIR "/usr/include/GL")
    set (GLUT_LIB "/usr/lib/x86_64-linux-gnu/libglut.so")
    target_include_directories(nehe_04b PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(nehe_04b ${GLUT_LIB})
    # Find Glew
    set (GLEW_INCLUDE_DIR "/usr/include/GL")
    set (GLEW_LIB "/usr/lib/x86_64-linux-gnu/libGLEW.so")
    target_include_directories(nehe_04b PUBLIC ${GLEW_INCLUDE_DIR})
    target_link_libraries(nehe_04b ${GLEW_LIB})
    # Find GLM
    set(GLM_INCLUDE_DIR "/usr/local/include/")
    # Find Assim
    set (ASSIMP_DIR "/home/geronimo/programacao/assimp-master/include")
    set (ASSIMP_LIB "/home/geronimo/programacao/assimp-master/lib/libassimp.so")
    target_include_directories(nehe_04b PUBLIC ${ASSIMP_DIR})
    target_link_libraries(nehe_04b ${ASSIMP_LIB})
else(${UNIX})
    # Find Glut
    set (GLUT_INCLUDE_DIR "C:/lib2/freeglut/include/GL")
    set (GLUT_LIB "C:/lib2/freeglut/lib/freeglut.lib")
    target_include_directories(nehe_04b PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(nehe_04b ${GLUT_LIB} )
    # Find GLEW
    set (GLEW_INCLUDE_DIR "C:/lib2/glew-2.0.0/include/GL")
    set (GLEW_LIB "C:/lib2/glew-2.0.0/lib/Release/Win32/glew32.lib")
    target_include_directories(nehe_04b PUBLIC ${GLEW_INCLUDE_DIR})
    target_link_libraries(nehe_04b ${GLEW_LIB} )
    # Find GLM
    set(GLM_INCLUDE_DIR "C:/libs/glm-0.9.7.1")
    target_include_directories(nehe_04b PUBLIC ${GLM_INCLUDE_DIR})
    # Find Assim
    set (ASSIMP_DIR "C:/Program Files (x86)/Assimp/include")
    set (ASSIMP_LIB "C:/Program Files (x86)/Assimp/lib/assimp-vc140-mt.lib")
    target_include_directories(nehe_04b PUBLIC ${ASSIMP_DIR})
    target_link_libraries(nehe_04b ${ASSIMP_LIB})
endif(${UNIX})