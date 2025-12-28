#include <iostream>
#include "algorithm/vector_processing.h"
#include <vector>
#include <random>
#include <chrono>

using namespace std;

int main() {
    int numbTest = 10;
    // VectorAlgorithm::scaleVectorWithConstants();
    for (int i = 0 ; i < numbTest; i ++){
        VectorAlgorithm::scaleVectorWithConstants();
    }
    return 0;
}
