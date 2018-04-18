#include "main.h"

using namespace std;

int main(int argc, char** argv) {

  if(argc < 3) {
    cout << "Not enough arguments:\n" <<
      "arg 1: filename\n" <<
      "arg 2: block size" << endl;
    exit(0);
  }

  string file_name = argv[1];
  int block_size = atoi(argv[2]);

  Grid g(file_name, block_size);

  g.test();

  return 0;
}
