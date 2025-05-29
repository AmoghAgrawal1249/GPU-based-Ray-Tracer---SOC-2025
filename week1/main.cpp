#include <iostream>
using namespace std;

int main(){
    int img_h = 256;
    int img_w = 256;
    
     cout << "P3\n";
     cout << img_w << ' ' << img_h;
     cout << "\n255\n";

     for (int j = 0; j < img_h; ++j) {
        clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;
        for (int i = 0; i < img_w; i++) {
            auto r = double(i) / (img_w-1);
            auto g = double(j) / (img_h-1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::clog << "\rDone.                 \n";
}