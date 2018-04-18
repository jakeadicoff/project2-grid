#ifndef __grid_h
#define	__grid_h

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <vector>
#include <assert.h>

using namespace std;

class Grid {
 public:
  Grid(string file_name, int r_);

  //Get corresponding rowmajor index i,j from blocked array
  int get_blocked_index(int i, int j);

  //row major array accessor
  double get_row_major(int i, int j) {return row_major[i*n_j+j];}

  //test for blocked layout correctness
  void test();

  void print_row_major();
  void print_blocked();

 private:
  int n_i, n_j, r;
  vector<double> row_major;
  vector<double> blocked;

  //populate blocked array from row_major
  void make_blocked_layout();

  //read in test file, populate row_major grid
  void read_file(string file_name);
};
#endif
