cmake_minimum_required(VERSION 3.0)

project(open62541_compiled_nodeset_server C)

include_directories(build/src_generated/open62541)

add_executable(${PROJECT_NAME} src/main.c
                               build/src_generated/open62541/namespace_example_generated.c)

find_package(open62541)

ua_generate_nodeset(
    NAME "example"
    FILE "${PROJECT_SOURCE_DIR}/nodeset/Test.xml"
    DEPENDS_TYPES "UA_TYPES"
    DEPENDS_NS "${PROJECT_SOURCE_DIR}/nodeset/Opc.Ua.NodeSet2.xml"
)

target_link_libraries(${PROJECT_NAME} open62541)
