set(CURRENT_PROJECT_NAME protocol)

set(CURRENT_PROJECT_SRC_LISTS 
  auth.grpc.pb.cc
  auth.pb.cc
  avthumb.pb.cc
  avthumb.grpc.pb.cc
  kv.grpc.pb.cc
  kv.pb.cc
  rpc.grpc.pb.cc
  rpc.pb.cc
)

add_library(${CURRENT_PROJECT_NAME} STATIC ${CURRENT_PROJECT_SRC_LISTS})

set_target_properties(${CURRENT_PROJECT_NAME}
  PROPERTIES
  OUTPUT_NAME ${GRPC_PROTOCOL_LIBRARY}
  ARCHIVE_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR}
)
