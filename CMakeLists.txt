cmake_minimum_required(VERSION 3.8)
project(auto_utest)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_gtest REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

add_library(my_lib SHARED
  src/publisher_node.cpp
)

ament_target_dependencies(my_lib
  rclcpp
  std_msgs
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  #set(ament_cmake_cpplint_FOUND TRUE)
  set(ament_cmake_lint_cmake_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(unit_test_publisher
    test/unit_test_publisher_node.cpp
  )
  target_link_libraries(unit_test_publisher
    my_lib
  )
  ament_target_dependencies(unit_test_publisher
    rclcpp
    std_msgs
  )

endif()


# Add compiler options for coverage
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
  endif()
endif()

# Custom target for coverage report
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_custom_target(
    coverage
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage_html_report
    # Capture coverage data
    COMMAND lcov --directory ${CMAKE_BINARY_DIR} --capture --output-file ${CMAKE_BINARY_DIR}/coverage.info
    # Remove unwanted files from coverage (system and external libraries)
    COMMAND lcov --remove ${CMAKE_BINARY_DIR}/coverage.info '/usr/*' '/opt/ros/*' '*/gtest/*' '*/test/*' --output-file ${CMAKE_BINARY_DIR}/coverage_filtered.info
    # Generate HTML report
    COMMAND genhtml ${CMAKE_BINARY_DIR}/coverage_filtered.info --output-directory ${CMAKE_BINARY_DIR}/coverage_html_report
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating coverage report"
  )
endif()

ament_package()