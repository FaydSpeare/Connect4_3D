//
// Created by fspea on 2/12/2019.
//

#include "Node.h"
#include <random>

Node::Node(Node* parent, int &move) {
    this -> parent = parent;
    last_move = move;
    for(int i: parent -> all_moves){
        if(i != move) all_moves.push_back(i);
    }
    to_expand = all_moves;
    light = parent->light;
    dark = parent->dark;
    turn = parent->turn;
}

void Node::update(int &value) {
    wins += value;
    visits++;
    if(parent != nullptr) parent->update(value);
}

Node* Node::select_child() {

    Node* best_node = nullptr;
    double best_score = children[0] -> uct();

    if(!turn){
        for(Node* n: children){
            double uct = n -> uct();
            if(uct <= best_score){
                best_node = n;
                best_score = uct;
            }
        }
    } else {
        for(Node* n: children){
            double uct =  n -> uct();
            if(uct >= best_score){
                best_node = n;
                best_score = uct;
            }
        }
    }
    return best_node;
}

double Node::uct(){
    double expand = std::sqrt(2.5 * std::log(double(parent->visits))/double(this->visits));
    if(turn) expand *= -1.0;
    return double(this->wins)/double(this->visits) + expand;
}

bool Node::is_expandable() {
    return !to_expand.empty();
}

Node* Node::make_move(int move) {
    auto creation = new Node(this, move);

    if(move < 48){
        int new_move = move + 16;
        creation->to_expand.push_back(new_move);
        creation->all_moves.push_back(new_move);
    }

    if(turn) creation->light |= (1ULL << move);
    else creation->dark |= (1ULL << move);

    creation->turn = !this -> turn;
    children.push_back(creation);
    to_expand.pop_back();
    return creation;
}

int Node::get_random_move(int random) {
    short move = to_expand[random];
    to_expand[random] = to_expand.back();
    return move;
}

Node::Node(uint64_t l, uint64_t d, bool t, vector<int> const moves) {
    light = l;
    dark = d;
    turn = t;
    parent = nullptr;
    all_moves = moves;
    to_expand = all_moves;
}

void Node::set_terminal(bool terminal) {
    this -> terminal = terminal;
}

void Node::set_terminal_value(int terminal_value, int depth) {
    this -> terminal_value = terminal_value;
    terminal_depth = depth;
    terminal = true;

    if(parent != nullptr){
        depth++;

        if(parent -> turn){
            if(terminal_value == 2){
                parent -> set_terminal_value(terminal_value, depth);
            }
            else if(terminal_value == -2){
                parent -> terminal_sum += terminal_value;
                if(parent -> terminal_sum / parent -> children.size() == -2){
                    parent->set_terminal_value(terminal_value, depth);
                }
            }
        }
        else {
            if(terminal_value == -2){
                parent -> set_terminal_value(terminal_value, depth);
            }
            else if(terminal_value == 2){
                parent -> terminal_sum += terminal_value;
                if(parent -> terminal_sum / parent -> children.size() == 2){
                    parent->set_terminal_value(terminal_value, depth);
                }
            }
        }
    }

}

bool Node::is_terminal() {
    return terminal;
}


