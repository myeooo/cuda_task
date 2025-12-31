
#pragma once    
#include <vector>
#include "../compute/add_vector.cuh"
#include "../data_binding/vector_binding.h"
#include <random>
#include <chrono>
using namespace std;
namespace VectorAlgorithm{

void addVector2();
void addVector();
void dotProductVector();
void addVectorMultipleDims();
void scaleVectorWithConstants();
void minLengthVector();
}