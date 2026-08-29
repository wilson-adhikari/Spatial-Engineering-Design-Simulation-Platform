#include "io/assets.h"
#include <cassert>
int main(){
 auto m=spatial::io::AssetLoader::load_material("assets/materials/steel.json"); assert(m.has_value());
 auto t=spatial::io::AssetLoader::load_texture("assets/textures/checker_256.png"); assert(t.has_value());
 auto mod=spatial::io::AssetLoader::load_model("assets/models/primitive_box.stl"); assert(mod.has_value());
 assert(!spatial::io::AssetLoader::load_material("../evil.json").has_value());
 return 0;
}
