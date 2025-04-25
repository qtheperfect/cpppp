/***************************************************************************
      0   1   2   3   4   5   6   7 
    +---+---+---+---+---+---+---+---+
  0 |   |   |   |   |   |   |   | W |
    +---+---+---+---+---+---+---+---+
  1 |   |   | W |   |   |   |   |   |
    +---+---+---+---+---+---+---+---+
  2 | W |   |   |   |   |   |   |   |
    +---+---+---+---+---+---+---+---+
  3 |   |   |   |   |   | W |   |   |
    +---+---+---+---+---+---+---+---+
  4 |   | W |   |   |   |   |   |   |
    +---+---+---+---+---+---+---+---+
  5 |   |   |   |   | W |   |   |   |
    +---+---+---+---+---+---+---+---+
  6 |   |   |   |   |   |   | W |   |
    +---+---+---+---+---+---+---+---+
  7 |   |   |   | W |   |   |   |   |
    +---+---+---+---+---+---+---+---+

 * Discription: C++ N-Queens problem solved using different data structures. 
 * Author: Linghuei Guo
 * Contact: 6819d81b0971c2c4 (gpg) 
 * Copyright: All Rights Reserved

 ***************************************************************************/

#include <iostream>
#include <cassert>
#include <ctime>
#include <vector>
#include <array>

/**
 * Template class where the chess board is stored as the template type */
template <typename board_t>
struct NQueens {
  NQueens(int width): board_width(width) {
  } 

  virtual void make_blank_board(int width) = 0;
  virtual int read_coordinate(int r, int c) = 0;
  virtual int set_coordinate(int r, int c, int value) = 0;

  int check_row(int r, int c);
  int check_column(int r, int c);
  int check_diag1(int r, int c);
  int check_diag2(int r, int c);
  int check4directions(int r, int c);
  void print();
  bool solve();
  bool solve(int r, std::vector<int> &shuffled); // the recursive version

protected:
  int board_width;
  board_t board;
  // returns the shuffled column indices so that solve() returns a random solution
  std::vector<int> get_shuffled(); 
};


template <typename board_t>
int NQueens<board_t>::check_row(int r, int c) {
  int sum = 0;
  for (int c0 = 0; c0 < board_width; ++c0) {
    sum += read_coordinate(r, c0);
  }
  return sum;
}

template <typename board_t>
int NQueens<board_t>::check_column(int r, int c) {
  int sum = 0;
  for (int r0 = 0; r0 < board_width; ++r0) {
    sum += read_coordinate(r0, c);
  }
  return sum;
}

template <typename board_t>
int NQueens<board_t>::check_diag1(int r, int c) {
  int length = board_width, r0, c0;
  if (r >= c) {
    r0 = r - c;
    c0 = 0;
    length -= r0;
  }
  else {
    r0 = 0;
    c0 = c - r;
    length -= c0;
  }
  int sum = 0;
  for (int i = 0; i < length; ++i) {
    sum += read_coordinate(r0 + i, c0 + i);
  }
  return sum;
}

template <typename board_t>
int NQueens<board_t>::check_diag2(int r, int c) {
  int length = board_width, r0, c0;
  if (r >= board_width - 1 - c) {
    r0 = r - board_width + 1 + c;
    c0 = board_width - 1;
    length -= r0;
  }
  else {
    r0 = 0;
    c0 = c + r;
    length = c0 + 1;
  }
  int sum = 0;
  for (int i = 0; i < length; ++i) {
    sum += read_coordinate(r0 + i, c0 - i);
  }
  return sum;
}

template <typename board_t>
int NQueens<board_t>::check4directions(int r, int c) {
  assert(r < board_width); assert(r >= 0);
  assert(c < board_width); assert(c >= 0);
  int sum0 = 1, sum1 = 1;
  int checks[4] = {
    check_row(r, c),
    check_column(r, c),
    check_diag1(r, c),
    check_diag2(r, c)
  };
  for (auto sum: checks) {
    if (sum > sum1) sum1 = sum;
    if (sum < sum0) sum0 = sum;
  }
  return (sum1 > 1) ? sum1 : sum0;
}

template <typename board_t>
void NQueens<board_t>::print() {
  printf("%c[H", 27);
  printf("    ");
  for (int i = 0; i < board_width; ++i) {
    printf(" %-3d", i);
  }
  printf("\n");
  for (int i = 0; i < board_width; ++i) {
    printf("    ");
    for (int j = 0; j < board_width; ++j) {
      printf("+---");
    }
    printf("+\n%3d ", i);
    for (int j = 0; j < board_width; ++j) {
      printf("| %c ", read_coordinate(i, j) ? 'W' : ' ');
    }
    printf("|\n");
  }
  printf("    ");
  for (int j = 0; j < board_width; ++j) {
    printf("+---");
  }
  printf("+\n");
}

template<typename board_t>
std::vector<int> NQueens<board_t>::get_shuffled() {
  std::vector<int> shuffled(board_width, 0);
  srand(time(NULL));
  for (int i = 0; i < board_width; ++i) {
    shuffled[i] = i;
  }
  for (int i = 0; i < board_width; ++i) {
    int j = rand() % (board_width - i);
    std::swap(shuffled[i], shuffled[i + j]);
  }
  return shuffled;
}

template<typename board_t>
bool NQueens<board_t>::solve(int r, std::vector<int> &shuffled) {
  static int counter = 0;
  if (r >= board_width)
    return 1;
  for (int c = 0; c < board_width; ++c) {
    int mark = set_coordinate(r, shuffled[c], 1);

    if ((++counter %= 1000) == 0)
      print();
 
    bool result = mark <= 1;
    if (!result)
      continue;
    result = solve(r + 1, shuffled);
    if (result) {
      return true;
    }
    else {
      set_coordinate(r, shuffled[c], 0);
    }
  }
  return 0;
}

template<typename board_t>
bool NQueens<board_t>::solve() {
  std::vector<int> shuffled = get_shuffled();
  return solve(0, shuffled);
}

/**
 * The chess board is a vector<int> of length n * n */
struct NQueens_straight : public NQueens<std::vector<int>> {
  NQueens_straight(int width): NQueens<std::vector<int>>(width) {
    make_blank_board(width);
  }
  void make_blank_board(int width);
  int read_coordinate(int r, int c);
  int set_coordinate(int r, int c, int value);
};

void NQueens_straight::make_blank_board(int width) {
  board_width = width;
  board = std::vector<int>(width * width, 0);
}

int NQueens_straight::read_coordinate(int r, int c) {
  assert(r < board_width); assert(r >= 0);
  assert(c < board_width); assert(c >= 0);
  int pos = r * board_width + c;
  return *(board.begin() + pos);
}

int NQueens_straight::set_coordinate(int r, int c, int value) {
  int pos = r * board_width + c;
  *(board.begin() + pos) = value;
  int result = 1;

  if (value == 0)
    return 1;
  else if ((result = check4directions(r, c)) > 1) {
    *(board.begin() + pos) = 0;
    return result;
  }
  else {
    return result;
  }
}

/**
 *  The queens are indexed as vector<array<int, 2>> */
struct NQueens_indices: public NQueens<std::vector<std::array<int, 2>>> {
  NQueens_indices(int width): NQueens<std::vector<std::array<int, 2>>>(width) {
    make_blank_board(width);
  }
  virtual void make_blank_board(int width) ;
  virtual int read_coordinate(int r, int c);
  virtual int set_coordinate(int r, int c, int value);
};

void NQueens_indices::make_blank_board(int width) {
  board_width = width;
  board = std::vector<std::array<int, 2>>();
}

int NQueens_indices::read_coordinate(int r, int c) {
  assert(r < board_width); assert(r >= 0);
  assert(c < board_width); assert(c >= 0);
  for (auto &queen : board) {
    if (queen[0] == r && queen[1] == c)
      return 1;
  }
  return 0;
}

int NQueens_indices::set_coordinate(int r, int c, int value) {
  if (value == 0) {
    for (int i = 0; i < board.size(); ++i) {
      if (board[i][0] == r && board[i][1] == c) {
	board.erase(board.begin() + i);
      }
    }
    return 1;
  }
  // else
  board.push_back(std::array<int, 2> {{r, c}});
  int result = check4directions(r, c);
  if (result > 1) {
    board.pop_back();
    return result;
  }
  else {
    return result;
  }
}

/**
 * Queens in each row are represented by their columns.
 * Or -1 if the row is empty */
struct NQueens_rowfixed : public NQueens<std::vector<int>> {
  NQueens_rowfixed(int width): NQueens<std::vector<int>>(width) {
    make_blank_board(width);
  }
  virtual void make_blank_board(int width) {
    board_width = width;
    board = std::vector<int>(width, -1);
  }
  virtual int read_coordinate(int r, int c) {
    assert(r < board_width); assert(r >= 0);
    assert(c < board_width); assert(c >= 0);
    return *(board.begin() + r) == c;
  }
  virtual int set_coordinate(int r, int c, int value) {
    if (value == 0) {
      board[r] = -1;
      return 1;
    }
    else if (board[r] > 0 && board[r] != c) {
      return 2;
    }
    board[r] = c;
    int result = check4directions(r, c);
    if (result > 1) {
      board[r] = -1;
    }
    return result;
  }
};

int main() {
  using namespace std;
  int width;
  cout<<"Set the width:";
  cin>>width;
  NQueens_rowfixed board(width);
  board.solve();
  board.print();
  return 0;
}

