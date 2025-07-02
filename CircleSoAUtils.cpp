//
// Created by matteo on 28/03/25.
//

#include <random>
#include <algorithm>
#include <fstream>
#include <omp.h>
#include <iostream>
#include "CircleSoAUtils.h"


void CircleSoAUtils::generateCircles() {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distributionX(0.0, width);
    std::uniform_real_distribution<double> distributionY(0.0, height);
    std::uniform_real_distribution<double> distributionZ(0.0, 1.0);
    std::uniform_real_distribution<double> distributionR(10.0, 100.0);
    std::uniform_real_distribution<double> distributionRGB(0.0, 1.0);

    for (int i = 0; i < this->n; i++) {
        circles->setX(i, distributionX(generator));
        circles->setY(i, distributionY(generator));
        circles->setZ(i, distributionZ(generator));
        circles->setR(i, distributionR(generator));
        circles->setRed(i, distributionRGB(generator));
        circles->setGreen(i, distributionRGB(generator));
        circles->setBlue(i, distributionRGB(generator));
    }

}

void CircleSoAUtils::renderCircles() {
    // Costruisce un array di indici ordinati per z crescente
    std::vector<int> sortedIndices;
    sortedIndices.resize(circles->getSize());
    std::iota(sortedIndices.begin(), sortedIndices.end(), 0);
    std::sort(sortedIndices.begin(), sortedIndices.end(),
              [this](int a, int b) {
                  return circles->getZ(a) < circles->getZ(b);
              });

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

bool CircleSoAUtils::isInsideCircle(double px, double py, int index) {
    double dx = px - circles->getX(index);
    double dy = py - circles->getY(index);
    return (dx * dx + dy * dy) <= (circles->getR(index) * circles->getR(index));
}

void CircleSoAUtils::savePPM(const std::string &filename) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    file << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int r = static_cast<int>(imgR[x][y] * 255);
            int g = static_cast<int>(imgG[x][y] * 255);
            int b = static_cast<int>(imgB[x][y] * 255);
            file << r << " " << g << " " << b << " ";
        }
        file << "\n";
    }
    file.close();
}
