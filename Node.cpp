//
// Created by fspea on 2/12/2019.
//

#include "Node.h"

Node::Node(Node* parent, int move) {

    this -> parent = parent;
    last_move = move;


    /*
    cout << this << endl;
    cout << last_move << endl;
    cout << parent << endl;
     */

    for(int i: parent -> all_moves){
        if(i != move) all_moves.push_back(i);
    }

    to_expand = all_moves;

    board = parent -> board;
}

void Node::update(int value) {
    //cout << endl << "update" << endl;
    wins += value;
    visits++;

    if(parent != nullptr) parent->update(value);
}

Node* Node::select_child() {
    //cout << "start select child" << endl;
    //cout << this << endl;


    Node* best_node = children[0];
    double best_score = children[0] -> uct();


    if(!board.turn){

        best_score++;
        for(Node* n: children){
            double uct = n -> uct();
            if(uct <= best_score){
                best_node = n;
                best_score = uct;
            }
        }
    } else {
        best_score--;
        for(Node* n: children){

            double expand = std::sqrt(3.0 * std::log(double(n->parent->visits))/double(n->visits));
            if(n->board.turn) expand *= -1.0;
            double uct = double(n->wins)/double(n->visits) + expand;


            if(uct >= best_score){
                best_node = n;
                best_score = uct;
            }
        }
    }
    //cout << best_node << endl;
    //cout << "end select child" << endl;
    return best_node;
}

double Node::uct(){
    double expand = std::sqrt(3.0 * std::log(double(parent->visits))/double(this->visits));
    if(board.turn) expand *= -1.0;
    return double(this->wins)/double(this->visits) + expand;
}

bool Node::is_expandable() {
    return !to_expand.empty();
}

Node* Node::make_move(int move) {
    Node* creation = new Node(this, move);

    if(move < 48){
        int new_move = move + 16;
        creation->to_expand.push_back(new_move);
        creation->all_moves.push_back(new_move);
    }

    if(board.turn) creation->board.light |= (1ULL << move);
    else creation->board.dark |= (1ULL << move);

    creation->board.turn = !this -> board.turn;
    children.push_back(creation);
    to_expand.pop_back();
    return creation;
}

int Node::get_random_move() {
    int index = rand() % to_expand.size();
    int move = to_expand[index];
    to_expand[index] = to_expand.back();
    return move;
}

Node::Node(Node::State s, vector<int> const moves) {
    board = s;
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

        if(parent -> board.turn){
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

bool Node::is_terminal() {
    return terminal;
}


