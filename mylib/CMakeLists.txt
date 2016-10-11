cmake_minimum_required(VERSION 2.8)

project(MyLib)
file(GLOB my_source_files "*.h" "*.cpp")
add_library (mylib ${my_source_files} ) 

# Expose B's public includes (including Boost transitively) to other
# subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

if(${UNIX})
    # Find OpenGL
    find_package(OpenGL REQUIRED)
    target_link_libraries(mylib ${OPENGL_LIBRARIES})
    # Find Glut
    set (GLUT_INCLUDE_DIR "/usr/include/GL")
    set (GLUT_LIB "/usr/lib/x86_64-linux-gnu/libglut.so")
    target_include_directories(mylib PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(mylib ${GLUT_LIB})
    # Find Glew
    set (GLEW_INCLUDE_DIR "/usr/include/GL")
    set (GLEW_LIB "/usr/lib/x86_64-linux-gnu/libGLEW.so")
    target_include_directories(mylib PUBLIC ${GLEW_INCLUDE_DIR})
    target_link_libraries(mylib ${GLEW_LIB})
    # Find GLM
    set(GLM_INCLUDE_DIR "/usr/local/include/")
    # Find Assim
    set (ASSIMP_DIR "/home/geronimo/programacao/assimp-master/include")
    set (ASSIMP_LIB "/home/geronimo/programacao/assimp-master/lib/libassimp.so")
    target_include_directories(mylib PUBLIC ${ASSIMP_DIR})
    target_link_libraries(mylib ${ASSIMP_LIB})
	# Find libpng
	set (LIBPNG_DIR "C:/Program Files (x86)/libpng/include")
	set (LIBPNG_LIB "C:/Program Files (x86)/libpng/lib/libpng16_staticd.lib")
	target_include_directories(mylib PUBLIC ${LIBPNG_DIR})
	target_link_libraries(mylib ${LIBPNG_LIB})
else(${UNIX})
    # Find Glut
    set (GLUT_INCLUDE_DIR "C:/Program Files/freeglut/include/GL")
    set (GLUT_LIB "C:/Program Files/freeglut/lib/freeglut_static.lib")
    target_include_directories(mylib PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(mylib ${GLUT_LIB} )
    # Find GLEW
    set (GLEW_INCLUDE_DIR "C:/lib2/glew-2.0.0/include/GL")
    set (GLEW_LIB "C:/lib2/glew-2.0.0/lib/Release/x64/glew32.lib")
    target_include_directories(mylib PUBLIC ${GLEW_INCLUDE_DIR})
    target_link_libraries(mylib ${GLEW_LIB} )
    # Find GLM
    set(GLM_INCLUDE_DIR "C:/libs/glm-0.9.7.1")
    target_include_directories(mylib PUBLIC ${GLM_INCLUDE_DIR})
    # Find Assim
    set (ASSIMP_DIR "C:/Program Files/Assimp/include")
    set (ASSIMP_LIB "C:/Program Files/Assimp/lib/assimp-vc140-mt.lib")
    target_include_directories(mylib PUBLIC ${ASSIMP_DIR})
    target_link_libraries(mylib ${ASSIMP_LIB})
	# Find libpng
	set (LIBPNG_DIR "C:/Program Files/libpng/include")
	set (LIBPNG_LIB "C:/Program Files/libpng/lib/libpng16d.lib")
	target_include_directories(mylib PUBLIC ${LIBPNG_DIR})
	target_link_libraries(mylib ${LIBPNG_LIB})
endif(${UNIX})


	
