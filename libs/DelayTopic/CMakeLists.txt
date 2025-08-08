# Build DisappearSystemCommon as a static library
add_library(DelayTopic
    "DelayTopic.cpp"
    "DelayTopic.h"
 "queue/IMessageQueue.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DisappearSystemCommon PROPERTY CXX_STANDARD 20)
endif()
