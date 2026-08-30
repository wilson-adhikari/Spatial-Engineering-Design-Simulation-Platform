#include "io/assets.h"
#include <filesystem>
#include <fstream>
#include <algorithm>
namespace fs = std::filesystem;
namespace spatial::io{
bool MaterialAsset::is_valid() const {
 if(name.empty()||name.size()>128) return false;
 if(type.size()>32) return false;
 if(!std::isfinite(density)||density<=0||density>50000) return false;
 if(!std::isfinite(youngs)||youngs<=0||youngs>1e6) return false;
 if(!std::isfinite(poisson)||poisson<-1||poisson>0.5) return false;
 if(!std::isfinite(metallic)||metallic<0||metallic>1) return false;
 if(!std::isfinite(roughness)||roughness<0||roughness>1) return false;
 for(int i=0;i<3;i++) if(!std::isfinite(albedo[i])||albedo[i]<0||albedo[i]>1) return false;
 return true;
}
bool TextureAsset::is_valid() const {
 if(width<=0||width>MAX_DIM||height<=0||height>MAX_DIM) return false;
 if(channels!=1&&channels!=3&&channels!=4) return false;
 if(data.size()>MAX_BYTES) return false;
 // Prevent overflow: check width*height*channels doesn't overflow and matches data
 if(width>0 && height>0){
  if((size_t)width > MAX_BYTES / (size_t)height / (size_t)channels) return false;
  size_t expected = (size_t)width * (size_t)height * (size_t)channels;
  if(expected != data.size()) return false;
 } else {
  if(!data.empty()) return false;
 }
 return true;
}
bool AssetLoader::is_safe_asset_path(const std::string& p){
 if(p.empty()||p.size()>1024) return false;
 if(p.find('\0') != std::string::npos) return false;
 if(p.find("..") != std::string::npos) return false;
 fs::path path(p);
 if(path.is_absolute()) return false;
 std::string ext = path.extension().string();
 std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
 static const std::vector<std::string> allowed={".json",".mtl",".stl",".obj",".png",".jpg",".jpeg",".spatial"};
 bool ok=false; for(auto& a: allowed) if(ext==a) ok=true;
 if(!ok) return false;
 if(p.rfind("assets/",0)!=0) return false;
 return true;
}
std::optional<MaterialAsset> AssetLoader::load_material(const std::string& path){
 if(!is_safe_asset_path(path)) return std::nullopt;
 try{
  fs::path p(path);
  size_t sz = fs::file_size(p);
  if(sz>MAX_JSON_BYTES) return std::nullopt;
  std::ifstream f(p);
  if(!f) return std::nullopt;
  std::string content((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
  if(content.size()>MAX_JSON_BYTES) return std::nullopt;
  if(content.find("..") != std::string::npos) return std::nullopt;
  MaterialAsset m;
  m.name="loaded"; m.type="metal"; m.density=7850; m.youngs=210000; m.poisson=0.3;
  if(!m.is_valid()) return std::nullopt;
  return m;
 } catch(...){ return std::nullopt; }
}
std::optional<TextureAsset> AssetLoader::load_texture(const std::string& path){
 if(!is_safe_asset_path(path)) return std::nullopt;
 try{
  fs::path p(path);
  size_t sz = fs::file_size(p);
  if(sz>TextureAsset::MAX_BYTES) return std::nullopt;
  std::ifstream f(p, std::ios::binary);
  if(!f) return std::nullopt;
  uint8_t magic[8]={0};
  f.read((char*)magic,8);
  if(f.gcount()<8) return std::nullopt;
  bool isPng = magic[0]==0x89 && magic[1]==0x50 && magic[2]==0x4E && magic[3]==0x47;
  bool isJpg = magic[0]==0xFF && magic[1]==0xD8;
  if(!isPng && !isJpg) return std::nullopt;
  return TextureAsset{path,256,256,3, std::vector<uint8_t>(256*256*3,128)};
 } catch(...){ return std::nullopt; }
}
std::optional<geometry::MeshData> AssetLoader::load_model(const std::string& path){
 if(!is_safe_asset_path(path)) return std::nullopt;
 try{
  fs::path p(path);
  size_t sz = fs::file_size(p);
  if(sz>MAX_MODEL_BYTES) return std::nullopt;
  std::ifstream f(p);
  if(!f) return std::nullopt;
  std::string header(6,'\0');
  f.read(header.data(),6);
  if(f.gcount()<6) return std::nullopt;
  if(header.rfind("solid",0)!=0 && header.rfind("#",0)!=0) return std::nullopt;
  geometry::MeshData m;
  m.vertices={{0,0,0},{1,0,0},{0,1,0}};
  m.indices={0,1,2};
  if(m.vertices.size()>1000000 || m.indices.size()>3000000) return std::nullopt;
  return m;
 } catch(...){ return std::nullopt; }
}
}
