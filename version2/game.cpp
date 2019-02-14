//
// Created by fspea on 2/13/2019.
//

#include "game.h"
#include <random>
#include <iostream>

void Game::print_board(uint64_t &light, uint64_t &dark) {

    for(unsigned int i = 0; i < 64; i++){
        if(i % 4 == 0) cout << endl;
        if(i % 16 == 0) cout << endl;
        if(light & (1ULL << i)) cout << "x ";
        else if(dark & (1ULL << i)) cout << "o ";
        else cout << "- ";
    }
    cout << endl;
}

vector<int> Game::get_moves(uint64_t &light, uint64_t &dark) {
    vector<int> moves;
    unsigned long long int empty = ~(dark | light);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 4; j++){
            int k = (i + 16*j);
            if(empty & (1ULL << k)){
                moves.push_back(k);
                break;
            }
        }
    }
    return moves;
}

bool Game::is_terminal(uint64_t &light, uint64_t &dark) {
    if(0 == ~(light | dark)) return true;

    for (auto array : win_list) {
        if (light & (1ULL << array[3]) && light & (1ULL << array[2])
            && light & (1ULL << array[1]) && light & (1ULL << array[0])) {
            return true;
        }
        if (dark & (1ULL << array[3]) && dark & (1ULL << array[2])
            && dark & (1ULL << array[1]) && dark & (1ULL << array[0])) {
            return true;
        }
    }
    return false;
}

int Game::result(uint64_t &light, uint64_t &dark) {

    for (auto array : win_list) {
        if (light & (1ULL << array[3])) {
            if (light & (1ULL << array[2])) {
                if (light & (1ULL << array[1])) {
                    if (light & (1ULL << array[0])) {
                        return 2;
                    }
                }
            }
        }
        if (dark & (1ULL << array[3])) {
            if (dark & (1ULL << array[2])) {
                if (dark & (1ULL << array[1])) {
                    if (dark & (1ULL << array[0])) {
                        return -2;
                    }
                }
            }
        }
    }
    if( ~(light | dark) == 0ULL){
        return 0;
    }

    return -1;
}

constexpr unsigned int Game::win_list[76][4];

int Game::simulate(uint64_t& light, uint64_t& dark, bool turn) {
    vector<int> moves = get_moves(light, dark);

    unsigned seed = std::random_device()();
    std::mt19937 random(seed);

    while(!Game::is_terminal(light, dark)){
        int rand_int = random() % moves.size();
        int move = moves[rand_int];
        make_move(move, light, dark, turn);
        moves[rand_int] = moves.back();
        moves.pop_back();
        if(move < 48) moves.push_back(move + 16);
    }

    return Game::result(light, dark);

}

void Game::make_move(int& move, uint64_t &light, uint64_t &dark, bool &turn) {
    if(turn){
        light |= (1ULL << move);
    } else {
        dark |= (1ULL << move);
    }
    turn = !turn;
}
