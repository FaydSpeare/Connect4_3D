//
// Created by fspea on 2/12/2019.
//

#ifndef STACKGAME_NODE_H
#define STACKGAME_NODE_H

#include <vector>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

class Node {

private:
    bool terminal = false;
    int terminal_sum;

public:
    uint64_t light = 0ULL;
    uint64_t dark = 0ULL;
    bool turn = true;

    int wins = 0;
    int visits = 0;
    Node *parent;
    int last_move;
    int terminal_value;
    int terminal_depth;
    vector<int> all_moves;
    vector<int> to_expand;
    vector<Node*> children;

    Node(Node *parent, int &move);

    void update(int &value);
    void set_terminal(bool terminal);
    void set_terminal_value(int terminal_value, int depth);
    Node(uint64_t light, uint64_t dark, bool turn, vector<int> moves);
    int get_random_move(int random);
    Node* make_move(int move);
    bool is_expandable();
    double uct();
    Node* select_child();
    bool is_terminal();

};


#endif //STACKGAME_NODE_H
