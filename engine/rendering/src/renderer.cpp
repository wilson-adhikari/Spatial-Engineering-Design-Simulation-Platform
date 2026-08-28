#include "rendering/renderer.h"
#include "rendering/material.h"
namespace spatial::rendering{
class NullRenderer : public IRenderer{
public:
 bool init(void*) override {return true;}
 void shutdown() override {}
 void begin_frame() override {}
 void draw_scene(const scene::Scene&) override { stats_.draw_calls=1;}
 void end_frame() override {}
 RenderStats stats() const override {return stats_;}
private:
 RenderStats stats_{};
};
std::unique_ptr<IRenderer> create_renderer(Backend){ return std::make_unique<NullRenderer>();}
}
