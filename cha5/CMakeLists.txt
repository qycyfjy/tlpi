project(Cha5FileIODetail)

add_executable(ex5.2 ex5.2.cpp ../helper.h ../helper.cpp)
target_link_libraries(ex5.2 PRIVATE absl::base absl::strings fmt::fmt)

add_executable(atomic_append atomic_append.cpp ../helper.h ../helper.cpp)
target_link_libraries(atomic_append PRIVATE absl::base absl::strings fmt::fmt)