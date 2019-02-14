//
// Created by fspea on 2/13/2019.
//

#include "node.h"
#include <iostream>
#include <random>

double Node::uct() {
    double expand = std::sqrt(3.0 * std::log(double(parent -> wins))/(this -> visits));
    cout << *(&parent->wins) << endl;

    if(turn) expand *= -1.0;
    return double(wins)/double(visits) + expand;
}

Node* Node::select_child() {
    cout << "IM HERE: " << children[0] << endl;


    Node* best_node = children[0];
    double best_score = (*children[0]).uct();



    if(!turn){

        for(int i = 0; i < children.size(); i++){
            Node* child = children[i];
            double score = child -> uct();
            if(score <= best_score){
                best_node = child;
                best_score = score;
            }
        }
    } else {
        for(int i = 0; i < children.size(); i++){
            Node* child = children[i];
            double score = child -> uct();
            cout << score << " " << best_score << " " << endl;
            if(score >= best_score){
                best_node = child;
                best_score = score;
            }
        }
    }

    cout << "we got here?";
    cout << best_node;
    return best_node;
}

bool Node::is_expandable() {
    return to_expand.size() != 0;
}

bool Node::is_terminal() {
    return terminal;
}

void Node::update(int value) {
    wins += value;
    visits++;
    if(parent != nullptr) parent->update(value);
}

Node Node::make_move(int move) {
    Node creation(*this, move);

    if(move < 48){
        int new_move = move + 16;
        creation.to_expand.push_back(new_move);
        creation.all_moves.push_back(new_move);
    }

    if(turn) creation.light |= (1ULL << move);
    else creation.dark |= (1ULL << move);

    creation.turn = !this -> turn;
    children.push_back(&creation);
    to_expand.pop_back();
    return creation;
}

Node::Node(Node& p, int move) {
    parent = &p;
    last_move = move;

    for(int i: parent -> all_moves){
        if(i != move) all_moves.push_back(i);
    }

    to_expand = all_moves;

    turn = parent -> turn;
    light = parent -> light;
    dark = parent -> dark;

    cout << "k: " << (&p) << endl;

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

int Node::get_random_move() {
    std::mt19937 eng;
    std::uniform_int_distribution<> dist(0, to_expand.size()-1);
    int index = dist(eng);
    //int index = rand() % to_expand.size();
    int move = to_expand[index];
    to_expand[index] = to_expand.back();
    return move;
}

Node::Node(uint64_t l, uint64_t  d, bool t, vector<int>& moves) {
    light = l;
    dark = d;
    turn = t;
    parent = 0;
    all_moves = moves;
    to_expand = all_moves;
}

