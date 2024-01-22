project(miniocpp-test)
cmake_minimum_required(VERSION 3.10)

add_subdirectory(minio-cpp)

add_executable(get_object_url test/getObjectUrl.cpp)
target_link_libraries(get_object_url miniocpp ${S3_LIBS})

add_executable(make_bucket test/makeBucket.cpp)
target_link_libraries(make_bucket miniocpp ${S3_LIBS})