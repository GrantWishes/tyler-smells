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
	char **words = (char **) malloc(size);
	char *ptr = strtok(arguments, " ");

	if (words == NULL) {
		perror("words mem"); // delete at end
		error();
		}

	for (int i = 0; ptr != NULL; i++) {
		words[i] = ptr;
		ptr = strtok(NULL, " ");
	}

//	for(int i = 0; words[i] != NULL; i++) {
//		printf("Word: %s\n", words[i]);
//
//	}

	return words;

}

int main(int argc, char *argv[]) {

	char input[MAX_INPUT];	
	char **args;	

	while(1) {
		// the shell print	
		printf("mysh> ");
		// read in from standard input
		fgets(input,sizeof(input),stdin);

		// black magic code that gets rid of a stupid newline character
		input[strcspn(input,"\n")] = '\0';	

		args = parse(input,sizeof(input));

		for (int i = 0; args[i] != NULL; i++) {
			printf("Word2: %s\n", args[i]);	
		}

	//        switch(input) {
	//	case "exit" :
	//	  exit(0);
//
//		case "cd" :
//
//		case
//		}
		
		// exits the shell when called	
		if(strcmp(input,"exit") == 0) {
			exit(0);
		}

	}

	args[0] = '\0'; 

}
