cmake_minimum_required(VERSION 3.14)
project(velecs-input VERSION 0.1.0)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories to bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT TARGET velecs-common)
    add_subdirectory(../velecs-common ${CMAKE_BINARY_DIR}/velecs-common)
endif()

if(NOT TARGET velecs-math)
    add_subdirectory(../velecs-math ${CMAKE_BINARY_DIR}/velecs-math)
endif()

# Source files for the library
set(LIB_SOURCES
    src/InputPollingState.cpp

    src/Input.cpp

    src/ActionProfile.cpp
    src/ActionMap.cpp
    src/Action.cpp

    src/InputStatus.cpp

    src/InputBindings/ButtonBinding.cpp
)

# Header files for the library (for IDE organization)
set(LIB_HEADERS
    include/velecs/input/Common.hpp

    include/velecs/input/PollingData.hpp
    include/velecs/input/InputPollingState.hpp
    
    include/velecs/input/Input.hpp

    include/velecs/input/ActionProfile.hpp
    include/velecs/input/ActionMap.hpp
    include/velecs/input/Action.hpp

    include/velecs/input/InputStatus.hpp

    include/velecs/input/InputBindings/InputBinding.hpp
    include/velecs/input/InputBindings/ButtonBinding.hpp
)

# Always build the library
add_library(velecs-input ${LIB_SOURCES} ${LIB_HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(velecs-input
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(velecs-input
    PUBLIC velecs-common
    PUBLIC velecs-math
)

if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # We're being included as a submodule
    set(VELECS_INPUT_LIBRARIES velecs-input PARENT_SCOPE)
endif()