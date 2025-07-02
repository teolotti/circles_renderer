#include <iostream>
#include <omp.h>
#include <fstream>
#include "CircleUtils.h"
#include "CircleSoAUtils.h"
#include "CircleUtilsParallel.h"
#include "CircleSoAUtilsParallel.h"


//sort parallelo
//render parallelo
//SoA

int const NUM_MEASUREMENTS = 30;
int const MAX_THREADS = 12;


struct times {
    int numCircles;
    bool isParallel;
    // isParallel is 1 for parallel, 0 for sequential
    bool AoS; // AoS or SoA
    int nthreads;
    double time;
};

std::vector<times> sequentialAoSPipeline(int width, int height, int n) {
    std::vector<times> results;
    double elapsedTime = 0.0;
    for (int i = 0; i < NUM_MEASUREMENTS; i++) {
        CircleUtils circleUtils(width, height, n);
        circleUtils.generateCircles();
        double startTime = omp_get_wtime();
        circleUtils.renderCircles();
        double endTime = omp_get_wtime();
        if(i == 0) {
            circleUtils.savePPM("output_AoS_sequential.ppm");
        }
        elapsedTime += (endTime - startTime);
    }
    double averageTime = elapsedTime / NUM_MEASUREMENTS;
    times t = {n, false, true, 1, averageTime};
    results.push_back(t);
    return results;
}

std::vector<times> parallelAoSPipeline(int width, int height, int n) {
    std::vector<times> results;

    for (int j= 2; j <= MAX_THREADS; j++) {
        double elapsedTime = 0.0;
        omp_set_num_threads(j);
        std::cout << "Using " << j << " threads for parallel rendering." << std::endl;
        for (int i = 0; i < NUM_MEASUREMENTS; i++) {
            CircleUtilsParallel circleUtils(width, height, n);
            circleUtils.generateCircles();
            double startTime = omp_get_wtime();
            circleUtils.renderCircles();
            double endTime = omp_get_wtime();
            if(i == 0 && j == 2) {
                circleUtils.savePPM("output_AoS_parallel.ppm");
            }
            elapsedTime += (endTime - startTime);
        }
        double averageTime = elapsedTime / NUM_MEASUREMENTS;
        times t = {n, true, true, j, averageTime};
        results.push_back(t);
    }
    return results;
}

std::vector<times> sequentialSoAPipeline(int width, int height, int n) {
    std::vector<times> results;
    double elapsedTime = 0.0;
    for (int i = 0; i < NUM_MEASUREMENTS; i++) {
        CircleSoAUtils circleSoAUtils(width, height, n);
        circleSoAUtils.generateCircles();
        double startTime = omp_get_wtime();
        circleSoAUtils.renderCircles();
        double endTime = omp_get_wtime();
        if(i == 0) {
            circleSoAUtils.savePPM("output_SoA_sequential.ppm");
        }
        elapsedTime += (endTime - startTime);
    }
    double averageTime = elapsedTime / NUM_MEASUREMENTS;
    times t = {n, false, false, 1, averageTime};
    results.push_back(t);
    return results;
}

std::vector<times> parallelSoAPipeline(int width, int height, int n) {
    std::vector<times> results;

    for (int j= 2; j <= MAX_THREADS; j++) {
        double elapsedTime = 0.0;
        omp_set_num_threads(j);
        std::cout << "Using " << j << " threads for parallel rendering." << std::endl;
        for (int i = 0; i < NUM_MEASUREMENTS; i++) {
            CircleSoAUtilsParallel circleSoAUtils(width, height, n);
            circleSoAUtils.generateCircles();
            double startTime = omp_get_wtime();
            circleSoAUtils.renderCircles();
            double endTime = omp_get_wtime();
            if(i == 0 && j == 2) {
                circleSoAUtils.savePPM("output_SoA_parallel.ppm");
            }
            elapsedTime += (endTime - startTime);
        }
        double averageTime = elapsedTime / NUM_MEASUREMENTS;
        times t = {n, true, false, j, averageTime};
        results.push_back(t);
    }
    return results;
}

void timesToCSV(const std::vector<times>& results, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    file << "numCircles,isParallel,AoS,nthreads,time\n";
    for (const auto& t : results) {
        file << t.numCircles << ","
             << (t.isParallel ? "1" : "0") << ","
             << (t.AoS ? "1" : "0") << ","
             << t.nthreads << ","
             << t.time << "\n";
    }
    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}


int main() {
    int width = 800;
    int height = 800;

    std::vector<times> resultsSequential;
    std::vector<times> resultsParallel;

    std::vector<times> results;

    results = sequentialAoSPipeline(width, height, 500);
    resultsSequential.insert(resultsSequential.end(), results.begin(), results.end());
    std::cout << "500 Aos seq" << std::endl;
    results = sequentialAoSPipeline(width, height, 1000);
    resultsSequential.insert(resultsSequential.end(), results.begin(), results.end());
    std::cout << "1000 Aos seq" << std::endl;
    results = sequentialAoSPipeline(width, height, 2000);
    resultsSequential.insert(resultsSequential.end(), results.begin(), results.end());
    std::cout << "2000 Aos seq" << std::endl;
    results = sequentialSoAPipeline(width, height, 500);
    resultsSequential.insert(resultsSequential.end(), results.begin(), results.end());
    std::cout << "500 SoA seq" << std::endl;
    results = sequentialSoAPipeline(width, height, 1000);
    resultsSequential.insert(resultsSequential.end(), results.begin(), results.end());
    std::cout << "1000 SoA seq" << std::endl;
    results = sequentialSoAPipeline(width, height, 2000);
    resultsSequential.insert(resultsSequential.end(), results.begin(), results.end());
    std::cout << "2000 SoA seq" << std::endl;

    timesToCSV(resultsSequential, "results_sequential.csv");

    std::cout << "Sequential results saved to results_sequential.csv" << std::endl;

    results = parallelAoSPipeline(width, height, 500);
    resultsParallel.insert(resultsParallel.end(), results.begin(), results.end());
    std::cout << "500 Aos parallel" << std::endl;
    results = parallelAoSPipeline(width, height, 1000);
    resultsParallel.insert(resultsParallel.end(), results.begin(), results.end());
    std::cout << "1000 Aos parallel" << std::endl;
    results = parallelAoSPipeline(width, height, 2000);
    resultsParallel.insert(resultsParallel.end(), results.begin(), results.end());
    std::cout << "2000 Aos parallel" << std::endl;
    results = parallelSoAPipeline(width, height, 500);
    resultsParallel.insert(resultsParallel.end(), results.begin(), results.end());
    std::cout << "500 SoA parallel" << std::endl;
    results = parallelSoAPipeline(width, height, 1000);
    resultsParallel.insert(resultsParallel.end(), results.begin(), results.end());
    std::cout << "1000 SoA parallel" << std::endl;
    results = parallelSoAPipeline(width, height, 2000);
    resultsParallel.insert(resultsParallel.end(), results.begin(), results.end());
    std::cout << "2000 SoA parallel" << std::endl;
    timesToCSV(resultsParallel, "results_parallel.csv");
    std::cout << "Parallel results saved to results_parallel.csv" << std::endl;




    return 0;
}

