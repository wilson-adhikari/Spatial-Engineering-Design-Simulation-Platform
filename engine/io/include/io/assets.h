#pragma once
#include <string>
#include <vector>
#include <optional>
#include "geometry/primitives.h"
namespace spatial::io{
struct MaterialAsset{
 std::string name;
 std::string type;
 double density=0, youngs=0, poisson=0, yield=0;
 double albedo[3]{0.7,0.7,0.7};
 double metallic=0, roughness=0.5;
 bool is_valid() const;
};
struct TextureAsset{
 std::string path;
 int width=0,height=0,channels=0;
 std::vector<uint8_t> data;
 static constexpr int MAX_DIM=8192;
 static constexpr size_t MAX_BYTES=32*1024*1024;
 bool is_valid() const;
};
class AssetLoader{
public:
 static std::optional<MaterialAsset> load_material(const std::string& path);
 static std::optional<TextureAsset> load_texture(const std::string& path);
 static std::optional<geometry::MeshData> load_model(const std::string& path);
 static bool is_safe_asset_path(const std::string& p);
 static constexpr size_t MAX_JSON_BYTES = 64*1024;
 static constexpr size_t MAX_MODEL_BYTES = 50*1024*1024;
};
}
