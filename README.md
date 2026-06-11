# Free Orbit Ortho View Plugin

ROS 2 Humble RViz2 plugin that adds a free-orbit orthographic view controller.

This package keeps the normal RViz Orbit mouse controls, but renders the camera with an orthographic projection. The default `Ortho Scale` is `8.5`.

## Naming

The package name is `free_orbit_ortho_view_plugin`.

This is a generic ROS 2 plugin-style name because it describes the RViz feature instead of a robot, sensor, or workspace. The RViz plugin class is registered as:

```text
free_orbit_ortho_view_plugin/FreeOrbitOrtho
```

This package is intended for ROS 2 Humble.

## Build

Install or source ROS 2 Humble first.

```bash
source /opt/ros/humble/setup.bash
cd /path/to/free_orbit_ortho_view_plugin
colcon build --packages-select free_orbit_ortho_view_plugin
```

Source the built workspace.

```bash
source /path/to/free_orbit_ortho_view_plugin/install/setup.bash
```

## Run In RViz

Start RViz from a terminal where the plugin workspace has been sourced.

```bash
source /opt/ros/humble/setup.bash
source /path/to/free_orbit_ortho_view_plugin/install/setup.bash
rviz2
```

In RViz:

1. Open the `Views` panel. If it is hidden, enable it from `Panels` > `Views`.
2. In `Current View`, open the `Type` dropdown.
3. Select `free_orbit_ortho_view_plugin/FreeOrbitOrtho`.
4. Adjust `Ortho Scale` in the `Views` panel if a different orthographic zoom level is needed.

## Controls

- Left drag: orbit around the focal point.
- Middle drag: move the focal point.
- Mouse wheel: change `Ortho Scale`.
- Right vertical drag: change `Ortho Scale`.

## Install As A Debian Package

Install the packaging tools.

```bash
sudo apt update
sudo apt install python3-bloom python3-rosdep fakeroot debhelper dh-python dpkg-dev
```

Install package dependencies.

```bash
source /opt/ros/humble/setup.bash
cd /path/to/free_orbit_ortho_view_plugin
rosdep install --from-paths src --ignore-src -r -y --rosdistro humble
```

Build a local Debian package.

```bash
cd /path/to/free_orbit_ortho_view_plugin/src/free_orbit_ortho_view_plugin
bloom-generate rosdebian --ros-distro humble
fakeroot debian/rules binary
```

The generated `.deb` file is created in the parent directory of the package source, which is `src/` in this workspace.

Install the generated package.

```bash
cd /path/to/free_orbit_ortho_view_plugin/src
sudo apt install ./ros-humble-free-orbit-ortho-view-plugin_*.deb
```

After installing the Debian package, only the ROS 2 Humble environment needs to be sourced before starting RViz.

```bash
source /opt/ros/humble/setup.bash
rviz2
```
