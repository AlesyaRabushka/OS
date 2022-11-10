#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>


// find word in file
void find_word(char* file, char *word, pid_t child){
	int is_found = 0;
	FILE* f = fopen(file, "r");
	
	if(f == NULL){
		printf("The file cannot be open\n");
	}
	else{
		int bytes_count = 0;
		int bytes_count1 = 0;
		char symbol[1];
		char found_word[255];
		
		while (fgets(found_word,255,f))
		{
			bytes_count += sizeof(found_word);
			
			if (strstr(found_word, word))
			{
				//printf("\t%s",found_word);
				is_found ++;
				//break;
			}
		}
		printf("The process pid is %d\n", getpid());
		printf("\tThe amount of found sequences: %d\n\tThe amount of viewed bytes: %d\n", is_found, bytes_count);
	}
	
	
};

// go through all files in directory
void search_files_in_directory(char* directory, char* searched_sequence){
	DIR *d;
	struct dirent *dir;
	d = opendir(directory);
	if (d)
	{
		int processes_amount = 0;
		while ((dir=readdir(d))!= NULL)
		{
			processes_amount++;
			// create child process
			pid_t child = fork();
			int st;
			if (child == 0)
			{
				char file_name[255];
				strcpy(file_name,dir->d_name);
				printf("file: %s\n",file_name);
				char file_path[256];
				// make a file path in format
				// dir/file.ext
				sprintf(file_path,"%s/%s", directory, file_name);
				// file word in files
				find_word(file_path, searched_sequence, child);
				// terminate child process
				exit(st);
			}
			// wait for child process to terminate
			for(int i = 0; i < processes_amount;i++)
			{
				wait(st);
			}
		}
		closedir(d);
	}
};

int main(int argc, char *argv[]){
	
	if (strlen(argv[2])>255){
		printf("The combination is too long\n");
	}
	else {
		search_files_in_directory(argv[1], argv[2]);
		//find_word("file2.txt", argv[2]);
	}
	return 0;
}
