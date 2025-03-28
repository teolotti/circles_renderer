//
// Created by matteo on 26/03/25.
//

#ifndef CIRCLES_RENDERER_CIRCLE_H
#define CIRCLES_RENDERER_CIRCLE_H


class Circle {
private:
    double x, y, z, r;
    double red, green, blue;

public:
    Circle(double x, double y, double z, double r, double red, double green, double blue):
        x(x), y(y), z(z), r(r), red(red), green(green), blue(blue) {}
    ~Circle() = default;

    double getZ() const {
        return z;
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getR() const {
        return r;
    }

    double getRed() const {
        return red;
    }

    double getGreen() const {
        return green;
    }

    double getBlue() const {
        return blue;
    }


};


#endif //CIRCLES_RENDERER_CIRCLE_H
