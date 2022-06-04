cmake_minimum_required(VERSION 3.15)

project(final_project)

set(SOURCE_PATH ${CMAKE_SOURCE_DIR}/src)
set(THIRD_PARTY_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/external)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

file(COPY "media/" DESTINATION "media")

add_subdirectory(${THIRD_PARTY_LIBRARY_PATH}/glfw)
add_subdirectory(${THIRD_PARTY_LIBRARY_PATH}/glad)
add_subdirectory(${THIRD_PARTY_LIBRARY_PATH}/glm)
add_subdirectory(${THIRD_PARTY_LIBRARY_PATH}/imgui)
add_subdirectory(${THIRD_PARTY_LIBRARY_PATH}/stb)
add_subdirectory(${THIRD_PARTY_LIBRARY_PATH}/obj_loader)

file(GLOB BASE_HDR ${SOURCE_PATH}/base/*.h)
file(GLOB BASE_SRC ${SOURCE_PATH}/base/*.cpp)
file(GLOB PROJECT_HDR ${SOURCE_PATH}/*.h)
file(GLOB PROJECT_SRC ${SOURCE_PATH}/*.cpp)

if (WIN32)
	add_executable(final_project ${BASE_HDR} ${BASE_SRC} ${PROJECT_HDR} ${PROJECT_SRC} src/genBaseElements.cpp src/genBaseElements.h src/NPC.cpp src/NPC.h src/screenshot.cpp src/screenshot.h)
elseif (UNIX)
	add_executable(final_project ${BASE_HDR} ${BASE_SRC} ${PROJECT_HDR} ${PROJECT_SRC} src/genBaseElements.cpp src/genBaseElements.h src/NPC.cpp src/NPC.h)
endif ()

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
elseif (UNIX)
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Debug")
    else ()
        set_target_properties(${PROJECT_NAME} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Release")
    endif ()
endif ()

target_include_directories(
        final_project PUBLIC
        ${THIRD_PARTY_LIBRARY_PATH}/glfw/include
        ${THIRD_PARTY_LIBRARY_PATH}/glad/include
        ${THIRD_PARTY_LIBRARY_PATH}/glm
        ${THIRD_PARTY_LIBRARY_PATH}/imgui
        ${THIRD_PARTY_LIBRARY_PATH}/stb
        ${THIRD_PARTY_LIBRARY_PATH}/obj_loader
)

target_link_libraries(final_project PUBLIC glfw glad glm imgui stb obj_loader)