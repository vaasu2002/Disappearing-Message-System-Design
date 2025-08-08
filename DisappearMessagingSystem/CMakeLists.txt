add_executable(DisappearMessagingSystem
    "DisappearMessagingSystem.cpp"
    "DisappearMessagingSystem.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DisappearMessagingSystem PROPERTY CXX_STANDARD 20)
endif()

# Link with the common library
target_link_libraries(DisappearMessagingSystem PRIVATE DisappearSystemCommon)

# Also make sure the header path is known
target_include_directories(DisappearMessagingSystem PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../libs/DisappearSystemCommon
)
