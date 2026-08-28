#pragma once
#include "scene/scene.h"
#include "rendering/material.h"
#include <memory>
namespace spatial::rendering{
enum class Backend{OpenGL,Vulkan,Software};
struct RenderStats{ uint32_t draw_calls=0, triangles=0; double frame_ms=0;};
class IRenderer{
public:
 virtual ~IRenderer()=default;
 virtual bool init(void* window_handle=nullptr)=0;
 virtual void shutdown()=0;
 virtual void begin_frame()=0;
 virtual void draw_scene(const scene::Scene& sc)=0;
 virtual void end_frame()=0;
 virtual RenderStats stats() const =0;
};
std::unique_ptr<IRenderer> create_renderer(Backend b=Backend::OpenGL);
}
