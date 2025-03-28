//
// Created by matteo on 28/03/25.
//

#ifndef CIRCLES_RENDERER_CIRCLESOA_H
#define CIRCLES_RENDERER_CIRCLESOA_H


class CircleSoA {
private:
    double* x;
    double* y;
    double* z;
    double* r;
    double* red;
    double* green;
    double* blue;
    int size;

public:
    CircleSoA(int size) : size(size) {
        x = new double[size];
        y = new double[size];
        z = new double[size];
        r = new double[size];
        red = new double[size];
        green = new double[size];
        blue = new double[size];

        // Initialize the arrays with zeros
        for (int i = 0; i < size; ++i) {
            x[i] = 0.0;
            y[i] = 0.0;
            z[i] = 0.0;
            r[i] = 0.0;
            red[i] = 0.0;
            green[i] = 0.0;
            blue[i] = 0.0;
        }
    }

    ~CircleSoA() {
        delete[] x;
        delete[] y;
        delete[] z;
        delete[] r;
        delete[] red;
        delete[] green;
        delete[] blue;
    }

    // Getters for the circle properties
    double getX(int index) const {
        return x[index];
    }

    double getY(int index) const {
        return y[index];
    }

    double getZ(int index) const {
        return z[index];
    }

    double getR(int index) const {
        return r[index];
    }

    double getRed(int index) const {
        return red[index];
    }

    double getGreen(int index) const {
        return green[index];
    }

    double getBlue(int index) const {
        return blue[index];
    }

    int getSize() const {
        return size;
    }

};


#endif //CIRCLES_RENDERER_CIRCLESOA_H
