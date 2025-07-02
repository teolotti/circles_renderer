//
// Created by matteo on 27/06/25.
//

#include <vector>
#include <numeric>
#include <algorithm>
#include <omp.h>
#include <iostream>
#include <random>
#include "CircleSoAUtilsParallel.h"

void CircleSoAUtilsParallel::generateCircles() {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distributionX(0.0, width);
    std::uniform_real_distribution<double> distributionY(0.0, height);
    std::uniform_real_distribution<double> distributionZ(0.0, 1.0);
    std::uniform_real_distribution<double> distributionR(10.0, 100.0);
    std::uniform_real_distribution<double> distributionRGB(0.0, 1.0);

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < this->n; i++) {
            double x = distributionX(generator);
            double y = distributionY(generator);
            double z = distributionZ(generator);
            double r = distributionR(generator);
            double red = distributionRGB(generator);
            double green = distributionRGB(generator);
            double blue = distributionRGB(generator);

            circles->setX(i, x);
            circles->setY(i, y);
            circles->setZ(i, z);
            circles->setR(i, r);
            circles->setRed(i, red);
            circles->setGreen(i, green);
            circles->setBlue(i, blue);
        }
    }
}

void CircleSoAUtilsParallel::renderCircles() {
    // Costruisce un array di indici ordinati per z crescente
    std::vector<int> sortedIndices;
    sortedIndices.resize(circles->getSize());
    std::iota(sortedIndices.begin(), sortedIndices.end(), 0);
    std::sort(sortedIndices.begin(), sortedIndices.end(),
              [this](int a, int b) {
                  return circles->getZ(a) < circles->getZ(b);
              });

    #pragma omp parallel for collapse(2)
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            double px = x + 0.5;
            double py = y + 0.5;

            double r = 1.0, g = 1.0, b = 1.0;
            for (int i : sortedIndices) {
                if (isInsideCircle(px, py, i)) {
                    r = alpha * circles->getRed(i) + (1 - alpha) * r;
                    g = alpha * circles->getGreen(i) + (1 - alpha) * g;
                    b = alpha * circles->getBlue(i) + (1 - alpha) * b;
                }
            }
            imgR[x][y] = r;
            imgG[x][y] = g;
            imgB[x][y] = b;
        }
    }
}
