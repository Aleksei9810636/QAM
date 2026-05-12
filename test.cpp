#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cmath>
#include <stdexcept>
    
unsigned count_errors1(double x, double y) {
    unsigned errors = 0;
        int bit1 = ((x>-1 and x<=0)or(x>=1)) ? 1 : 0;                
        int bit2 = x>0 ? 1 : 0;

        int bit3 = ((y>-1 && y<0)||(y>1)) ? 1 : 0;                
        int bit4 = y<0 ? 1 : 0;
        return bit1 *10 + bit2;
}

int main(){
    double x, y;
    while(true){
        std::cin >> x;
        std::cout << count_errors1(x, 0) << "\n";
    }
    return 0;
}