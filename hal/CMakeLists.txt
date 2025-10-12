# CMakeList.txt for HAL
# Build a library (`hal`) which exposes the header files as "hal/*.h"
# Use header as: #include "hal/button.h"

include_directories(hal/include)
file(GLOB MY_SOURCES "src/*.c")

add_library(hal STATIC ${MY_SOURCES})

# Include paths for HAL headers AND app headers (for read_channel.h)
target_include_directories(hal PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/app/include
)
