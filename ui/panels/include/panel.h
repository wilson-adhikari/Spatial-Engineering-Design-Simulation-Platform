#pragma once
#include <string>
namespace spatial::ui{ class Panel{ public: virtual ~Panel()=default; virtual std::string title() const=0; virtual void render()=0; }; }
