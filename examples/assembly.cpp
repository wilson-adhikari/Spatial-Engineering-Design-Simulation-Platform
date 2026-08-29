#include "cad/assembly.h"
int main(){ auto a=std::make_shared<spatial::cad::Assembly>(); auto p=spatial::cad::make_box_part(5,5,5); a->add_part(p, {}); return 0; }
