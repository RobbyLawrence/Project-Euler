#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

struct Node {
    int val;
    int max_path;

    // default constructor
    Node() {
        val = 0;
        max_path = 0;
    }

    // single field constructor
    Node(int val_n) {
        val = val_n;
        max_path = 0;
    }
};

struct Pyramid {
    vector<vector<Node>> vect;
    int num_nodes;

    Pyramid(string file_name) {
        /*
        * What's the strategy for reading in the pyramid?
        * Requirements:
        * read in one line at a time. each number should be initialized into a Node that has a single parent (non-null)
        *  and two null children.
        */

        ifstream fin(file_name);
        if (!fin.is_open()) {
            cerr << "Unable to open" << file_name << '\n';
            exit(1);
        }
        string val,line;
        int counter = 0;
        vector<Node> curr_row;
        while (getline(fin,line)) {
            // we'll process one line at a time, so we can maintain the previous line as well
            stringstream ss;
            double counter = 0;
            ss << line;
            // below is the actual processing of each value
            while (ss >> val) {
                int num = stoi(val); // shouldn't have to worry about stoi returning errors
                Node node = Node(num);
                curr_row.push_back(node);
                this->num_nodes++;
            }
            this->vect.push_back(curr_row);
        }
    }

    void output() {
        for (vector<Node> vect : this->vect) {
            for (Node node : vect) {
                cout << node.val << " ";
            }
            cout << '\n';
        }
    }
};

int max_path(const Pyramid& pyramid) {
    vector<int> curr_row, prev_row;
    return 0;
}

int main() {
    Pyramid pyramid = Pyramid("triangle.txt");
    pyramid.output();
    return 0;
}
