//
// Created by fspea on 2/13/2019.
//

#ifndef TESTING_NODE_H
#define TESTING_NODE_H

#include <vector>

using namespace std;

class Node {

public:
    vector<Node*> children;
    vector<int> all_moves;
    vector<int> to_expand;

    int last_move = -1;
    int terminal_value = -1;
    int terminal_depth = -1;
    bool terminal = false;
    int terminal_sum = 0;

    Node* parent;

    bool turn = true;
    uint64_t light = 0b0;
    uint64_t dark = 0b0;

    Node();
    Node(Node &p, int move);
    Node make_move(int move);
    double uct();
    Node* select_child();
    bool is_expandable();
    bool is_terminal();
    void update(int value);
    void set_terminal(bool terminal);
    void set_terminal_value(int terminal_value, int depth);
    int get_random_move();
    Node(uint64_t l, uint64_t  d, bool t, vector<int>& moves);

private:
    int visits = 0;
    int wins = 0;
};


#endif //TESTING_NODE_H
