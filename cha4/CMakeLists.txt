project(Cha04FileIO)

add_executable(copy copy.cpp ../helper.h)
add_dependencies(copy spdlog)
target_include_directories(copy PUBLIC ${STAGING_DIR}/include/)
target_link_libraries(copy PRIVATE absl::base absl::strings fmt::fmt)