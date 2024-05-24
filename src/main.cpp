#include <iostream>
#include <thread>

//#include "src/Crawler.h"


int main() {
    // get CPU core count
    const auto processor_count = std::thread::hardware_concurrency();

    std::cout << "Hello, World! with "<< processor_count<<" CPU cores!" << std::endl;
    return 0;
}