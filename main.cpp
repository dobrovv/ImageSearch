#include "MonoPixmap.h"

int main() {
    MonoPixmap m;
    m = MonoPixmap(3, 3, new Byte[3*3]);
    m.setPixel(0,0,1);
    m.setPixel(1,0,5);
    m.setPixel(0,1,3);
    m.setPixel(1,1,4);

    std::cout << m.toString();

}
