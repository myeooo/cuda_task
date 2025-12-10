
#pragma once    
#include <vector>
#include <random>
#include <chrono>
using namespace std;
struct VectorAddTest {

    int dimension;

    vector<float> input;
    vector<float> output;
    VectorAddTest(int dimension, int numberOfVectors) : dimension(dimension) {
        input.resize(numberOfVectors * dimension);
        static std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> dist(0.0f, 12.0f); 
        for (auto& v : input) {
            v = dist(rng);        
        }
        output.resize(dimension, 0.0f);
    }
};

void addVector();