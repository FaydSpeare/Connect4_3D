#include <iostream>
#include "Game.h"
#include "Node.h"
#include <bitset>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;

int main() {

    //auto start = chrono::steady_clock::now();

    uint64_t light = 0b0;
    uint64_t dark = 0b0;
    bool turn = true;
    Node n(light, dark, turn, Game::get_moves(light, dark));

    while(!Game::is_terminal(light, dark)){
        int move = Game::runUCT(light, dark, turn, 5.0);
        if(turn){
            light |= (1ULL << move);
        } else {
            dark |= (1ULL << move);
        }
        turn = !turn;

        Game::print_board(light, dark);
        int c;
        cout << "enter move: " << endl;
        cin >> c;

        if(turn){
            light |= (1ULL << c);
        } else {
            dark |= (1ULL << c);
        }
        turn = !turn;

    }



    //auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );

    //std::cout << "milliseconds since start: " << elapsed.count( ) << '\n';

    return 0;
}
