#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]){

	pid_t pid2, pid3, pid4, pid5, pid6, pid7;
	
	//main process
	printf("Main process ID: %d, Parent ID: %d\n", getpid(), getppid());
	printf("----------------------------------------\n\n");
	
	// process 2
	pid2 = fork();
	if (pid2 == 0)
	{
		printf("Parent with ID: %d create process with ID %d\n", getppid(), getpid());
		// process 5
		pid5 = fork();
		if (pid5 == 0)
		{
			printf("Parent with ID: %d create process with ID %d\n", getppid(), getpid());
			// process 6
			pid6 = fork();
			if (pid6 == 0)
			{
				printf("Parent with ID: %d create process with ID %d\n", getppid(), getpid());
				exit(0);
			}
			wait(0); // wait for pid6 to complete
			printf("\tThe process with ID %d is completed. Parent ID: %d\n", pid6, getpid());
			exit(0);
		}
		wait(0); // wait for pid5 to complete
		printf("\tThe process with ID %d is completed. Parent ID: %d\n", pid5, getpid());
		exit(0);
	}
	wait(0); // wait for pid2 to complete
	printf("\tThe process with ID %d is completed. Parent ID: %d\n", pid2, getpid());
	
	// process 3
	pid3 = fork();
	if (pid3 == 0)
	{
		printf("Parent with ID: %d create process with ID %d\n", getppid(), getpid());
		// process 7
		pid7 = fork();
		if (pid7 == 0)
		{
			printf("Parent with ID: %d create process with ID %d\n", getppid(), getpid());
			exit(0);
		}
		wait(0); // wait for pid7 to complete
		printf("\tThe process with ID %d is completed. Parent ID: %d\n", pid7, getpid());
		exit(0);
	}
	wait(0); // wait for pid3 to complete
	printf("\tThe process with ID %d is completed. Parent ID: %d\n", pid3, getpid());
	
	// process 4
	pid4 = fork();
	if (pid4 == 0)
	{
		printf("Parent with ID: %d create process with ID %d\n", getppid(), getpid());
		system("whoami");
		exit(0);
	}
	wait(0);// wait for pid4 to complete
	printf("\tThe process with ID %d is completed. Parent ID: %d\n", pid4, getpid());
	
	return 0;
}
