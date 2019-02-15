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

    auto start = chrono::steady_clock::now();
    double k = 10;
    Node::State state;
    state.light = 0b0;
    state.dark = 0b0;
    state.turn = true;
    Node n(state, Game::get_moves(state.light, state.dark));

    Game::runUCT(state);

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );

    std::cout << "milliseconds since start: " << elapsed.count( ) << '\n';

    return 0;
}
