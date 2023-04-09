# Sum Totient Range

In this project, I have parallelized a .c code for calculating the "Euler Totient Range" between 2 numbers. I have used OpenMP for this matter. After finishing the development I cloned this code on Heriot-Watt Robotarium Cluster and ran it on 64 cores. 
For make: gcc (-fopenmp) Totient.c -o totient 
//-fopenmp for parallel code
For run: ./totient lower upper
