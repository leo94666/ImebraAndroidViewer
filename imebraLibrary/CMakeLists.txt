cmake_minimum_required(VERSION 2.8)

project("imebrajni")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic -Wconversion -Wfloat-equal")
    set(IMEBRA_JNILIBRARIES pthread)

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

    message(STATUS "CLANG detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic -Wconversion -Wfloat-equal")
    set(IMEBRAJNI_LIBRARIES pthread)

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    message(STATUS "MSVC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /Wp64")
    set(IMEBRAJNI_LIBRARIES Kernel32)

endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

add_definitions(-DIMEBRA_USE_JAVA)

find_package(JNI REQUIRED)

set(IMEBRA_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/../../library/include" ${JNI_INCLUDE_DIRS})
set(IMEBRA_LIBRARIES ${IMEBRA_LIBRARIES} ${JNI_LIBRARIES})
message("Java libraries: ${JNI_LIBRARIES}")

include_directories(${IMEBRA_INCLUDE})

file(GLOB imebra_interface "${CMAKE_CURRENT_SOURCE_DIR}/../../library/include/**/*.h")
file(GLOB imebra_include "${CMAKE_CURRENT_SOURCE_DIR}/../../library/src/*.h")
file(GLOB imebra_src "${CMAKE_CURRENT_SOURCE_DIR}/../../library/src/*.cpp")
file(GLOB imebra_implementation_src "${CMAKE_CURRENT_SOURCE_DIR}/../../library/implementation/*.cpp")
file(GLOB imebra_implementation_include "${CMAKE_CURRENT_SOURCE_DIR}/../../library/implementation/*.h")
file(GLOB imebra_swig_implementation "${CMAKE_CURRENT_SOURCE_DIR}/java_wrapper.cxx")

add_library(imebrajni SHARED
    ${imebra_implementation_src}
    ${imebra_implementation_include}
    ${imebra_include}
    ${imebra_src}
    ${imebra_interface}
    ${imebra_swig_implementation}
)

target_link_libraries(imebrajni ${IMEBRA_LIBRARIES})

