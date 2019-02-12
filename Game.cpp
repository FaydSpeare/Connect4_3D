//
// Created by fspea on 2/12/2019.
//

#include "Game.h"


using namespace std;

void Game::make_move(unsigned long long int& move) {
    if(turn){
        light |= move;
    } else {
        dark |= move;
    }
    turn = !turn;
}

void Game::print_board() {

    for(unsigned int i = 0; i < 64; i++){
        if(i % 4 == 0) cout << endl;
        if(i % 16 == 0) cout << endl;
        if(light & (1ULL << i)) cout << "x";
        else if(dark & (1ULL << i)) cout << "o";
        else cout << "-";
    }
    cout << endl;
}

bool Game::is_terminal() {
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

int Game::result() {
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
    return 0;
}

vector<unsigned long long int> Game::get_moves() {

    vector<unsigned long long int> moves;
    unsigned long long int empty = ~(dark | light);
    unsigned long long int j;
    for(unsigned int i = 0; i < 16; i++){

        j = (1ULL << i);
        if(empty & j){
            moves.push_back(j);
            continue;
        }
        j = (1ULL << (i+16));
        if(empty & j){
            moves.push_back(j);
            continue;
        }
        j = (1ULL << (i+32));
        if(empty & j){
            moves.push_back(j);
            continue;
        }
        j = (1ULL << (i+48));
        if(empty & j){
            moves.push_back(j);
            continue;}
    }

    return moves;
}

/*
 * Alternative get_moves()
 *
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 4; j++){
            unsigned long long int shift = 1ULL << (i + 16*j);
            if(empty & shift){
                moves.push_back(shift);
                break;
            }
        }
    }
 *
 */
