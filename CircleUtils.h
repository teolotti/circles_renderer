//
// Created by matteo on 26/03/25.
//
#include <vector>
#include <random>
#include "Circle.h"

#ifndef CIRCLES_RENDERER_GENERATOR_H
#define CIRCLES_RENDERER_GENERATOR_H


class CircleUtils {
private:
    std::vector<std::vector<double>> imgR;
    std::vector<std::vector<double>> imgG;
    std::vector<std::vector<double>> imgB;
    int width;
    int height;
    std::vector<Circle*> circles;
    const double alpha = 0.5;

public:
    CircleUtils(int width, int height) : width(width), height(height) {
        imgR = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
        imgG = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
        imgB = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
    }

    std::vector<Circle*> generateCircles(int n);
    void renderCircles(int n);
    bool isInsideCircle(double px, double py, const Circle& c);
    void savePPM(const std::string& filename);




};


#endif //CIRCLES_RENDERER_GENERATOR_H
