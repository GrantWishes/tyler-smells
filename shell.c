#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT (512)

void error() {
	char error_message[30] = "An error has occured\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

char **parse(char arguments[], size_t size) {
	char **words = (char **) malloc(size);		// the array of commands and arguments
	char *ptr = strtok(arguments, " ");

	if (words == NULL) {				// error checking
		perror("words mem"); // delete at end
		error();
		}

	// adding the words to the array
	for (int i = 0; ptr != NULL; i++) {
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

//	        switch(input) {
//		case "exit" :
//			exit(0);
//			break;
//
//		case "cd" :
//
//		case
//		}
		
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

		
	}

	args[0] = '\0'; 

}
