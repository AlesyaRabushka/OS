#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>


void get_time(){  
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	struct timeval te;
	gettimeofday(&te, NULL);
	long long millisec = te.tv_sec*1000LL + te.tv_usec/1000;
	printf("Current time: %02d:%02d:%02d:%02lld\n", tm.tm_hour, tm.tm_min, tm.tm_sec, millisec);
};



int main(void){
pid_t pid = fork();

if (pid == 0){
	printf("I am a child with pid %d for a parent with pid %d\n", getpid(), getppid());
	get_time();
	exit(0); // finish the child process
} 
else if (pid > 0){
	printf("I am a parent with pid %d for a child with pid %d\n", getpid(), pid);
	get_time();	
}


pid_t pid2 = fork();

if (pid2 == 0){
	printf("I am a child with pid %d for a parent with pid %d\n", getpid(), getppid());
	get_time();
	exit(0); // finish the child process
} 
else if (pid2 > 0){
	printf("I am a parent with pid %d for a child with pid %d\n", getpid(), pid2);
	get_time();
}

system("ps -x");
wait(0);// parent waits for child to be finished
wait(0);// parent waits for child to be finished
return 0;
}



