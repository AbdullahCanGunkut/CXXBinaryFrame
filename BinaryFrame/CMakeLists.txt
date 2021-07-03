
macro(SetDefaultCompilerVersion NAME)
set_target_properties(${NAME} PROPERTIES
CXX_STANDARD ${CXX_STANDARD_VERSION}
CXX_STANDARD_REQUIRED ON
)
endmacro()


cmake_minimum_required(VERSION 3.1)

project(CXXBinaryFrame VERSION 1.0.0)

include_directories(Headers)

add_executable(BinaryFrameStringExample "${PROJECT_SOURCE_DIR}/Examples/BinaryFrameStringExample.cpp")
add_executable(BinaryFrameVectorExample "${PROJECT_SOURCE_DIR}/Examples/BinaryFrameVectorExample.cpp")
add_executable(BasicObjectExample "${PROJECT_SOURCE_DIR}/Examples/BasicObjectExample.cpp")

set(CXX_BINARY_FRAME_TYPENAME_LIB CXXBinaryFrameTypename)
set(CXX_BINARY_FRAME_FACILITATE_STATIC_LIB CXXBinaryFrameFacilitateStatic)
set(CXX_BINARY_FRAME_BINARY_STREAM_LIB CXXBinaryFrameBinaryStream)
set(CXX_BINARY_FRAME_INCLUDE_PATH "/usr/include/CXXBinaryLoader/CXXBinaryFrame")
set(CXX_BINARY_FRAME_LIBRARY_PATH "/usr/lib")

if(NOT DEFINED CXX_STANDARD_VERSION)
message("Standard Version is set as 11 ! (Because CXX_STANDARD_VERSION isn't defined !)")
set(CXX_STANDARD_VERSION 11)

elseif (${CXX_STANDARD_VERSION} LESS 11)
message(FATAL_ERROR "CXX_STANDARD_VERSION is less than 11 !")
endif()

SetDefaultCompilerVersion(BinaryFrameStringExample)
SetDefaultCompilerVersion(BinaryFrameVectorExample)
SetDefaultCompilerVersion(BasicObjectExample)


add_library(${CXX_BINARY_FRAME_TYPENAME_LIB} STATIC
"${PROJECT_SOURCE_DIR}/Sources/CXXBinaryFrameTypename.cpp")

add_library(${CXX_BINARY_FRAME_FACILITATE_STATIC_LIB}  STATIC
"${PROJECT_SOURCE_DIR}/Sources/CXXBinaryFrameFacilitateStatic.cpp")

add_library(${CXX_BINARY_FRAME_BINARY_STREAM_LIB}  STATIC
"${PROJECT_SOURCE_DIR}/Sources/CXXBinaryFrameBinaryStream.cpp")



SetDefaultCompilerVersion(${CXX_BINARY_FRAME_TYPENAME_LIB})
SetDefaultCompilerVersion(${CXX_BINARY_FRAME_FACILITATE_STATIC_LIB})
SetDefaultCompilerVersion(${CXX_BINARY_FRAME_BINARY_STREAM_LIB})



target_link_libraries(BasicObjectExample PRIVATE ${CXX_BINARY_FRAME_BINARY_STREAM_LIB} ${CXX_BINARY_FRAME_FACILITATE_STATIC_LIB} ${CXX_BINARY_FRAME_TYPENAME_LIB} )
target_link_libraries(BinaryFrameStringExample PRIVATE ${CXX_BINARY_FRAME_BINARY_STREAM_LIB} ${CXX_BINARY_FRAME_FACILITATE_STATIC_LIB} ${CXX_BINARY_FRAME_TYPENAME_LIB} )
target_link_libraries(BinaryFrameVectorExample PRIVATE ${CXX_BINARY_FRAME_BINARY_STREAM_LIB} ${CXX_BINARY_FRAME_FACILITATE_STATIC_LIB} ${CXX_BINARY_FRAME_TYPENAME_LIB} )
