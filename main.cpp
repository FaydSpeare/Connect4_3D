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

    Node::State state;
    state.light = 0b0;
    state.dark = 0b0;
    state.turn = true;
    Node n(state, Game::get_moves(state.light, state.dark));

    while(!Game::is_terminal(state.light, state.dark)){
        int move = Game::runUCT(state, 5.0);
        if(state.turn){
            state.light |= (1ULL << move);
        } else {
            state.dark |= (1ULL << move);
        }
        state.turn = !state.turn;

        Game::print_board(state.light, state.dark);
        int c;
        cout << "enter move: " << endl;
        cin >> c;

        if(state.turn){
            state.light |= (1ULL << c);
        } else {
            state.dark |= (1ULL << c);
        }
        state.turn = !state.turn;

    }



    //auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );

    //std::cout << "milliseconds since start: " << elapsed.count( ) << '\n';

    return 0;
}
