#include <cstddef>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

/*
* What's the strategy for reading in the pyramid?
* Requirements:
* read in one line at a time. each number should be initialized into a Node that has a single parent (non-null)
*  and two null children.
*/

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
        max_path = val_n;
    }
};

struct Pyramid {
    vector<vector<Node>> vect;
    int num_nodes;

    Pyramid(string file_name) {

        ifstream fin(file_name);
        if (!fin.is_open()) {
            cerr << "Unable to open" << file_name << '\n';
            exit(1);
        }
        string val,line;
        vector<Node> curr_row;
        while (getline(fin,line)) {
            // we'll process one line at a time, so we can maintain the previous line as well
            stringstream ss;
            ss << line;
            // below is the actual processing of each value
            while (ss >> val) {
                int num = stoi(val); // shouldn't have to worry about stoi returning errors
                Node node = Node(num);
                curr_row.push_back(node);
                this->num_nodes++;
            }
            this->vect.push_back(curr_row);
            curr_row.clear();
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

    void output_max_path() {
        for (vector<Node> vect : this->vect) {
            for (Node node : vect) {
                cout << node.max_path << " ";
            }
            cout << '\n';
        }
    }
};

// helper function to compare max_max_path to other vals
void check_val(int& max_max_path, int& val) {
    if (val > max_max_path) {
        max_max_path = val;
    }
}

int max_path(Pyramid& pyramid) {
    vector<Node> prev_row = {};

    int max_max_path = 0;
    for (vector<Node>& curr_row : pyramid.vect) {
        // this will only run on the first line, initializes all the values
        if (prev_row.empty()) {
            prev_row = curr_row;
            pyramid.vect[0][0].max_path = pyramid.vect[0][0].val;
            max_max_path = pyramid.vect[0][0].val;
            continue;
        }

        for (size_t i = 0;i<prev_row.size() - 1;i++) {
            // this logic handles the middle, and the edges and fixed afterwards
            if (prev_row[i].max_path > prev_row[i+1].max_path) { // increment middle by left if left is greater
                curr_row[i+1].max_path += prev_row[i].max_path;
                check_val(max_max_path,curr_row[i+1].max_path);
            }
            else { // otherwise we increment by the right
                curr_row[i+1].max_path += prev_row[i+1].max_path;
                check_val(max_max_path, curr_row[i+1].max_path);
            }
        }
        // left edge
        curr_row[0].max_path += prev_row[0].max_path;
        check_val(max_max_path, curr_row[0].max_path);

        // right edge
        curr_row[curr_row.size() - 1].max_path += prev_row[prev_row.size() - 1].max_path;
        check_val(max_max_path,curr_row[curr_row.size() - 1].max_path);
        // should be the last line of the loop, prepares for next iteration
        prev_row = curr_row;
    }
    return max_max_path;
}

int main() {
    Pyramid pyramid = Pyramid("triangle.txt");
    int max = max_path(pyramid);
    pyramid.output_max_path();
    cout << max << '\n';
    return 0;
}

/*
 * I enjoyed this problem! Took me a little while to solve it,
 * but once I got the algorithm it solved both versions of the
 * problem.
 */
