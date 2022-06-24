aux_source_directory(. PARSER)

add_library (Parser ${PARSER})
target_link_libraries(Parser Inter)