cmake_minimum_required(VERSION 2.8)

project(Nehe04_Geometry)


file(GLOB my_source_files "*.h" "*.cpp")
add_executable(Nehe04 ${my_source_files} )    

# Find Glut
set (GLUT_INCLUDE_DIR "C:/lib2/freeglut/include")
set (GLUT_LIB "C:/lib2/freeglut/lib/freeglut.lib")
target_include_directories(Nehe04 PUBLIC ${GLUT_INCLUDE_DIR})
target_link_libraries(Nehe04 ${GLUT_LIB} )
# Find GLEW
set (GLEW_INCLUDE_DIR "C:/lib2/glew-2.0.0/include")
set (GLEW_LIB "C:/lib2/glew-2.0.0/lib/Release/Win32/glew32.lib")
target_include_directories(Nehe04 PUBLIC ${GLEW_INCLUDE_DIR})
target_link_libraries(Nehe04 ${GLEW_LIB} )
# Find GLM
set(GLM_INCLUDE_DIR "C:/libs/glm-0.9.7.1/glm")
target_include_directories(Nehe04 PUBLIC ${GLM_INCLUDE_DIR})
