//
// Created by matteo on 28/03/25.
//

#ifndef CIRCLES_RENDERER_UTILS_H
#define CIRCLES_RENDERER_UTILS_H

#include <string>

class Utils {
public:
    virtual void generateCircles() = 0;
    virtual void renderCircles() = 0;
    virtual bool isInsideCircle(double px, double py, int index) = 0;
    virtual void savePPM(const std::string& filename) = 0;
};
#endif //CIRCLES_RENDERER_UTILS_H
