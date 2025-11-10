cmake_minimum_required(VERSION 3.20)

set(PROJECT ImGuiKit)

enable_language(C CXX)

project(
	${PROJECT} 
	LANGUAGES CXX
)

option(USE_NEW_SINGLETON "Use new sigleton" ON)

option(USE_IMPLOT "Use ImPlot" OFF)
option(USE_IM_TOOLS "Use ImTools" OFF)
option(USE_IMGUI_FILE_DIALOG "Use ImGui_FileDialog" OFF)

option(IMGUIPACK_USE_STD_FILESYSTEM "Enable the use of std::filesystem in ImGui_FileDialog" OFF)

option(USE_CUSTOM_IMGUI_CONFIG "Use Custom ImGui Config (User Side)" OFF)

if(USE_SHARED_LIBS)
	set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
	set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "" FORCE)
else()
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
	set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "" FORCE)
endif()

if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX _debug)
endif()
if(NOT CMAKE_RELEASE_POSTFIX)
  set(CMAKE_RELEASE_POSTFIX)
endif()
if(NOT CMAKE_MINSIZEREL_POSTFIX)
  set(CMAKE_MINSIZEREL_POSTFIX _minsizerel)
endif()
if(NOT CMAKE_RELWITHDEBINFO_POSTFIX)
  set(CMAKE_RELWITHDEBINFO_POSTFIX _reldeb)
endif()

#####################################################
##### FREETYPE
#####################################################

set(FREETYPE_LIBRARIES freetype)
set(FT_WITH_PNG OFF CACHE BOOL "" FORCE)
set(FT_WITH_ZLIB OFF CACHE BOOL "" FORCE)
set(FT_WITH_BZIP2 OFF CACHE BOOL "" FORCE)
set(FT_WITH_BROTLI OFF CACHE BOOL "" FORCE)
set(FT_WITH_HARFBUZZ OFF CACHE BOOL "" FORCE)
set(FREETYPE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/freetype2/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/freetype2 EXCLUDE_FROM_ALL)

if(USE_SHARED_LIBS)
	set_target_properties(freetype PROPERTIES FOLDER 3rdParty/Shared)
else()
	set_target_properties(freetype PROPERTIES FOLDER 3rdParty/Static)
endif()

#####################################################
#####################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

add_definitions(-DUSE_STD_FILESYSTEM)
add_definitions(-DFT_DEBUG_LEVEL_TRACE)
add_definitions(-DIMGUI_ENABLE_FREETYPE)
add_definitions(-DIMGUI_DEFINE_MATH_OPERATORS)

if(NOT USE_CUSTOM_IMGUI_CONFIG)
	add_definitions(-DIMGUI_USER_CONFIG="${CMAKE_CURRENT_SOURCE_DIR}/CustomImConfig.h")
endif()

#####################################################
##### IMGUI
#####################################################

file(GLOB IMGUI_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_Docking/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_Docking/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_Docking/misc/freetype/imgui_freetype.h
		${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_Docking/misc/freetype/imgui_freetype.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ PREFIX pack FILES ${IMGUI_SOURCES})

#####################################################
##### IMPLOT
#####################################################

if (USE_IMPLOT)
	message(STATUS "USE IM PLOT")
	file(GLOB IMGUI_IMPLOT_SOURCES
			${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_ImPlot/*.h
			${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_ImPlot/*.cpp)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ PREFIX pack FILES ${IMGUI_IMPLOT_SOURCES})
endif()

#####################################################
##### IMTOOLS
#####################################################

if (USE_IM_TOOLS)
	message(STATUS "USE IN TOOLS")
	file(GLOB IMGUI_IMTOOLS_SOURCES
			${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_Tools/*.h
			${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_Tools/*.hpp
			${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_Tools/*.cpp)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ PREFIX pack FILES ${IMGUI_IMTOOLS_SOURCES})
endif()

#####################################################
##### IMGUIFILEDIALOG
#####################################################

if (USE_IMGUI_FILE_DIALOG)
	message(STATUS "USE IMGUI FILE DIALOG")
	file(GLOB IMGUI_IMGUIFILEDIALOG_SOURCES
			${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_FileDialog/*.h
			${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_FileDialog/*.cpp)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ PREFIX pack FILES ${IMGUI_IMGUIFILEDIALOG_SOURCES})
endif()

#####################################################
##### IMGUIPACK
#####################################################

file(GLOB IMGUI_IMGUIPACK_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/ PREFIX header FILES ${IMGUI_IMGUIPACK_SOURCES})

#####################################################

if (BUILD_SHARED_LIBS)
	set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "" FORCE)
	add_library(${PROJECT} 
		${IMGUI_SOURCES} 
		${IMGUI_IMPLOT_SOURCES}
		${IMGUI_IMTOOLS_SOURCES}
		${IMGUI_IMGUIPACK_SOURCES}
		${IMGUI_IMGUIFILEDIALOG_SOURCES}
	)
	target_compile_definitions(${PROJECT} INTERFACE BUILD_IMGUI_PACK_SHARED_LIBS)
	set_target_properties(${PROJECT} PROPERTIES POSITION_INDEPENDENT_CODE ON)
else()
	set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "" FORCE)
	add_library(${PROJECT} STATIC 
		${IMGUI_SOURCES} 
		${IMGUI_IMPLOT_SOURCES}
		${IMGUI_IMTOOLS_SOURCES}
		${IMGUI_IMGUIPACK_SOURCES}
		${IMGUI_IMGUIFILEDIALOG_SOURCES}
	)
endif()

set(IMGUIPACK_INCLUDE_DIRS
	${FREETYPE_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/
	${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_Tools/
	${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_ImPlot/
	${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_Docking/
	${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/ImGui_FileDialog/
)

target_include_directories(${PROJECT} PUBLIC
	${IMGUIPACK_INCLUDE_DIRS}
)

if (USE_NEW_SINGLETON)
	target_compile_definitions(${PROJECT} PRIVATE -DNEW_SINGLETON)
endif()

if(UNIX)
    target_compile_options(${PROJECT} PUBLIC "-Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter")
endif()

if (USE_IMPLOT)
	target_compile_definitions(${PROJECT} PUBLIC USE_IMPLOT)
endif()

if (USE_IM_TOOLS)
	target_compile_definitions(${PROJECT} PUBLIC USE_IM_TOOLS)
endif()

if (USE_IMGUI_FILE_DIALOG)
	target_compile_definitions(${PROJECT} PUBLIC USE_IMGUI_FILE_DIALOG)
endif()

if(USE_DEBUG_SANITIZER)
	target_compile_options(${PROJECT} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address -static-libasan -static-libasan>)
	target_link_options(${PROJECT} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address -static-libasan>)
	message(STATUS "Address Sanitizer enabled for projet ${PROJECT}")
endif()

target_link_libraries(${PROJECT}
	${FREETYPE_LIBRARIES}
)

set_target_properties(${PROJECT} PROPERTIES OUTPUT_NAME "ImGuiKit")

set(IMGUIPACK_INCLUDE_DIRS ${IMGUIPACK_INCLUDE_DIRS} PARENT_SCOPE)
set(IMGUIPACK_LIBRARIES ${PROJECT} PARENT_SCOPE)
set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARIES} PARENT_SCOPE)

install(TARGETS ${PROJECT} RUNTIME DESTINATION / COMPONENT APP_LIBS_${TINYXML2_LIBRARIES})
install(TARGETS ${FREETYPE_LIBRARIES} RUNTIME DESTINATION / COMPONENT APP_LIBS_${FREETYPE_LIBRARIES})
