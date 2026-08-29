#include "cad/primitives.h"
#include "io/formats.h"
int main(){ auto p=spatial::cad::make_box_part(10,10,10); auto m=p->build(); spatial::io::export_stl(m, "box.stl"); return 0; }
