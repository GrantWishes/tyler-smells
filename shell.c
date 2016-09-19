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

void parse(char arguments[]) {
	char **args;	// pointer to a pointer. for multiple words
	printf("The string passed: %s\n",args);	

		

}

int main(int argc, char *argv[]) {

	char input[MAX_INPUT];	

	while(1) {
		// the shell print	
		printf("mysh> ");
		// read in from standard input
		fgets(input,sizeof(input),stdin);

		// black magic code that gets rid of a stupid newline character
		input[strcspn(input,"\n")] = '\0';	

		parse(input);
		
		// exits the shell when called	
		if(strcmp(input,"exit") == 0) {
			exit(0);
		}
	



		


	}



}
