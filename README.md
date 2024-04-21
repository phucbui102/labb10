#include<stdio.h> 
#include<unistd.h>
 	int main()
{ 
	pid_t pid; 
	int num_coconuts = 17; 
	pid = fork(); 
	if(pid == 0)
{ 
	num_coconuts = 42; 
	exit(0); 
	} else 
{
wait(NULL); /*wait until the child terminates */ 
	} 
	printf("I see %d coconuts!\n", num_coconuts); 
	exit(0); 
}
