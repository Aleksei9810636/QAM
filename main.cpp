#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <string>


double rho(const std::pair<double, double>& a, const std::pair<double, double>& b) {
    double dx = a.first - b.first;
    double dy = a.second - b.second;
    return sqrt(dx*dx + dy*dy);
}

class QAM{
protected:
    size_t _size_data;
    std::vector<int> _bits;
    std::vector<std::pair<double, double>> _points;
    std::vector<std::pair<double, double>> _noise_points;

public:
    void add_noise(double sigma) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> dist(0, sigma);
        for (size_t i = 0; i < _points.size(); i++) {
            _noise_points[i] = std::pair(_points[i].first + dist(gen), _points[i].second + dist(gen));
        }
    }
    void write_points_to_file(std::string name = "default") {
        std::ofstream file("results/" + name + ".csv");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for writing");
        }
        for (auto p : _noise_points) {
            file << p.first << ", " << p.second << "\n";
        }
    }
};

class QPSK: public QAM {
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

    void write_points_to_file(std::string name = "points_QPSK") {
        QAM::write_points_to_file(name);
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
};

class QAM16: public QAM{
    size_t _size_data;
    std::vector<int> _bits;
    std::vector<std::pair<double, double>> _points;
    std::vector<std::pair<double, double>> _noise_points;
public:
    QAM16(const std::vector<int>& bits) {
        if (bits.size() % 4 != 0) {
            throw std::invalid_argument("Number of bits must be multiple of 4 for QAM16");
        }
        _size_data = bits.size();
        _bits = bits;
        _points.resize(_size_data / 4);

        for (unsigned i = 0; i < _points.size(); i++) {
            _points[i] = std::pair<double, double>(_bits[4*i] + 2*_bits[4*i+1] - 1.5,_bits[4*i+2] + 2*_bits[4*i+3] - 1.5);
        }
        _noise_points.resize(_points.size());
    }

    void write_points_to_file(std::string name = "points_QAM16") {
        QAM::write_points_to_file(name);
    }

    unsigned count_errors() {
        unsigned errors = 0;
        for (size_t i = 0; i < _points.size(); i++) {
            double x = _noise_points[i].first;
            double y = _noise_points[i].second;

            int bit1 = ((x>-1 and x<=0)or(x>=1)) ? 1 : 0;                
            int bit2 = x>0 ? 1 : 0;
            int bit3 = (y>-1 && y<=0)||(y>=1) ? 1 : 0;                
            int bit4 = y>0 ? 1 : 0;

            if (bit1 != _bits[4*i]) errors++;
            if (bit2 != _bits[4*i+1]) errors++;
            if (bit3 != _bits[4*i+2]) errors++;
            if (bit4 != _bits[4*i+3]) errors++;
        }
        return errors;
    }
};

class QAM64: public QAM{
    size_t _size_data;
    std::vector<int> _bits;
    std::vector<std::pair<double, double>> _points;
    std::vector<std::pair<double, double>> _noise_points;
public:
    QAM64(const std::vector<int>& bits) {
        if (bits.size() % 6 != 0) {
            throw std::invalid_argument("Number of bits must be multiple of 6 for QAM64");
        }
        _size_data = bits.size();
        _bits = bits;
        _points.resize(_size_data / 6);

        for (unsigned i = 0; i < _points.size(); i++) {
            _points[i] = std::pair<double, double>
                (_bits[6*i] + 2*_bits[6*i+1] + 4*_bits[6*i+2],
                _bits[6*i+3] + 2*_bits[6*i+4] + 4*_bits[6*i+5]);
        }
        _noise_points.resize(_points.size());
    }

    void write_points_to_file(std::string name = "points_QAM64") {
        QAM::write_points_to_file(name);
    }

    unsigned count_errors() {
        unsigned errors = 0;
        for (size_t i = 0; i < _points.size(); i++) {
            double x = _noise_points[i].first;
            double y = _noise_points[i].second;

            int bit1 = (0.5<x && x<1.5)||(2.5<x && x<3.5)
                ||(4.5<x && x<5.5)||(6.5<x) ? 1 : 0;                
            int bit2 = ((x>5.5)||(x>1.5 && x<3.5)) ? 1 : 0;
            int bit3 = (x>=3.5) ? 1 : 0;
            int bit4 = (0.5<y && y<1.5)||(2.5<y && y<3.5)
                ||(4.5<y && y<5.5)||(6.5<y) ? 1 : 0;                
            int bit5 = ((y>5.5)||(y>1.5 && y<3.5)) ? 1 : 0;
            int bit6 = (y>=3.5) ? 1 : 0;          

            if (bit1 != _bits[6*i]) errors++;
            if (bit2 != _bits[6*i+1]) errors++;
            if (bit3 != _bits[6*i+2]) errors++;
            if (bit4 != _bits[6*i+3]) errors++;
            if (bit5 != _bits[6*i+4]) errors++;
            if (bit6 != _bits[6*i+5]) errors++;
        }
        return errors;
    }
};

int main() {
    size_t size_data = 120'000;
    std::vector<int> bits(size_data);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_u(0, 1);
    for (auto& b : bits) b = dist_u(gen);

{
    std::ofstream file_qpsk("results/error_sigma_qpsk.csv");
    if (!file_qpsk.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    file_qpsk << "sigma,errors,ber\n";
    QPSK qpsk(bits);
    for (double sigma = 0.0; sigma <= 10; sigma += 0.1) {
        qpsk.add_noise(sigma);
        unsigned errors = qpsk.count_errors();
        double ber = static_cast<double>(errors) / size_data;
        file_qpsk << sigma << "," << errors << "," << ber << "\n"; 
    }
    qpsk.add_noise(1.0);
    qpsk.write_points_to_file();
}
{
    std::ofstream file_qam16("results/error_sigma_qam16.csv");
    if (!file_qam16.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    file_qam16 << "sigma,errors,ber\n";
    QAM16 qam16(bits);
    for (double sigma = 0.0; sigma <= 10; sigma += 0.1) {
        qam16.add_noise(sigma);
        unsigned errors = qam16.count_errors();
        double ber = static_cast<double>(errors) / size_data;
        file_qam16 << sigma << "," << errors << "," << ber << "\n"; 
    }
    qam16.add_noise(1.0);
    qam16.write_points_to_file();
}
{
    std::ofstream file_qam64("results/error_sigma_qam64.csv");
    if (!file_qam64.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    file_qam64 << "sigma,errors,ber\n";
    QAM64 qam64(bits);
    qam64.add_noise(0.1);
    for (double sigma = 0.0; sigma <= 10; sigma += 0.1) {
        qam64.add_noise(sigma);
        unsigned errors = qam64.count_errors();
        double ber = static_cast<double>(errors) / size_data;
        file_qam64 << sigma << "," << errors << "," << ber << "\n"; 
    }
    qam64.add_noise(1.0);
    qam64.write_points_to_file();
}
    return 0;
}