#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

int main() {
    long long int n;
    std::cin >> n;

    for( long long i = 2; i * i <= n; ++i ) {
        if ( n % i == 0 ) {
            if (i + (n / i) == n) {
                if (n == i * i) {
                    std::cout << 1 << '\n';
                    std::cout << i << ' ' << 2;
                } else {
                    std::cout << 2 << '\n';
                    std::cout << i << ' ' << 1 << '\n';
                    std::cout << n / i << ' ' << 1;
                }
            } else {
                if (n == i * i) {
                    std::cout << 2 << '\n';
                    std::cout << i << ' ' << 2 << '\n';
                    std::cout << 1 << ' ' << (n - i - (n / i));
                } else {
                    std::cout << 3 << '\n';
                    std::cout << i << ' ' << 1 << '\n';
                    std::cout << n / i << ' ' << 1 << '\n';
                    std::cout << 1 << ' ' << (n - i - (n / i));
                }
            }
            return 0;
        }
    }

    std::cout << -1;
}
