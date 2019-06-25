set(CURRENT_PROJECT_NAME app)

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
  "/usr/include/ffmpeg"
  ${OpenCV_INCLUDE_DIRS}
  ${SPDLOG_INCLUDE_DIRS}
  ${YAML_CPP_INCLUDE_DIR}
)

set(LINK_LIBS
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
  -lopencv_imgcodecs
  -lopencv_highgui
)
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${LINK_LIBS}")

include_directories(${GRPC_PROTOCOL_INCLUDE_DIRS})

link_directories(${BINARY_OUTPUT_DIR})

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
source_group("Header Files" FILES ${CURRENT_HEADERS}) 
add_executable(${CURRENT_PROJECT_NAME} ${CURRENT_HEADERS} ${CURRENT_PROJECT_SRC_LISTS})

set_target_properties(${CURRENT_PROJECT_NAME}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY
  "${BINARY_OUTPUT_DIR}"
)

target_link_libraries(${CURRENT_PROJECT_NAME} ${GRPC_PROTOCOL_LIBRARY} ${YAML_CPP_LIBRARIES})
