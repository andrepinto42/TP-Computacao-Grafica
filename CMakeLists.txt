cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(class1)

# set(OpenGL_GL_PREFERENCE LEGACY)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(${PROJECT_NAME} main.cpp
		Timer.cpp Timer.h
		tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
		tinyxml/tinyxml.cpp tinyxml/tinyxml.h
		tinyxml/tinystr.cpp tinyxml/tinystr.h
		Parser.cpp Parser.h CameraStatus.cpp CameraStatus.h
		TransformationsDataStruct/Transformations.cpp TransformationsDataStruct/Transformations.h
		Axes.cpp Axes.h
        DrawBasicPrimitives/HandlerDrawSquare.cpp DrawBasicPrimitives/HandlerDrawSquare.h
        DrawBasicPrimitives/HandleDrawSphere.cpp DrawBasicPrimitives/HandleDrawSphere.h
		DrawBasicPrimitives/DrawCone.cpp DrawBasicPrimitives/DrawCone.h
		HandlerModel.cpp HandlerModel.h
		TransformationsDataStruct/StoreModels.cpp TransformationsDataStruct/StoreModels.h
		HandleRenderTransform.cpp HandleRenderTransform.h
		catmull_rom.cpp catmull_rom.h
		TransformationsDataStruct/Transform.cpp TransformationsDataStruct/Transform.h BezierCurves.cpp BezierCurves.h ParseTeapotPatch.cpp ParseTeapotPatch.h )

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS},"tinyxml")
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")	
	
	
	include_directories(${TOOLKITS_FOLDER}/glut )
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} 
										  ${TOOLKITS_FOLDER}/glut/glut32.lib)
	
	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )	
	
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	
else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR},"tinyxml/**")
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

	if (NOT APPLE)
		find_package(GLEW REQUIRED)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif(NOT APPLE)

	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} )
	if(NOT GLUT_FOUND)
		message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)

endif(WIN32)
