//Fibonacci Series using Dynamic Programming 
#include<stdio.h> 

int fib(int n) 
{ 
/* Declare an array to store Fibonacci numbers. */
int f[n+2]; // 1 extra to handle case, n = 0 
int i; 

/* 0th and 1st number of the series are 0 and 1*/
f[0] = 0; 
f[1] = 1; 

for (i = 2; i <= n; i++) 
{ 
	/* Add the previous 2 numbers in the series 
		and store it */
	f[i] = f[i-1] + f[i-2]; 
        //printf("f[%d] = %d\n", i, f[i]); 
} 

return f[n]; 
} 

int main () 
{ 
/* Maximum int value is 2147483647. 
   The 46th fibonacci number is 1836311903.
   The 47th fibonacci number exceeds the maximum. */
int n = 46;  
printf("Calculating the 46th Fibonacci Number using Dynamic Programming.\n");
printf("f[%d] = %d\n", n, fib(n)); 
return 0; 
} 

