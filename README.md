Jake Adicoff and Ethan Zhou

The Grid class parses an .asc grid data file and parses the matrix
into a row-major format and a blocked format.

The class provides accessors to index into either array, using the
row-major coordinates.

The class also provides a test method to test for correctness. The
method uses an assert(), so the program will crash upon failure.

The class also provides a print method for printing the matricies in a
2 dimensional layout. Comment out the print methods on lines 56 and 84
if you wish to surpress the printout.


---


After making the project, run:
./grid <.asc filename> <blocksize>
