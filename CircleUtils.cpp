//
// Created by matteo on 26/03/25.
//

#include "CircleUtils.h"
#include <algorithm>
#include <fstream>
#include <omp.h>
#include <iostream>

void CircleUtils::generateCircles() {

    std::vector<Circle*> circles;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distributionX(0.0, width);
    std::uniform_real_distribution<double> distributionY(0.0, height);
    std::uniform_real_distribution<double> distributionZ(0.0, 1.0);
    std::uniform_real_distribution<double> distributionR(10.0, 100.0);
    std::uniform_real_distribution<double> distributionRGB(0.0, 1.0);

    for (int i = 0; i < this->n; i++) {
        double x = distributionX(generator);
        double y = distributionY(generator);
        double z = distributionZ(generator);
        double r = distributionR(generator);
        double red = distributionRGB(generator);
        double green = distributionRGB(generator);
        double blue = distributionRGB(generator);

        circles.push_back(new Circle(x, y, z, r, red, green, blue));
    }
    this->circles = circles;
}

void CircleUtils::renderCircles() {
    std::vector<Circle*> sortedCircles = this->circles;
    std::sort(sortedCircles.begin(), sortedCircles.end(), [](Circle* a, Circle* b) {
        return a->getZ() < b->getZ();
    });

    double startTime = omp_get_wtime();

    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            double px = x + 0.5;
            double py = y + 0.5;

            double r, g, b = 1.0;
            for(int i=0; i<sortedCircles.size(); i++) {
                Circle* circle = sortedCircles[i];
                if(isInsideCircle(px, py, i)) {
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
    double endTime = omp_get_wtime();
    std::cout << "Rendering time - Sequential AoS: " << endTime - startTime << " seconds." << std::endl;
}
bool CircleUtils::isInsideCircle(double px, double py, int index) {
    double dx = px - circles[index]->getX();
    double dy = py - circles[index]->getY();
    return dx * dx + dy * dy <= circles[index]->getR() * circles[index]->getR();
}

void CircleUtils::savePPM(const std::string &filename) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    file << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int r = static_cast<int>(imgR[y][x] * 255);
            int g = static_cast<int>(imgG[y][x] * 255);
            int b = static_cast<int>(imgB[y][x] * 255);
            file << r << " " << g << " " << b << " ";
        }
        file << "\n";
    }
    file.close();
}


