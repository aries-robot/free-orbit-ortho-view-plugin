# Free Orbit Ortho View Plugin

ROS 2 Humble RViz2 plugin that adds a free-orbit orthographic view controller.

This package keeps the normal RViz Orbit mouse controls, but renders the camera with an orthographic projection. The default `Ortho Scale` is `8.5`.

## Naming

The package name is `free_orbit_ortho_view_plugin`.

The RViz plugin class is registered as:

```text
free_orbit_ortho_view_plugin/FreeOrbitOrtho
```

This package is intended for ROS 2 Humble.

## Clone Into A Workspace

Create a ROS 2 workspace and clone this package into its `src` directory.

If you already have a ROS 2 workspace, use that workspace's `src` directory instead of `/path/to/ortho_ws/src`.

```bash
mkdir -p /path/to/ortho_ws/src
cd /path/to/ortho_ws/src
git clone https://github.com/aries-robot/free-orbit-ortho-view-plugin.git
```

The package source should be located here after cloning:

```text
/path/to/ortho_ws/src/free-orbit-ortho-view-plugin
```

## Build

Install or source ROS 2 Humble first.

```bash
source /opt/ros/humble/setup.bash
cd /path/to/ortho_ws
colcon build --symlink-install --packages-select free_orbit_ortho_view_plugin
```

Source the built workspace.

```bash
source /path/to/ortho_ws/install/setup.bash
```

## Run In RViz

Start RViz from a terminal where the plugin workspace has been sourced.

```bash
source /opt/ros/humble/setup.bash
source /path/to/ortho_ws/install/setup.bash
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
cd /path/to/ortho_ws
rosdep install --from-paths src --ignore-src -r -y --rosdistro humble
```

Build a local Debian package.

```bash
cd /path/to/ortho_ws/src/free-orbit-ortho-view-plugin
bloom-generate rosdebian --ros-distro humble
fakeroot debian/rules binary
```

The generated `.deb` file is created in the parent directory of the package source, which is `src/` in this workspace.

Install the generated package.

```bash
cd /path/to/ortho_ws/src
sudo apt install ./ros-humble-free-orbit-ortho-view-plugin_*.deb
```

After installing the Debian package, only the ROS 2 Humble environment needs to be sourced before starting RViz.

```bash
source /opt/ros/humble/setup.bash
rviz2
```
