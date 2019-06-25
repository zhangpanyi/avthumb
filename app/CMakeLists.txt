set(CURRENT_PROJECT_NAME server)

set(CURRENT_PROJECT_SRC_LISTS 
  avmedia.cpp
  avthumb.cpp
  config.cpp
  etcd_client_v3.cpp
  logger.cpp
  main.cpp
  repeater.cpp
  service.cpp
  thread_pool.cpp
  worker.cpp
)

find_package(yaml-cpp REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${SPDLOG_INCLUDE_DIRS}
  ${YAML_CPP_INCLUDE_DIR}
  ${GRPC_PROTOCOL_INCLUDE_DIRS}
)

set(LINK_LIBRARIES
  -lgpr
  -lpthread
  -lprotobuf
  -lgrpc++
  -lavcodec
  -lavformat
  -lavutil
  -lswscale
  -lavcodec
  -lopencv_core
  -lopencv_imgproc
  -lopencv_highgui
)

link_directories(${BINARY_OUTPUT_DIR})

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
source_group("Header Files" FILES ${CURRENT_HEADERS}) 
add_executable(${CURRENT_PROJECT_NAME} ${CURRENT_HEADERS} ${CURRENT_PROJECT_SRC_LISTS})

set_target_properties(${CURRENT_PROJECT_NAME}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY
  "${BINARY_OUTPUT_DIR}"
)

target_link_libraries(${CURRENT_PROJECT_NAME} ${YAML_CPP_LIBRARIES} ${LINK_LIBRARIES} ${GRPC_PROTOCOL_LIBRARY})
