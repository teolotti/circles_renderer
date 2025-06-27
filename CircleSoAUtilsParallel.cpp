//
// Created by matteo on 27/06/25.
//

#include <vector>
#include <numeric>
#include <algorithm>
#include <omp.h>
#include <iostream>
#include "CircleSoAUtilsParallel.h"

void CircleSoAUtilsParallel::renderCircles() {
    // Costruisce un array di indici ordinati per z crescente
    std::vector<int> sortedIndices;
    sortedIndices.resize(circles->getSize());
    std::iota(sortedIndices.begin(), sortedIndices.end(), 0);
    std::sort(sortedIndices.begin(), sortedIndices.end(),
              [this](int a, int b) {
                  return circles->getZ(a) < circles->getZ(b);
              });

    double startTime = omp_get_wtime();

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
    double endTime = omp_get_wtime();
    std::cout << "Rendering time - Parallel SoA: " << endTime - startTime << " seconds." << std::endl;
}
