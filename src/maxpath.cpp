#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

struct Node {
    int val;
    Node* parent;
    Node* left_child;
    Node* right_child;

    // default constructor
    Node() {
        val = 0;
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
    }

    // single field constructor
    Node(int val_n) {
        val = val_n;
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
    }

    // full constructor
    Node(int val_n, Node* parent_n, Node* left_child_n, Node* right_child_n) {
        val = val_n;
        parent = parent_n;
        left_child = left_child_n;
        right_child = right_child_n;
    }

    void set_left(Node* left_child) {
        this->left_child = left_child;
        left_child-> parent = this;
    }

    void set_right(Node* right_child) {
        this->left_child = right_child;
        right_child-> parent = this;
    }
};

struct Pyramid {
    vector<Node> vect;
    int num_nodes;
    Pyramid(vector<int>& vect) {
        /*
        * What's the strategy for reading in the pyramid?
        * Requirements:
        * read in one line at a time. each number should be initialized into a Node that has a single parent (non-null)
        *  and two null children.
        */

        ifstream fin("triangle.txt");
        string val,line;
        int counter = 0;
        vector<Node*> prev_row,curr_row;
        while (getline(fin,line)) {
            // we'll process one line at a time, so we can maintain the previous line as well
            stringstream ss;
            double counter = 0;
            ss << line;
            // below is the actual processing of each value
            while (ss >> val) {
                int num = stoi(val);
                Node node = Node(num);
                curr_row.push_back(&node);
                this->num_nodes++;
            }
            if (prev_row.empty()) { // this should only run during the first loop
                prev_row = curr_row;
                continue;
            }

            // we shouldn't have to worry about seg fault, since curr_row will always be bigger than prev_row
            for (int i = 0;i<prev_row.size();i++) {
                prev_row[i]->set_left(curr_row[i]);
                prev_row[i]->set_right(curr_row[i+1]);
            }
        }
    }

    void output() {

    }
};

int max_path(const Pyramid& pyramid) {


    return 0;
}

int main() {
    return 0;
}
