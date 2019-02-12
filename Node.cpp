//
// Created by fspea on 2/12/2019.
//

#include "Node.h"

Node::Node(Node *parent, int move) {
    this -> parent = parent;
    last_move = move;


    for(int i: parent -> all_moves){
        if(i != move) all_moves.push_back(i);
    }

    to_expand = all_moves;

    board = parent -> board;
}

void Node::update(int value) {
    wins += value;
    visits++;
    if(parent != nullptr) parent->update(value);
}

Node Node::select_child() {
    Node *best_node = nullptr;
    double best_score = children[0] -> uct();

    if(!board.turn){
        for(Node* n: children){
            double uct = n -> uct();
            if(uct <= best_score){
                best_node = n;
                best_score = uct;
            }
        }
    } else {
        for(Node* n: children){
            double uct = n -> uct();
            if(uct >= best_score){
                best_node = n;
                best_score = uct;
            }
        }
    }
    return *best_node;
}

double Node::uct(){
    double expand = sqrt(3*log(parent->visits)/visits);
    if(board.turn) expand *= -1;
    return wins/visits + expand;
}

bool Node::is_expandable() {
    return !to_expand.empty();
}

Node Node::make_move(int move) {
    Node creation(this, move);

    if(move < 48){
        int new_move = move + 16;
        creation.to_expand.push_back(new_move);
        creation.all_moves.push_back(new_move);
    }

    if(board.turn) creation.board.light |= (1ULL << move);
    else creation.board.dark |= (1ULL << move);

    creation.board.turn = !this -> board.turn;
    children.push_back(&creation);
    to_expand.pop_back();
    return creation;
}

int Node::get_random_move() {
    int index = rand() % to_expand.size();
    int move = to_expand[index];
    to_expand[index] = to_expand.back();
    return move;
}

Node::Node(State s, vector<int> &moves) {
    board = s;
    this->parent = nullptr;
    all_moves = moves;
    to_expand = all_moves;
}

void Node::set_terminal(bool terminal) {
    this -> terminal = terminal;
}

void Node::set_terminal_value(bool terminal_value) {
    this -> terminal_value = terminal_value;
}

vector<Node*> Node::get_children() {
    return children;
}

int Node::get_last_move() {
    return last_move;
}

Node* Node::get_child(int move) {
    for(Node* n: children){
        if(n->last_move == move) return n;
    }
    return nullptr;
}

