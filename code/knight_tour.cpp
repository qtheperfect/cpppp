/**************************************
 * Knight Tour Game on Chess board
 * Author: Linghuei Guo
 * Email: l.h.kuo@outlook.com
 * Date: Apr-22-2026
 * All Rights Reserved
 ****************************************/
#include <iostream>
#include <vector>
#include <array>
#include <format>
using std::format, std::cout, std::endl, std::vector, std::array;

const int BOARDSIZE = 6;

template<int boardsize>
class Knightour {
	int board[boardsize][boardsize];
	bool search_complete;
	unsigned long long int search_count;

public:
	Knightour(){
		for (auto &r : board)
			for (auto &p : r)
				p = -1;
		search_complete = false;
		search_count = 0;
	}

	vector<array<int, 2>> nextMoves(int current_x, int current_y) {
		int dx[] = {1,  1,  2,  2,  -1,  -1,  -2,  -2};
		int dy[] = {2, -2, -1,  1,   2,   -2,  1,  -1};
		vector<array<int, 2>> result;
		for (int i = 0; i < 8; ++i) {
			int x1 = current_x + dx[i];
			if (x1 < 0 || x1 >= boardsize) continue;
			int y1 = current_y + dy[i];
			if (y1 < 0 || y1 >= boardsize) continue;
			result.push_back({x1, y1});
		}
		return result;
	}



	bool search(int x1 = 0, int y1 = 0, int path_count = 0) {
		if (++search_count % 100000 == 0) {
			cout << "\033[2;1H";
			cout << format("step:{:15d}, path:{:<4d}, x={:<3d}, y={:<3d}   \n", search_count, path_count, x1, y1);
			display(cout);
		}

		const int totalboard = boardsize * boardsize;
		if (path_count >= totalboard) {
			if ( x1 == 0 && y1 == 0 ) {
				search_complete = true;
				return true;
			}
			else {
				return false;
			}
		}
		else if (board[x1][y1] != -1) {
			return false;
		} 

		board[x1][y1] = path_count;

		vector<array<int, 2>> nexts = nextMoves(x1, y1);
		for (auto &p : nexts) {
			int x2 = p[0], y2 = p[1];
			bool r1 = search(x2, y2, path_count + 1);
			if (r1) {
				return true;
			}
		}

		board[x1][y1] = -1;
		return false;
	}

	void display(std::ostream &c = cout) {
		c << format("\n--------------Board {0:^3d}x{0:^3d}--------------------\n", boardsize);
		for (int i = 0; i < boardsize; ++i)  {
			for (int j = 0; j < boardsize; ++j) {
				c << format(" | {:^5d}", board[i][j]);
			}
			c << " |\n";
		}
	}
	static void test() {
		Knightour<boardsize> o;
		o.search();
		o.display(cout);
	}

};

int main() {
	Knightour<BOARDSIZE>::test();
}
