#include <iostream>
#include "node.h"
#include "game.h"

using namespace std;

int main() {

    uint64_t l = 0b0;
    uint64_t d = 0b0;
    vector<int> moves = Game::get_moves(l, d);
    Node root(l, d, true, moves);

    int max_depth = 0;
    int it = 0;

    Node node = root;
    while(it < 17){

        it++;

        int depth = 0;


        for(Node* n: node.children){
            cout << n->parent<< " ";

        }

        for(int i = 0; i < node.children.size(); i++){
            cout << node.children[i] -> parent << " ";
        }

        cout << endl;
        while(!node.is_expandable()){ // O(1)

            node = *node.select_child(); // O(n) n = 16
            depth++;
            if(node.is_terminal()){ // if is terminal O(1)
                break;
            }
        }
        if(depth > max_depth){
            max_depth = depth;
        }
        if(node.parent != nullptr){
            if(node.is_terminal()){ // recall value O(1)
                node.update(node.terminal_value); // O(1)
                continue;
            }
        }
        Node expanded = node.make_move(node.get_random_move()); // get is O(n)


        //Game::print_board(expanded.light, expanded.dark);

        int result = Game::result(expanded.light, expanded.dark);
        //cout << result << endl;

        if(result != -1){
            expanded.set_terminal(true);
            expanded.set_terminal_value(result, 1);
        } else {
            result = Game::simulate(expanded.light, expanded.dark, expanded.turn);
            //cout << "Result: " << result;
        }
        //Game::print_board(expanded.light, expanded.dark);
        cout << "k: " << expanded.parent << endl;
        expanded.update(result);
        cout << "k: " << expanded.parent << endl;

    }

    return max_depth;
}