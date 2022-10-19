project(Cha5FileIODetail)

add_executable(ex5.2 ex5.2.cpp ../helper.h ../helper.cpp)
add_dependencies(ex5.2 spdlog)
target_include_directories(ex5.2 PUBLIC ${STAGING_DIR}/include/)
target_link_libraries(ex5.2 PRIVATE absl::base absl::strings fmt::fmt)