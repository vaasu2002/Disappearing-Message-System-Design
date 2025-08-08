# Build DisappearSystemCommon as a static library
add_library(DisappearSystemCommon
    "DisappearSystemCommon.cpp"
    "DisappearSystemCommon.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DisappearSystemCommon PROPERTY CXX_STANDARD 20)
endif()
