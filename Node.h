//
// Created by fspea on 2/12/2019.
//

#ifndef STACKGAME_NODE_H
#define STACKGAME_NODE_H

#include <vector>
#include <stdlib.h>
#include <cmath>
#include <iostream>

using namespace std;

class Node {

private:
    bool terminal = false;
    int terminal_sum;

public:
    struct State {
        unsigned long long light = 0ULL;
        unsigned long long dark = 0ULL;
        bool turn = true;
    };

    double uct_score;

    int wins = 0;
    int visits = 0;
    Node *parent;
    int last_move;
    int terminal_value;
    int terminal_depth;
    vector<int> all_moves;
    vector<int> to_expand;
    vector<Node*> children;
    State board;

    Node(Node *parent, int move);

    void update(int value);
    void set_terminal(bool terminal);
    void set_terminal_value(int terminal_value, int depth);
    vector<Node*> get_children();
    int get_last_move();
    Node* get_child(int move);
    Node(Node::State s, vector<int> moves);
    int get_random_move();
    Node make_move(int move);
    bool is_expandable();
    double uct();
    Node select_child();
    bool is_terminal();

};


#endif //STACKGAME_NODE_H
