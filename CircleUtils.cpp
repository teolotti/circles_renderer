//
// Created by matteo on 26/03/25.
//

#include "CircleUtils.h"
#include <algorithm>
#include <fstream>

std::vector<Circle*> CircleUtils::generateCircles(int n) {

    std::vector<Circle*> circles;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distributionXY(0.0, 100.0);
    std::uniform_real_distribution<double> distributionZ(0.0, 1.0);
    std::uniform_real_distribution<double> distributionR(0.0, 10.0);
    std::uniform_real_distribution<double> distributionRGB(0.0, 1.0);

    for (int i = 0; i < n; i++) {
        double x = distributionXY(generator);
        double y = distributionXY(generator);
        double z = distributionZ(generator);
        double r = distributionR(generator);
        double red = distributionRGB(generator);
        double green = distributionRGB(generator);
        double blue = distributionRGB(generator);

        circles.push_back(new Circle(x, y, z, r, red, green, blue));
    }
    this->circles = circles;
    return circles;
}

void CircleUtils::renderCircles(int n) {
    std::vector<Circle*> sortedCircles = this->circles;
    std::sort(sortedCircles.begin(), sortedCircles.end(), [](Circle* a, Circle* b) {
        return a->getZ() < b->getZ();
    });

    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            double px = x + 0.5;
            double py = y + 0.5;

            double r, g, b = 1.0;
            for(auto c : sortedCircles) {
                if(isInsideCircle(px, py, *c)) {
                    r = this->alpha * c->getRed() + (1 - this->alpha) * r;
                    g = this->alpha * c->getGreen() + (1 - this->alpha) * g;
                    b = this->alpha * c->getBlue() + (1 - this->alpha) * b;
                }
            }
            imgR[x][y] = r;
            imgG[x][y] = g;
            imgB[x][y] = b;
        }
    }
}
bool CircleUtils::isInsideCircle(double px, double py, const Circle &c) {
    double dx = px - c.getX();
    double dy = py - c.getY();
    return dx * dx + dy * dy <= c.getR() * c.getR();
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


