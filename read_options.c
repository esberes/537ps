#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "process_list.h"

/* @file read_options.c
 * @authors Ellie Beres and Libby Howard 
 *
 * This method is used to read user input in the command line.
 * Users can enable/disable the following options: 
 * p, s, U, S, v, c. If a user enters an option other than 
 * those stated, the program will exit. Options are tagged
 * in an array pointer called flags. If an option is tagged, its
 * value will be 1, else 0.
 *
 * @param argc - number of cmdine arguments 
 *        argv - structure containing arguments passed in by user  
 * 	  
 * */
int read_options(int argc, char **argv) {

	int *flags =(int*)malloc(6 * sizeof(int)); // p,s,U,S,v,c
	if (flags == NULL) {
        	puts("Failed to allocate memory\n");
        	exit(1);
	}
	
	// set default values of flags
	flags[0] = 0;//p
	flags[1] = 0;//s
	flags[2] = 1;//U
	flags[3] = 0;//S
	flags[4] = 0;//v
	flags[5] = 1;//c


	char *pid; // process ID user passes in 
	int cmdArg; // option character returned by getopt 

	// loop through command line arguments and handle accordingly
	while ((cmdArg = getopt (argc, argv, "-:p:s::U::S::v::c::")) != -1) {
		switch (cmdArg) {
        	case 'p':
        		flags[0] = 1;
        		pid = optarg;
        		break;
      		case 's':
        		if (optarg == NULL) {
                		flags[1] = 1; 
       		 	} else {
                		if (strcmp(optarg, "-") != 0) { 
                        		puts("Invalid input for '-s' argument");
                        		exit(1);
                		} else {
				       flags[1] = 0;
				}	       
			}
        		break;
      		case 'U':
        		if (optarg == NULL) {
                		flags[2] = 1;
        		} else {
                		if (strcmp(optarg, "-") != 0) {
                        		puts("Invalid input for '-U' argument");
                        		exit(1);
                	} else {
                        	flags[2] = 0; 
                	}
        	}
 			break;
      		case 'S':
        		if (optarg == NULL) {
                		flags[3] = 1;
        		} else {
                		if (strcmp(optarg, "-") != 0) { 
                        		puts("Invalid input for '-S' argument");
                        		exit(1);
                		} else {
					flags[3] = 0;
				}
        	}
        		break;
      		case 'v':
        		if (optarg == NULL) {
                		flags[4] = 1;
       		 	} else {
                		if (strcmp(optarg, "-") != 0) { 
                        		puts("Invalid input for '-S' argument");
                        		exit(1);
                		} else {
					flags[4] = 0;
				}
        		}	
        		break;
      		case 'c':
        		if (optarg == NULL) {
                		flags[5] = 1;
        		} else {
                		if (strcmp(optarg, "-") != 0) { 
                        		puts("Invalid input for '-c' argument");
                        		exit(1);
                		} else {
                        		flags[5] = 0;
                		}
        		}
        		break;
		// option needs an argument but was not given one
      		case ':': 
        		printf("-%c needs an argument\n",optopt);
        		exit(1);
			break;
		// option is invalid and is not possible in this program 
      		case '?':
        		printf("The option -%c does not exist\n",optopt);
        		exit(1);
			break;
      		default:
        		printf("The option -%c does not exist\n", optopt);
			exit(1);
			break;
      		}
	}
        
	// pass flags and pid to be handled while processing proc 
	process_list(flags, pid);  
  
	return 0;
}
                   
