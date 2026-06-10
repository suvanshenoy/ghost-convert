cmake_minimum_required(VERSION 3.20..4.2.3)
project(ghost-convert CXX)

include("${CMAKE_SOURCE_DIR}/cmake/options.cmake")

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_executable(${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME}
  packages
)

add_subdirectory(packages)
add_subdirectory(tests)

target_compile_options(${PROJECT_NAME}
  PRIVATE
   -Wall
   -Wextra
   -Wpedantic
   -Werror
)

target_link_options(${PROJECT_NAME}
   PRIVATE
    -fsanitize=address
    -fsanitize=leak
    -fsanitize=undefined
)

if(BUILD_FTXUI)
  message("building ftxui")
  include("${CMAKE_SOURCE_DIR}/cmake/deps/ftxui.cmake")
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
    packages
  )
endif()

if(BUILD_GTEST)
  add_executable(ghost-convert-test
    "${CMAKE_SOURCE_DIR}/tests/main_test.cpp"
  )
  message("building gtest")
  include("${CMAKE_SOURCE_DIR}/cmake/deps/gtest.cmake")
  target_link_libraries(ghost-convert-test PRIVATE
    GTest::gtest
    GTest::gtest_main
    tests
    packages
  )

  include(GoogleTest)
  gtest_discover_tests(ghost-convert-test)
endif()
