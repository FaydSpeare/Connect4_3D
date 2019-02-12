#include <iostream>
#include "Game.h"
#include <bitset>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

int main() {

    auto start = chrono::steady_clock::now();
    vector<unsigned long long int> moves;

    for(int i = 0; i < 100000; i++){
        Game game{};
        game.simulate(1);
    }

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );

    std::cout << "milliseconds since start: " << elapsed.count( ) << '\n';

    return 0;
}