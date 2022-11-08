Name: Michael Chagnon
Date: October 27, 2022


Accomplishment: I was able to finish both the scanner and parser parts of the assignment. I did the scanner
by adding appropriate tokens to the header file and adding cases for them in the .cpp file. For the parser
I used the predict set table to figure what needed to go in each case.

Additionally I added to my Makefile so when "make primes" or "make average" is typed the
program will automatically run with the primes.cl and average.cl respectively.


How to run program:
Run Makefile. Use scanner on particular file by using ./scantest < primes.cl and to parse
use ./parse < average.cl. Running scantest shows an output of what the scanner would read.
Parse shows the predict set for the scanned symbols and will stop when an error is found.