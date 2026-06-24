#include "free_orbit_ortho_view_plugin/free_orbit_ortho_view_controller.hpp"

#include <algorithm>
#include <cmath>

#include <OgreCamera.h>
#include <OgreFrustum.h>
#include <OgreViewport.h>
#include <QObject>

#include "pluginlib/class_list_macros.hpp"
#include "rviz_common/display_context.hpp"
#include "rviz_common/properties/float_property.hpp"
#include "rviz_common/viewport_mouse_event.hpp"
#include "rviz_rendering/orthographic.hpp"

namespace free_orbit_ortho_view_plugin
{

void FreeOrbitOrthoViewController::onInitialize()
{
  // Let the base Orbit controller create Target Frame, Yaw, Pitch, Distance, and Focal Point.
  rviz_default_plugins::view_controllers::OrbitViewController::onInitialize();

  // Keep Orbit's Distance positive because it still controls actual camera position.
  distance_property_->setMin(0.01F);

  // Use a separate scale property because orthographic scale and camera distance are independent.
  ortho_scale_property_ = new rviz_common::properties::FloatProperty(
    "Ortho Scale",
    8.5F,
    "Orthographic window height in meters. Smaller values zoom in.",
    this);
  ortho_scale_property_->setMin(0.01F);
  ortho_scale_property_->setMax(100.0F);

  // Re-render immediately when the scale is edited in the RViz Views panel.
  QObject::connect(
    ortho_scale_property_,
    &rviz_common::properties::Property::changed,
    [this]() {
      updateOrthographicProjection();
      emitConfigChanged();
      if (context_) {
        context_->queueRender();
      }
    });

  // Ensure the initial camera render uses orthographic projection immediately.
  updateOrthographicProjection();
}

void FreeOrbitOrthoViewController::handleWheelEvent(
  rviz_common::ViewportMouseEvent & event,
  float distance)
{
  (void)distance;

  // Match normal mouse-wheel zoom direction: wheel up reduces scale and zooms in.
  const float wheel_steps = static_cast<float>(event.wheel_delta) / 120.0F;
  const float scale_factor = std::pow(0.85F, wheel_steps);
  setOrthoScale(ortho_scale_property_->getFloat() * scale_factor);
}

void FreeOrbitOrthoViewController::handleRightClick(
  rviz_common::ViewportMouseEvent & event,
  float distance,
  int32_t diff_y)
{
  (void)event;
  (void)distance;

  // Dragging up produces a negative diff_y, so this reduces scale and zooms in.
  const float scale_factor = std::pow(1.01F, static_cast<float>(diff_y));
  setOrthoScale(ortho_scale_property_->getFloat() * scale_factor);
}

void FreeOrbitOrthoViewController::updateCamera()
{
  // Reuse Orbit's free-rotation camera pose and focal point behavior.
  rviz_default_plugins::view_controllers::OrbitViewController::updateCamera();

  // Force orthographic projection after every Orbit update in case RViz resets camera state.
  updateOrthographicProjection();
}

void FreeOrbitOrthoViewController::setOrthoScale(float scale)
{
  if (!ortho_scale_property_) {
    return;
  }

  const float clamped_scale = std::clamp(scale, 0.01F, 100.0F);
  if (ortho_scale_property_->setFloat(clamped_scale)) {
    emitConfigChanged();
  }
  updateOrthographicProjection();
  if (context_) {
    context_->queueRender();
  }
}

void FreeOrbitOrthoViewController::updateOrthographicProjection()
{
  if (!camera_ || !camera_->getViewport() || !ortho_scale_property_) {
    return;
  }

  // Orthographic window height controls visual scale; keep it positive and nonzero.
  const float viewport_width =
    static_cast<float>(camera_->getViewport()->getActualWidth());
  const float viewport_height =
    static_cast<float>(camera_->getViewport()->getActualHeight());
  if (viewport_width <= 0.0F || viewport_height <= 0.0F) {
    return;
  }

  const float ortho_height = std::max(ortho_scale_property_->getFloat(), 0.01F);
  const float ortho_width = ortho_height * viewport_width / viewport_height;
  const Ogre::Matrix4 projection = rviz_rendering::buildScaledOrthoMatrix(
    -ortho_width * 0.5F,
    ortho_width * 0.5F,
    -ortho_height * 0.5F,
    ortho_height * 0.5F,
    camera_->getNearClipDistance(),
    camera_->getFarClipDistance());

  camera_->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
  camera_->setCustomProjectionMatrix(true, projection);
}

}  // namespace free_orbit_ortho_view_plugin

PLUGINLIB_EXPORT_CLASS(
  free_orbit_ortho_view_plugin::FreeOrbitOrthoViewController,
  rviz_common::ViewController)
