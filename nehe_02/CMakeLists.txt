cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(Nehe02_First_Polygon)


file(GLOB my_source_files "*.h" "*.cpp")
add_executable(Nehe02 nehe02.h nehe02.cpp shader.h shader.cpp triangulo.h triangulo.cpp)
if(${WIN32})
    # Find OpenGL
    find_package(OpenGL REQUIRED)
    target_link_libraries(Nehe02  ${OPENGL_LIBRARIES})
  # Find Glut
  set (GLUT_INCLUDE_DIR "C:/lib2/freeglut/include/GL")
  set (GLUT_LIB "C:/lib2/freeglut/lib/freeglut.lib")
  target_include_directories(Nehe02 PUBLIC ${GLUT_INCLUDE_DIR})
  target_link_libraries(Nehe02 ${GLUT_LIB} )
  # Find GLEW
  set (GLEW_INCLUDE_DIR "C:/lib2/glew-2.0.0/include/GL")
  set (GLEW_LIB "C:/lib2/glew-2.0.0/lib/Release/Win32/glew32.lib")
  target_include_directories(Nehe02 PUBLIC ${GLEW_INCLUDE_DIR})
  target_link_libraries(Nehe02 ${GLEW_LIB} )
  # Find GLM
  set(GLM_INCLUDE_DIR "C:/libs/glm-0.9.7.1")
  target_include_directories(Nehe02 PUBLIC ${GLM_INCLUDE_DIR})
endif(${WIN32})
if(${UNIX})
    # Find OpenGL
    find_package(OpenGL REQUIRED)
    target_link_libraries(Nehe02  ${OPENGL_LIBRARIES})
    # Find Glut
    set (GLUT_INCLUDE_DIR "/usr/include/GL")
    set (GLUT_LIB "/usr/lib/x86_64-linux-gnu/libglut.so")
    target_include_directories(Nehe02 PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(Nehe02 ${GLUT_LIB})
    # Find Glew
    set (GLEW_INCLUDE_DIR "/usr/include/GL")
    set (GLEW_LIB "/usr/lib/x86_64-linux-gnu/libGLEW.so")
    target_include_directories(Nehe02 PUBLIC ${GLEW_INCLUDE_DIR})
    target_link_libraries(Nehe02 ${GLEW_LIB})
    # Find GLM
    set(GLM_INCLUDE_DIR "/usr/local/include/")
    target_include_directories(Nehe02 PUBLIC ${GLM_INCLUDE_DIR})
endif(${UNIX})
