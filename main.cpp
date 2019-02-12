#include <iostream>
#include "Game.h"
#include <bitset>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

struct State {
    unsigned long long int light = 0;
    unsigned long long int dark = 0;
    bool turn = true;
};


int main() {

    auto start = chrono::steady_clock::now( );
    int k = 0;

    vector<unsigned long long int> moves;
    std::mt19937 rng;

    for(int i = 0; i < 10000; i++){
        Game game{};

        while(!game.is_terminal()){
            moves = game.get_moves();

            std::uniform_int_distribution<std::mt19937::result_type> dist6(0,moves.size()-1);
            game.make_move(moves[dist6(rng)]);
            k++;
        }
    }

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );

    std::cout << "milliseconds since start: " << elapsed.count( ) << '\n';

    return 0;
}