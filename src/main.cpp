#include <iostream>
#include <vector>
#include <random>
#include <cmath>

int main() {
    unsigned  size_data = 12;
    std::vector<int> bits(size_data);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    for (auto & b : bits) b = dist(gen);

    for(auto i:bits) std::cout << i << "\n";

    std::vector<std::pair<double, double>> points(size_data/2);
    for(unsigned i = 0; i < size_data/2; i++){
        points[i] = std::pair<double, double>(
            bits[2*i] == 1 ? sqrt(2)/2 : -sqrt(2)/2,
            bits[2*i + 1] == 1 ? sqrt(2)/2 : -sqrt(2)/2
        );
    }

    for(auto i:points) std::cout << "(" << i.first << ", " << i.second << ") \n";

    

    return 0;
}