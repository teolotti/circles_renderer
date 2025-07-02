//
// Created by matteo on 25/06/25.
//

#include <algorithm>
#include <iostream>
#include <omp.h>
#include "CircleUtilsParallel.h"

void CircleUtilsParallel::generateCircles() {
    std::default_random_engine generator;
    #pragma omp parallel num_threads(omp_get_num_threads()) private(generator)
    {
        std::vector<Circle *> localCircles;
        localCircles.reserve(n / omp_get_num_threads());

        std::uniform_real_distribution<double> distributionX(0.0, width);
        std::uniform_real_distribution<double> distributionY(0.0, height);
        std::uniform_real_distribution<double> distributionZ(0.0, 1.0);
        std::uniform_real_distribution<double> distributionR(10.0, 100.0);
        std::uniform_real_distribution<double> distributionRGB(0.0, 1.0);
        #pragma omp for schedule(static)
        for (int i = 0; i < this->n; i++) {
            double x = distributionX(generator);
            double y = distributionY(generator);
            double z = distributionZ(generator);
            double r = distributionR(generator);
            double red = distributionRGB(generator);
            double green = distributionRGB(generator);
            double blue = distributionRGB(generator);

            localCircles.push_back(new Circle(x, y, z, r, red, green, blue));
        }
        #pragma omp critical
        {
            this->circles.insert(this->circles.end(), localCircles.begin(), localCircles.end());
        }
    }
}

void CircleUtilsParallel::renderCircles() {
    std::vector<Circle *> sortedCircles = this->circles;
    std::sort(sortedCircles.begin(), sortedCircles.end(), [](Circle *a, Circle *b) {
        return a->getZ() < b->getZ();
    });

    #pragma omp parallel for collapse(2)
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            double px = x + 0.5;
            double py = y + 0.5;
            double r = 1.0, g = 1.0, b = 1.0;
            for (int i = 0; i < sortedCircles.size(); i++) {
                Circle *circle = sortedCircles[i];
                if (isInsideCircle(px, py, i)) {
                    r = alpha * circle->getRed() + (1 - alpha) * r;
                    g = alpha * circle->getGreen() + (1 - alpha) * g;
                    b = alpha * circle->getBlue() + (1 - alpha) * b;
                }
            }
            imgR[x][y] = r;
            imgG[x][y] = g;
            imgB[x][y] = b;
        }
    }
}
