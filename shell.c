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

char[] parse(char arguments[]) {
	char **args;	// pointer to a pointer. for multiple words
	char *ptr;

	if(ptr) {


	}

<<<<<<< HEAD
=======

>>>>>>> 7f866092314da93b25fb3b2b3e85030b018870d5
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
		args = parse(input);
	        switch(input) {
		case "exit" {
		  exit(0);
		  break;
		}

		case "cd" {
		  if ((args[1]) == NULL) {
		    getenv("HOME");
		  }
		  else {
		    // lol idk how to do this yet so exit
		    exit(0);
		  }
		    break;
		  }

		case "pwd":
		  getcwd();
		  break;

		case "wait":
		  // i'm waiting on my brain to work
		  exit(0);
		  break;

		default:
		    
		    
		}
		
		// exits the shell when called	
		if(strcmp(input,"exit") == 0) {
			exit(0);
		}
	



		


	}



}
