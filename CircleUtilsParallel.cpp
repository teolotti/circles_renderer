//
// Created by matteo on 25/06/25.
//

#include <algorithm>
#include "CircleUtilsParallel.h"

void CircleUtilsParallel::renderCircles() {
    std::vector<Circle*> sortedCircles = this->circles;
    std::sort(sortedCircles.begin(), sortedCircles.end(), [](Circle* a, Circle* b) {
        return a->getZ() < b->getZ();
    });

    #pragma omp parallel for collapse(2)
    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            double px = x + 0.5;
            double py = y + 0.5;

            double r = 1.0, g = 1.0, b = 1.0;
            for(int i = 0; i < sortedCircles.size(); i++) {
                Circle* circle = sortedCircles[i];
                if(isInsideCircle(px, py, i)) {
                    r = circle->getRed();
                    g = circle->getGreen();
                    b = circle->getBlue();
                }
            }
            imgR[x][y] = r;
            imgG[x][y] = g;
            imgB[x][y] = b;
        }
    }
}
