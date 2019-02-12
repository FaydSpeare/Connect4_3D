//
// Created by fspea on 2/12/2019.
//

#ifndef STACKGAME_NODE_H
#define STACKGAME_NODE_H


class Node {

private:
    bool terminal = false;
    int terminal_sum;

public:
    int wins;
    int visits;
    Node *parent;
    int last_move;
    bool terminal_value;
    int terminal_depth;

    Node(Node *parent, int move);

};


#endif //STACKGAME_NODE_H
