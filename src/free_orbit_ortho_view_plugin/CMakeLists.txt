cmake_minimum_required(VERSION 3.8)
project(free_orbit_ortho_view_plugin)

# Use a modern baseline and enable useful compiler diagnostics on GCC/Clang.
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find the ROS and RViz dependencies needed by the plugin library.
find_package(ament_cmake REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_default_plugins REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)
find_package(rviz_rendering REQUIRED)

# Build one shared library containing all view-controller plugins in this package.
add_library(${PROJECT_NAME} SHARED
  src/free_orbit_ortho_view_controller.cpp
)

# Expose this package's public headers to consumers and the compiler.
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Link against RViz, Ogre, and pluginlib through ament dependency metadata.
ament_target_dependencies(${PROJECT_NAME}
  pluginlib
  rviz_common
  rviz_default_plugins
  rviz_ogre_vendor
  rviz_rendering
)

# Register this library as an RViz ViewController plugin provider.
pluginlib_export_plugin_description_file(rviz_common plugins_description.xml)

# Install the plugin library and public headers.
install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/
  DESTINATION include
)

# Install pluginlib metadata into the package share directory.
install(
  FILES plugins_description.xml
  DESTINATION share/${PROJECT_NAME}
)

# Export build metadata for downstream packages.
ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_targets(export_${PROJECT_NAME})
ament_export_dependencies(
  pluginlib
  rviz_common
  rviz_default_plugins
  rviz_ogre_vendor
  rviz_rendering
)

ament_package()
