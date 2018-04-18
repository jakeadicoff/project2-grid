#include "grid.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

xusing namespace std;

Grid::Grid(string file_name, int r_) {
  this->n_i = 0;
  this->n_j = 0;
  this->r = r_;
  read_file(file_name);
  make_blocked_layout();
}

//read in test file, populate row_major grid
void Grid::read_file(string file_name) {
  //open file
  ifstream file_stream;
  file_stream.open(file_name.c_str(), ios::in);

  if(!file_stream.good())
    cout << "Error: not able to open file" << endl;

  string line;

  //parse file for nrows, ncols, and data
  int i = 0;
  while(getline(file_stream,line)) {
    if(i > 5) {
      //https://stackoverflow.com/questions/236129/most-elegant-way-to-split-a-string
      istringstream iss(line);
      vector<string> tokens{istream_iterator<string>{iss},
	  istream_iterator<string>{}};

      //https://stackoverflow.com/questions/20257582/convert-vectorstdstring-to-vectordouble
      vector<double> doubleVector(tokens.size());
      transform(tokens.begin(), tokens.end(), doubleVector.begin(),
		[](const std::string& val) { return std::stod(val); });

      //Append new line that was just read into file
      for (uint i = 0; i<doubleVector.size(); ++i)
	row_major.insert(row_major.end(), doubleVector.begin(), doubleVector.end());
    }

    else if(i == 0) sscanf(line.c_str(), "%*s %d", &n_j); //first line is num_cols
    else if(i == 1) sscanf(line.c_str(), "%*s %d", &n_i); //second is num_rows

    i++;
  }

  cout << "rows: " << n_i << "; cols: " << n_j << "; block radius: " << r << endl;

  cout << "ROW MAJOR FORMAT:" << endl;
  print_row_major();
}

//populate blocked array from row_major
void Grid::make_blocked_layout() {
  int counter = 0; // to keep track of row-major array
  int r_i, r_j;
  r_i = r_j = 0;

  for(int i = 0; i < n_i; i+=r) {
    for(int j = 0; j < n_j; j+=r) {
      //r_i and r_j are height and width of current block
      r_i = r_j = r;

      //adjust block width and height if necessary
      if(n_i-i < r_i) r_i = n_i-i;
      if(n_j-j < r_j) r_j = n_j-j;

      for(int ii = 0; ii < r_i; ii++) {
	for(int jj = 0; jj < r_j; jj++) {
	  blocked.push_back(row_major[(i+ii)*n_j+j+jj]);
	  counter++;
	}
      }
    }//j for loop
  }//i for loop

  cout << "BLOCKED FORMAT:" << endl;
  print_blocked();
}

//Get corresponding rowmajor index i,j from blocked array
int Grid::get_blocked_index(int i, int j){
  //Block grid position
  int B_i = i/r;
  int B_j = j/r;

  //block height and width
  int height = r;
  int width = r;

  //truncate block if necessary
  if((B_i+1)*r > n_i) {height = r - ((B_i+1)*r-n_i);}
  if((B_j+1)*r > n_j) {width = r - ((B_j+1)*r-n_j);}

  //top blocks: number of rows * elements per row
  int top_blocks = (B_i*r*n_j);
  //left blocks: height * r * number of blocks BEFORE
  int left_blocks = (B_j*height*r);

  //index of top left corner
  int tlc = top_blocks + left_blocks;

  //relative position of element within block
  int i_rel = i%r;
  int j_rel = j%r;

  return tlc + (i_rel * width) + j_rel;
}

//Confirm that the blocked array was created properly
void Grid::test() {
  for(int i = 0; i < n_i; i++)
    for(int j = 0; j < n_j; j++)
      assert(get_row_major(i, j) == blocked[get_blocked_index(i, j)]);

  cout << "test() result: Blocked matrix maps to Row Major matrix correctly." << endl;
}

void Grid::print_row_major() {
  for(int i = 0; i < n_i; i++){
    for(int j = 0; j < n_j; j++){
      cout << row_major[i*n_j + j] << "\t";
    }
    cout << endl;
  }
}

void Grid::print_blocked() {
  for(int i = 0; i < n_i; i++){
    for(int j = 0; j < n_j; j++){
      cout << blocked[i*n_j + j] << "\t";
    }
    cout << endl;
  }
}
