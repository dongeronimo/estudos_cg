cmake_minimum_required(VERSION 2.8)

project(Nehe03_Matrixes)


file(GLOB my_source_files "*.h" "*.cpp")
add_executable(Nehe03 ${my_source_files} )    

# Find Glut
set (GLUT_INCLUDE_DIR "C:/lib2/freeglut/include")
set (GLUT_LIB "C:/lib2/freeglut/lib/freeglut.lib")
target_include_directories(Nehe03 PUBLIC ${GLUT_INCLUDE_DIR})
target_link_libraries(Nehe03 ${GLUT_LIB} )
# Find GLEW
set (GLEW_INCLUDE_DIR "C:/lib2/glew-2.0.0/include")
set (GLEW_LIB "C:/lib2/glew-2.0.0/lib/Release/Win32/glew32.lib")
target_include_directories(Nehe03 PUBLIC ${GLEW_INCLUDE_DIR})
target_link_libraries(Nehe03 ${GLEW_LIB} )
# Find GLM
set(GLM_INCLUDE_DIR "C:/libs/glm-0.9.7.1/glm")
target_include_directories(Nehe03 PUBLIC ${GLM_INCLUDE_DIR})
#Põe a glew
#set(GLEW_INCLUDE_DIR "C:/libs/glew-1.13.0/include")
#set(GLEW_LIBRARY "C:/libs/glew-1.13.0/lib/Release/Win32/glew32s.lib")
#include_directories(${GLEW_INCLUDE_DIR})
#target_link_libraries(Nehe03 ${GLEW_LIBRARY})
#põe a GLM
#set(GLM_INCLUDE_DIR "C:/libs/glm-0.9.7.1/glm")
#include_directories(${GLM_INCLUDE_DIR})