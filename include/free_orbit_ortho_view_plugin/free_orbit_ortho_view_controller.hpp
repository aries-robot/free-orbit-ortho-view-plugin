#ifndef FREE_ORBIT_ORTHO_VIEW_PLUGIN__FREE_ORBIT_ORTHO_VIEW_CONTROLLER_HPP_
#define FREE_ORBIT_ORTHO_VIEW_PLUGIN__FREE_ORBIT_ORTHO_VIEW_CONTROLLER_HPP_

#include "rviz_default_plugins/view_controllers/orbit/orbit_view_controller.hpp"

namespace rviz_common
{
class ViewportMouseEvent;

namespace properties
{
class FloatProperty;
}  // namespace properties
}  // namespace rviz_common

namespace free_orbit_ortho_view_plugin
{

// RViz ViewController that reuses Orbit controls and swaps the camera to orthographic projection.
class FreeOrbitOrthoViewController
  : public rviz_default_plugins::view_controllers::OrbitViewController
{
public:
  FreeOrbitOrthoViewController() = default;
  ~FreeOrbitOrthoViewController() override = default;

  // Configure the camera after the base Orbit controller creates its properties and scene nodes.
  void onInitialize() override;

protected:
  // Use wheel zoom to edit orthographic scale instead of moving the camera.
  void handleWheelEvent(rviz_common::ViewportMouseEvent & event, float distance) override;

  // Use right-button vertical drag to edit orthographic scale instead of moving the camera.
  void handleRightClick(
    rviz_common::ViewportMouseEvent & event,
    float distance,
    int32_t diff_y) override;

  // Keep Orbit's camera pose logic, then enforce orthographic projection and scale.
  void updateCamera() override;

private:
  // Clamp and store the orthographic scale property.
  void setOrthoScale(float scale);

  // Apply the orthographic projection settings to the Ogre camera.
  void updateOrthographicProjection();

  rviz_common::properties::FloatProperty * ortho_scale_property_{nullptr};
};

}  // namespace free_orbit_ortho_view_plugin

#endif  // FREE_ORBIT_ORTHO_VIEW_PLUGIN__FREE_ORBIT_ORTHO_VIEW_CONTROLLER_HPP_
