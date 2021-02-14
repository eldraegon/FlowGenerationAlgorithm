#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <stdlib.h>

using namespace std;

typedef vector<vector<int>> vvi;
typedef vector<vector<bool>> vvb;
typedef vector<pair<int,int>> vpi;
#define F first
#define S second
const vpi diff = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct Node {
    int i, j, n;
    Node(int i, int j, int n) : i(i), j(j), n(n) {}
};

vvi board;
vvb visited;
vpi start_pos;
queue<Node> q;
int s;

void print_board() {
    for(auto &iit : board) {
        for(auto it : iit) {
            cout << it << " ";
        }
        cout << "\n";
    }
}

int random(int L, int H) {
    return L + (rand() % (H - L + 1));
}

bool check_within_bounds(const pair<int, int> p, int x, int y) {
    int dx = p.F + x, dy = p.S + y;
    if(dx >= 0 && dx < s && dy >= 0 && dy < s) return true;
    return false;
}

bool check_start_node(int x, int y) {
    if(visited[x][y]) return false;
    for(auto it : diff) {
        if(check_within_bounds(it, x, y) && visited[x + it.F][y + it.S]) {
            return false;
        }
    }
    return true;
}

void generate_start_nodes() {
    start_pos.resize(s/2);
    for(int i = 0; i < s/2; i++) {
        int rand_x = random(0, s-1);
        int rand_y = random(0, s-1);
        while(!check_start_node(rand_x, rand_y)) { // Generate random numbers
            rand_x = random(0, s-1);
            rand_y = random(0, s-1);
        }
        start_pos[i] = {rand_x, rand_y};
        visited[rand_x][rand_y] = true;
        board[rand_x][rand_y] = i+1; //the index of start_positions coordinate is its assigned number.
    }
}

void generate_flow_board() {
    board.resize(s, vector<int>(s));
    visited.resize(s, vector<bool>(s));
    generate_start_nodes();
    for(int i = 0; i < s/2; i++) {
        q.emplace(Node(start_pos[i].F, start_pos[i].S, i));
    }
    print_board();
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cerr << argv[0] << ": Board size required!";
        return 1;
    }
    if(!sscanf(argv[1], "%d", &s)) {
        cerr << argv[0] << ": Invalid number!";
        return 1;
    }
    generate_flow_board();
    return 0;
}