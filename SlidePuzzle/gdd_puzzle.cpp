#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<map>
#include<queue>
using namespace std;

#define LIMIT 100
#define WALL '#'

#define COL 3
#define ROW 3

struct Puzzle {
    char cont[ROW*COL];	// content
    int space;			// 0 - (ROW*COL-1)
    string path;
    bool operator < ( const Puzzle &p ) const {
        for ( int i = 0; i < ROW*COL; i++ ) {
            if ( cont[i] == p.cont[i] ) continue;
            return cont[i] > p.cont[i];
        }
        return false;
    }
};

//int limit;
static const int dx[4] = {-1, 0, 1, 0};
static const int dy[4] = {0, -1, 0, 1};
static const char direction[4] = {'U', 'L', 'D', 'R'};

bool isTarget(Puzzle puzzle)
{
    for ( int i = 0; i < (ROW*COL-1); i++ ) {
        if ( puzzle.cont[i] == WALL ) continue;
        if ( puzzle.cont[i] != '1' + i ) return false;
    }
    return true;
}

void breadthFirstSearch(Puzzle s)
{
    queue<Puzzle> Q;
    map<Puzzle, bool> V;
    Puzzle u, v;
    s.path = "";
    Q.push(s);
    V[s] = true;
    
    while ( !Q.empty() ) {
        u = Q.front(); Q.pop();
        if ( isTarget(u) ) {
            cout << u.path << endl;
            return;
        } else if ( u.path.size() > LIMIT ) {
			cout << "u.path.size() > LIMIT" << endl;
			break;
		 }
		        
        int sx, sy, tx, ty;
        sx = u.space/COL;	// X coordinate of space
        sy = u.space%COL;	// Y coordinate of space
        
        for ( int r = 0; r < 4; r++ ) {
            tx = sx + dx[r];	// X coordinate of transport
            ty = sy + dy[r];	// Y coordinate of transport
            if ( tx < 0 || ty < 0 || 
				   tx >= ROW || ty >= COL ||
				   u.cont[tx*ROW+ty] == WALL
				    ) {
				continue;
			 }
            v = u;	// copy
            v.cont[u.space] = u.cont[tx*ROW+ty];
            v.cont[tx*ROW+ty] = '0';
            v.space = tx*ROW+ty;
            if ( !V[v] ) {
                V[v] = true;
                v.path += direction[r];
                Q.push(v);
            }
        }
    }
    cout << "unsolvable" << endl;
}

int main()
{
//    Puzzle in;
//    for ( int i = 0; i < (ROW*COL); i++ ) {
//        cin >> in.cont[i];
//        if ( in.cont[i] == '0' ) {
//            in.space = i;
//        }
//    }
//    
//    breadthFirstSearch(in);

	fstream file;
	
	file.open("puzzledata_edit.txt", ios::in);
	if (!file.is_open()) {
		return EXIT_FAILURE;
	}
	
	string str;
	while (getline(file, str)) {
		if (str.length() == 1) {
//			cout << endl;
		}
		else {
			Puzzle *in = new Puzzle;
			for ( int i = 0; i < (ROW*COL); i++ ) {
				in->cont[i] = str[i];
				if ( in->cont[i] == '=' ) {
				    in->cont[i] = WALL;
				}
				
				if ( in->cont[i] == '0' ) {
				    in->space = i;
				}
			}
			breadthFirstSearch(*in);
			delete(in);
		}
	}
	file.close();

	return 0;
}