//
// Created by fspea on 2/12/2019.
//

#include "Game.h"
#include "Node.h"
#include <random>

using namespace std;

void Game::make_move(int& move, unsigned long long int &light, unsigned long long int &dark, bool &turn) {
    if(turn){
        light |= (1ULL << move);
    } else {
        dark |= (1ULL << move);
    }
    turn = !turn;
}

void Game::print_board(unsigned long long int &light, unsigned long long int &dark) {

    for(unsigned int i = 0; i < 64; i++){
        if(i % 4 == 0) cout << endl;
        if(i % 16 == 0) cout << endl;
        if(light & (1ULL << i)) cout << "x ";
        else if(dark & (1ULL << i)) cout << "o ";
        else cout << "- ";
    }
    cout << endl;
}

bool Game::is_terminal(unsigned long long int &light, unsigned long long int &dark) {
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

int Game::result(unsigned long long int &light, unsigned long long int &dark) {
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

int Game::simulate(unsigned long long int light, unsigned long long int dark, bool turn) {
    vector<int> moves = get_moves(light, dark);

    unsigned seed = 55;
    std::mt19937 random(seed);

    while(!Game::is_terminal(light, dark)){
        int rand_int = random() % moves.size();
        int move = moves[rand_int];
        make_move(move, light, dark, turn);
        moves[rand_int] = moves.back();
        moves.pop_back();
        if(move < 48) moves.push_back(move + 16);
    }
    return 1;

}

vector<int> Game::get_moves(unsigned long long int &light, unsigned long long int &dark) {

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

int Game::runUCT(Node::State s) {
    Node* root = new Node(s, get_moves(s.light, s.dark));

    int max_depth = 0;
    int it = 0;

    Node* node = root;
    while(it < 17){

        it++;

        int depth = 0;

        /*
        cout<<it <<endl;
        for(int i = 0; i < node.children.size(); i++){
            cout << " node: " << node.children[i];
            node.children[i];
        }
        cout<<endl;
         */

        while(!node->is_expandable()){ // O(1)
            node = node->select_child(); // O(n) n = 16
            depth++;
            if(node->is_terminal()){ // if is terminal O(1)
                break;
            }

        }
        if(depth > max_depth){
            max_depth = depth;
        }
        if(node->parent != nullptr){
            if(node->is_terminal()){ // recall value O(1)
                node->update(node->terminal_value); // O(1)
                continue;
            }
        }


        Node* expanded = node->make_move(node->get_random_move()); // get is O(n)

        int result = Game::result(expanded->board.light, expanded->board.dark);

        if(result != -1){
            expanded->set_terminal(true);
            expanded->set_terminal_value(result, 1);
        } else {
            //Game::print_board(expanded.board.light, expanded.board.dark);
            result = Game::simulate(expanded->board.light, expanded->board.dark, expanded->board.turn);
            cout << "hello ";

        }
        cout << (expanded->parent) <<" ";
        cout << (expanded->parent)->parent << endl;
        expanded->update(result);



    }

    return max_depth;
}

constexpr unsigned int Game::win_list[76][4];


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
