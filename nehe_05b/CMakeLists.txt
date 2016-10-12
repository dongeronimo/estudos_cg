cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
project(nehe_05b)

add_executable(nehe_05b nehe_05b.cpp)

#Adiciona o mylib
include_directories(nehe_05b PUBLIC ${MyLib_INCLUDE_DIRS})
target_link_libraries(nehe_05b mylib)


if(${UNIX})
    # Find OpenGL
    find_package(OpenGL REQUIRED)
    target_link_libraries(nehe_05b ${OPENGL_LIBRARIES})
    # Find Glut
    set (GLUT_INCLUDE_DIR "/usr/include/GL")
    set (GLUT_LIB "/usr/lib/x86_64-linux-gnu/libglut.so")
    target_include_directories(nehe_05b PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(nehe_05b ${GLUT_LIB})
    # Find Glew
    set (GLEW_INCLUDE_DIR "/usr/include/GL")
    set (GLEW_LIB "/usr/lib/x86_64-linux-gnu/libGLEW.so")
    target_include_directories(nehe_05b PUBLIC ${GLEW_INCLUDE_DIR})
    target_link_libraries(nehe_05b ${GLEW_LIB})
    # Find GLM
    set(GLM_INCLUDE_DIR "/usr/local/include/")
    # Find Assim
    set (ASSIMP_DIR "/home/geronimo/programacao/assimp-master/include")
    set (ASSIMP_LIB "/home/geronimo/programacao/assimp-master/lib/libassimp.so")
    target_include_directories(nehe_05b PUBLIC ${ASSIMP_DIR})
    target_link_libraries(nehe_05b ${ASSIMP_LIB})
else(${UNIX})
	find_package(OpenGL REQUIRED)
	target_link_libraries(nehe_05b ${OPENGL_LIBRARIES})
    # Find Glut
    set (GLUT_INCLUDE_DIR "C:/Program Files/freeglut/include/GL")
    set (GLUT_LIB "C:/Program Files/freeglut/lib/freeglutd.lib")
    target_include_directories(nehe_05b PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(nehe_05b ${GLUT_LIB} )
    # Find GLEW
    set (GLEW_INCLUDE_DIR "C:/lib2/glew-2.0.0/include/GL")
    set (GLEW_LIB "C:/lib2/glew-2.0.0/lib/Release/x64/glew32.lib")
    target_include_directories(nehe_05b PUBLIC ${GLEW_INCLUDE_DIR})
    target_link_libraries(nehe_05b ${GLEW_LIB} )
    # Find GLM
    set(GLM_INCLUDE_DIR "C:/libs/glm-0.9.7.1")
    target_include_directories(nehe_05b PUBLIC ${GLM_INCLUDE_DIR})
    # Find Assim
    set (ASSIMP_DIR "C:/Program Files/Assimp/include")
    set (ASSIMP_LIB "C:/Program Files/Assimp/lib/assimp-vc120-mt.lib")
    target_include_directories(nehe_05b PUBLIC ${ASSIMP_DIR})
    target_link_libraries(nehe_05b ${ASSIMP_LIB})
	# Find GLFW - Não vou usar glut
	set (GLFW_INCLUDE_DIR "C:/Program Files/GLFW/include/GLFW")
	set (GLFW_LIB "C:/Program Files/GLFW/lib/glfw3dll.lib")
	target_include_directories(nehe_05b PUBLIC ${GLFW_INCLUDE_DIR})
    target_link_libraries(nehe_05b ${GLFW_LIB} )
endif(${UNIX})
