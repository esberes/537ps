#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "parse_files.h"

/* @file process_list.c
 * @authors Libby Howard and Ellie Beres 
 */

/* This method checks to see if the pid passed in by the user is an actual pid
 * within proc
 *
 * @param pid - pid passed in by user 
 */
int is_valid_pid(char *pid) {
    
    if (atoi(pid) == 0) {
	    puts("This program does not accept this pid value");
	    exit(1);
    }

    DIR *folder; // directory to be read 
    struct dirent *entry; // pointer to structure representing next directory entry

    folder = opendir("/proc");
        if (folder == NULL){
                puts("Unable to read directory");
                exit(1);
        }

    while((entry=readdir(folder))) {
        if (strcmp(entry->d_name, pid) == 0) {
                return 1;
        }
    }
    return 0;
}

/* This method first checks whether the p option has been tagged or not.
 * If it has been flagged, parse_files is called immediately to 
 * extract information about the particular pid provided by the user.
 * If p has not been flagged, the method compares the user UID to each UID of 
 * processes in proc. If they are equal, parse_files is called to extract information.
 *
 *
 * @param flags: pointer to an int array containing option flags (1 = turned on, 0 = off)
 *        pid: character pointer to pid of a process  
 */

int process_list(int *flags, char *pid)  {
   
    DIR *folder; // directory to be read 
    struct dirent *entry; // pointer to structure representing next directory entry
    int uid = getuid(); // UID of currently running process
    const int MAX_CHAR = 1000; // max chars in char array 

    // check to see if p is tagged. if yes, go straight to parse_files
    if (flags[0] == 1) {
	if (is_valid_pid(pid) == 1) {
    		parse_files(flags, pid);
	} else {
		puts("PID does not exist within proc");
		exit(1);
	}
    } else {
    	folder = opendir("/proc");
    	if (folder == NULL){   
        	puts("Unable to read directory");
        	exit(1);
    	}
 
	// loop through proc folder and extract uid from each valid pid 
    	while((entry=readdir(folder))) {  
    		// check if pid is digit 
		if (atoi(entry->d_name) != 0) {
			
			// build file path 
			FILE *fp; 
        		char str[MAX_CHAR];
        		char *proc_list_pid = entry->d_name; 
        		strcpy(str, "/proc/");
        		strcat(str, proc_list_pid);
        		strcat(str, "/status");
        		char *status = str;
	 
			// open status file 
			fp = fopen(status, "r");
        		if (fp == NULL) {
                		printf("Could not open file %s", status);
                		exit(1);
        		}	
	
			// retrieve 9th line of status file where UID is found 
			char uid_line[MAX_CHAR];
			for(int i = 1; i < 10; ++i){
				if (i == 9) {
					fgets(uid_line, MAX_CHAR, fp);
					break;
				}	
				fgets(uid_line, MAX_CHAR, fp);
			}
			
			// split line by tab char and extract 2nd token
			char *token = strtok(uid_line, "\t");
			int counter = 0; 
			char *procuid;
			while(token != NULL){
				if(counter == 1) {
                        		token = strtok(NULL, "\t");
					procuid = token;
					break;
				}
				token = strtok(NULL, "\t");
				counter++;
			}
			
			// check to see if uid of process equals uid of currently running process 
			int procuidint = atoi(procuid);
			if(procuidint == uid) {
				parse_files(flags, proc_list_pid); 
			}	
		}
    	}

    closedir(folder);
   
    }

    return(0);
}
