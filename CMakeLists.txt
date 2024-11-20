target_sources(${NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/color_conv.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/csal_ipc_message_publishqueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/csal_ipc_message_subscribequeue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/csal_ipc_thread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/csal_ipc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/csal_ledmatrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/os_led_strip.cpp
)
