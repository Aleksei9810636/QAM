#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cmath>
#include <stdexcept>

class QPSK {
    size_t _size_data;
    std::vector<int> _bits;
    std::vector<std::pair<double, double>> _points;
    std::vector<std::pair<double, double>> _noise_points;
public:
    QPSK(const std::vector<int>& bits) {
        if (bits.size() % 2 != 0) {
            throw std::invalid_argument("Number of bits must be even for QPSK");
        }
        _size_data = bits.size();
        _bits = bits;
        _points.resize(_size_data / 2);

        for (unsigned i = 0; i < _points.size(); i++) {
            _points[i] = std::pair(
                bits[2*i] == 1 ? sqrt(2)/2 : -sqrt(2)/2,
                bits[2*i + 1] == 1 ? sqrt(2)/2 : -sqrt(2)/2
            );
        }
        _noise_points.resize(_points.size());
    }

    void add_noise(double sigma) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> dist(0, sigma);
        for (size_t i = 0; i < _points.size(); i++) {
            _noise_points[i] = std::pair(_points[i].first + dist(gen), _points[i].second + dist(gen));
        }
    }

    void write_points_to_file() const {
        std::ofstream file("results/points.csv");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for writing");
        }
        for (auto p : _noise_points) {
            file << p.first << ", " << p.second << "\n";
        }
    }

    unsigned count_errors() {
        unsigned errors = 0;
        for (size_t i = 0; i < _points.size(); i++) {
            int bit1 = _noise_points[i].first > 0 ? 1 : 0;
            int bit2 = _noise_points[i].second > 0 ? 1 : 0;
            
            if (bit1 != _bits[2*i]) errors++;
            if (bit2 != _bits[2*i+1]) errors++;
        }
        return errors;
    }

    double rho(const std::pair<double, double>& a, const std::pair<double, double>& b) {
        double dx = a.first - b.first;
        double dy = a.second - b.second;
        return sqrt(dx*dx + dy*dy);
    }
};

int main() {
    size_t size_data = 10'000;
    std::vector<int> bits(size_data);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_u(0, 1);
    for (auto& b : bits) b = dist_u(gen);

    std::ofstream file("results/error_sigma.csv");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    file << "sigma,errors,ber\n";

    QPSK qpsk(bits);
    for (double sigma = 0.0; sigma <= 100.0; sigma += 1) {
        qpsk.add_noise(sigma);
        unsigned errors = qpsk.count_errors();
        double ber = static_cast<double>(errors) / size_data;
        file << sigma << "," << errors << "," << ber << "\n"; 
    }

    return 0;
}