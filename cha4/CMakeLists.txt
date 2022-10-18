project(Cha04FileIO)

add_executable(copy copy.cpp ../helper.h ../helper.cpp)
add_dependencies(copy spdlog)
target_include_directories(copy PUBLIC ${STAGING_DIR}/include/)
target_link_libraries(copy PRIVATE absl::base absl::strings fmt::fmt)

add_executable(seek_io seek_io.cpp ../helper.h ../helper.cpp)
add_dependencies(seek_io spdlog)
target_include_directories(seek_io PUBLIC ${STAGING_DIR}/include/)
target_link_libraries(seek_io PRIVATE absl::base absl::strings fmt::fmt)