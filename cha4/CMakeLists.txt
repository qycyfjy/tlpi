project(Cha04FileIO)

add_executable(copy copy.cpp ../helper.h ../helper.cpp)
add_dependencies(copy spdlog)
target_include_directories(copy PUBLIC ${STAGING_DIR}/include/)
target_link_libraries(copy PRIVATE absl::base absl::strings fmt::fmt)

add_executable(seek_io seek_io.cpp ../helper.h ../helper.cpp)
add_dependencies(seek_io spdlog)
target_include_directories(seek_io PUBLIC ${STAGING_DIR}/include/)
target_link_libraries(seek_io PRIVATE absl::base absl::strings fmt::fmt)

add_executable(my_tee my_tee.cpp ../helper.h ../helper.cpp)
add_dependencies(my_tee spdlog)
target_include_directories(my_tee PUBLIC ${STAGING_DIR}/include/)
target_link_libraries(my_tee PRIVATE absl::base absl::strings fmt::fmt)