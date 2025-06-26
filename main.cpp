#include <iostream>
#include <omp.h>
#include "CircleUtils.h"
#include "CircleSoAUtils.h"
#include "CircleUtilsParallel.h"


//sort parallelo
//render parallelo
//SoA
int main() {
    CircleUtils circleUtils(600, 600, 1000);
    circleUtils.generateCircles();
    circleUtils.renderCircles();
    circleUtils.savePPM("output.ppm");
    std::cout << "Circles rendered and saved to output.ppm" << std::endl;

    //CircleSoAUtils circleSoAUtils(600, 600, 1000);

    CircleUtilsParallel circleUtilsParallel(600, 600, 1000);
    circleUtilsParallel.generateCircles();
    circleUtilsParallel.renderCircles();
    circleUtilsParallel.savePPM("output_parallel.ppm");
    int nthreads = 0;
#ifdef _OPENMP
    nthreads = omp_get_max_threads();
#endif
    std::cout << "Using " << nthreads << " threads for parallel rendering." << std::endl;

    std::cout << "Parallel circles rendered and saved to output_parallel.ppm" << std::endl;
}

