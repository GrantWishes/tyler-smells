#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INPUT (513) // 512 characters + carriage return

void error() {
	/* The one true error message. */
	char error_message[30] = "An error has occured\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

char **parse(char arguments[], size_t size) {
	/* the array of commands and args
	   char array filled with char arrays so it's ** */	
	char **words = (char **) malloc(size);	
	/* pointer to each individual word */
	char *ptr = strtok(arguments, " ");

	/* error checking */
	if (words == NULL) {				
		perror("words mem"); // delete at end
		error();
		}

	/* for empty or only space strings, makes it work properly */
	if(ptr == NULL){
		words[0] = "";
		return words;
	}
	/* adding the words to the array */
	for (int i = 0; ptr != NULL; i++) {
		bool isPy = false;	//special case for python scripts
		char* ret;		//the substring we're looking for
		ret = strstr(ptr, ".py\0");
		/*if it's a python file, we gotta do something diff */
		if (ret != NULL) {
		  isPy = true;
		  printf("This is a python file\n");
		}
		words[i] = ptr;
		ptr = strtok(NULL, " ");
	}

//	Debug print
//	for(int i = 0; words[i] != NULL; i++) {
//		printf("Word: %s\n", words[i]);
//
//	}
	return words;
}

int main(int argc, char *argv[]) {

	char input[MAX_INPUT];	// for the input string
	char **args;		// for the command and arguments parsed
	char pwd[MAX_INPUT*2];	// for the pwd functionality, size seemed common

	

	while(1) {
		// the shell print	
		printf("mysh> ");
		// read in from standard input
		fgets(input,sizeof(input),stdin);

		// black magic code that gets rid of a stupid newline character
		input[strcspn(input,"\n")] = '\0';
		args = parse(input,sizeof(input));
		// exits the shell	
		if(strcmp(args[0],"exit") == 0) {
			exit(0);
		} 
		// prints working directory
		else if(strcmp(args[0],"pwd")==0) {
			if(getcwd(pwd,sizeof(pwd)) != NULL) {
				printf("%s\n", pwd);
			}
			else {
				error();
			}
		}
		else if(strcmp(args[0],"cd")==0) {
			if(args[1] == '\0') {
				//char *home = getenv("HOME");
				chdir(getenv("HOME"));		
			}
			else {
				int c = chdir(args[1]);
				if(c < 0) {
					error();
				}
			}
		}
		else if(strcmp(args[0], "") == 0) {
			continue;
		}
		else {
			pid_t pid = fork();   //i accidentally fork bombed here
			int status;
			
			if(pid < 0) {
				error();
			}
			else if(pid == 0) {
				if(execvp(args[0],args) < 0) {
					error();
					exit(1);
				}
			}

			else {
				while(wait(&status)!=pid) ;
			}
		}
	



		args[0] = '\0';			// clears the array
	}

	return 0;
	
}
