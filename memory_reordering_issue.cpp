/*
 *Detecting memory reordering. Courtesy Preshing.com
 */
#include <iostream>
#include <thread>

int X{0},Y{0},X1{0},Y1{0};

void set_X_and_Y1()
{
  X = 1;
  Y1 = Y;
}

void set_Y_and_X1()
{
  Y = 1;
  X1 = X;
}

int main()
{
  int detectionCount{0};

  //run the loop forever keeping track of the iteration count
  for(int iteration = 0; ; ++iteration)
  {
    //reinitialize global variables
    X = {0};
    Y = {0};
    X1 = {0};
    Y1 = {0};

    //start the threads to modify global variables
    std::thread t1(set_X_and_Y1);
    std::thread t2(set_Y_and_X1);
    //wait for the threads to complete
    t1.join();
    t2.join();

    //check for X1 and Y1 value combination which is impossible
    //to achieve on a single thread process
    if(X1 == 0 && Y1 == 0)
      std::cout << "Detected " << ++detectionCount
        << " times out of " << iteration << " tries." << std::endl;
  }
}

/*iramalin@ilaya-ubuntu:~/mygit/mysolutions$ g++ -O4 -std=c++14 -pthread memory_reordering_issue.cpp 
 *iramalin@ilaya-ubuntu:~/mygit/mysolutions$ ./a.out
 *Detected 1 times out of 148282 tries.
 *Detected 2 times out of 240535 tries.
 *Detected 3 times out of 370008 tries.
 *Detected 4 times out of 370078 tries.
 *Detected 5 times out of 468467 tries.
 *Detected 6 times out of 491427 tries.
 *Detected 7 times out of 603453 tries.
 *Detected 8 times out of 916054 tries.
 *Detected 9 times out of 1362330 tries.
 *Detected 10 times out of 1495274 tries.
 *Detected 11 times out of 1552475 tries.
 *^C
 *iramalin@ilaya-ubuntu:~/mygit/mysolutions$ lscpu
 *Architecture:          i686
 *CPU op-mode(s):        32-bit
 *Byte Order:            Little Endian
 *CPU(s):                2
 *On-line CPU(s) list:   0,1
 *Thread(s) per core:    1
 *Core(s) per socket:    2
 *Socket(s):             1
 *Vendor ID:             GenuineIntel
 *CPU family:            6
 *Model:                 14
 *Model name:            Genuine Intel(R) CPU           T2300  @ 1.66GHz
 *Stepping:              8
 *CPU MHz:               1667.000
 *CPU max MHz:           1667.0000
 *CPU min MHz:           1000.0000
 *BogoMIPS:              3324.57
 *Virtualization:        VT-x
 *L1d cache:             32K
 *L1i cache:             32K
 *L2 cache:              2048K
 *
 */
