//
// Created by fspea on 2/12/2019.
//

#include "Node.h"

Node::Node(Node *parent, int move) {
    this -> parent = parent;
    last_move = move;
}
