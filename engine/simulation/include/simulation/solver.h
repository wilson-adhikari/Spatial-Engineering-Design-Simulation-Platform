#pragma once
#include <string>
#include <vector>
#include <functional>
#include <memory>
namespace spatial::simulation{
struct SolverResult{ bool success=false; std::string message; std::vector<double> values; double max_stress=0, max_disp=0;};
class ISolver{
public:
 virtual ~ISolver()=default;
 virtual std::string name() const =0;
 virtual SolverResult solve()=0;
 virtual void set_mesh(void* m)=0;
 virtual void set_material(void* mat)=0;
};
class SolverRegistry{
public:
 static SolverRegistry& instance();
 void register_solver(std::function<std::unique_ptr<ISolver>()> f);
 std::unique_ptr<ISolver> create(const std::string& name);
private:
 std::vector<std::function<std::unique_ptr<ISolver>()>> factories_;
};
}
