#ifndef JAMTEMPLATE_GFX_NULL_HPP
#define JAMTEMPLATE_GFX_NULL_HPP

#include <camera.hpp>
#include <graphics/gfx_interface.hpp>
#include <graphics/render_window_null.hpp>
#include <texture_manager_impl.hpp>
#include <optional>

namespace jt {
namespace null_objects {

class GfxNull : public GfxInterface {
public:
    GfxNull();
    RenderWindowInterface& window() override;
    CamInterface& camera() override;
    std::shared_ptr<RenderTarget> target() override;
    TextureManagerInterface& textureManager() override;

    void reset() override;
    void update(float elapsed) override;
    void clear() override;
    void display() override;

    void setTextureManager(jt::TextureManagerImpl& tm);

private:
    RenderWindowNull m_window;
    jt::Camera m_camera;
    std::optional<jt::TextureManagerImpl> m_textureManager;
};

} // namespace null_objects
} // namespace jt

#endif // JAMTEMPLATE_GFX_NULL_HPP
