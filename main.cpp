#include <iostream>
#include <omp.h>
#include "CircleUtils.h"
#include "CircleSoAUtils.h"
#include "CircleUtilsParallel.h"
#include "CircleSoAUtilsParallel.h"


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
    int nthreads = 0;
#ifdef _OPENMP
    nthreads = omp_get_max_threads();
#endif
    std::cout << "Using " << nthreads << " threads for parallel rendering." << std::endl;
    circleUtilsParallel.savePPM("output_parallel.ppm");
    std::cout << "Parallel circles rendered and saved to output_parallel.ppm" << std::endl;

    CircleSoAUtils circleSoAUtils(600, 600, 1000);
    circleSoAUtils.generateCircles();
    circleSoAUtils.renderCircles();
    circleSoAUtils.savePPM("output_soa.ppm");
    std::cout << "SoA circles rendered and saved to output_soa.ppm" << std::endl;

    CircleSoAUtilsParallel circleSoAUtilsParallel(600, 600, 1000);
    circleSoAUtilsParallel.generateCircles();
    circleSoAUtilsParallel.renderCircles();
    circleSoAUtilsParallel.savePPM("output_soa_parallel.ppm");
    std::cout << "SoA parallel circles rendered and saved to output_soa_parallel.ppm" << std::endl;

}

