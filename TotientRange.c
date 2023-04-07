// TotientRance.c - Sequential Euler Totient Function (C Version)
// compile: gcc -Wall -O -o TotientRange TotientRange.c
// run:     ./TotientRange lower_num uppper_num

// Greg Michaelson 14/10/2003
// Patrick Maier   29/01/2010 [enforced ANSI C compliance]

// This program calculates the sum of the totients between a lower and an 
// upper limit using C longs. It is based on earlier work by:
// Phil Trinder, Nathan Charles, Hans-Wolfgang Loidl and Colin Runciman

#include <stdio.h>
#include <time.h>
#include <omp.h>

// hcf x 0 = x
// hcf x y = hcf y (rem x y)

long hcf(long x, long y)
{
  long t;
 // omp_set_num_threads(64);
// #pragma omp parallel
 // {
   //   #pragma omp for
      for (; y != 0;) {
          t = x % y;
          x = y;
          y = t;
      }
  //}
  return x;
}


// relprime x y = hcf x y == 1

int relprime(long x, long y)
{
  return hcf(x, y) == 1;
}


// euler n = length (filter (relprime n) [1 .. n-1])

long euler(long n)
{
  long length, i;

  length = 0;
  for (i = 1; i < n; i++)
    if (relprime(n, i))
      length++;
  return length;
}


// sumTotient lower upper = sum (map euler [lower, lower+1 .. upper])

long sumTotient(long lower, long upper)
{

  long sum,i;
  sum = 0; 
  omp_set_num_threads(64);
  #pragma omp parallel
  {
      long temp;
      temp = 0;
      int i, id;
      int num_threads;
      id = omp_get_thread_num();

      #pragma omp parallel for num_threads(64)
      for (i = lower+id; i <= upper; i+=64)
      {
          temp = euler(i);
          #pragma omp critical
          { sum += temp; }
      }
  }
  return sum;
}


void runBenchmark()
{
  clock_t start, end;
  double time_taken;

  for (long i = 1; i < 1000000 ; i = i + 100000) {
    start = clock();
    euler(i);
    end = clock();
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("euler(%lu) = %f seconds\n", i, time_taken);
  }   
}

int main(int argc, char ** argv)
{
  long lower, upper;
  clock_t t;
  t = clock();
  if (argc != 3) {
    printf("not 2 arguments\n");
    return 1;
  }
  sscanf(argv[1], "%ld", &lower);
  sscanf(argv[2], "%ld", &upper);
  printf("C: Sum of Totients  between [%ld..%ld] is %ld\n",
         lower, upper, sumTotient(lower, upper));
         	t = clock() - t;
           t/=64;
	 double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("process took %f seconds to execute \n", time_taken);
  return 0;
}
