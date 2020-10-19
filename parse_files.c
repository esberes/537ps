#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

/* @file parse_files.c
 * @authors Libby Howard and Ellie Beres
 *   
 * This method parses through the stat, statm and cmdline files and 
 * prints the appropriate information. 
 * In the stat file, we extract the state, utime and stime fields.
 * In the statm file, we extract the size field. Finally, we extract 
 * the command line that started the particular process in the cmdline
 * file. The information is printed depending on whether the option is flagged or not.
 *
 * @param flags: pointer to an int array containing option flags (1 = turned on, 0 = off)
 *        pid: character pointer to pid of a process  
 */

int parse_files(int *flags, char *pid)
{
    const int MAX_CHAR = 1000;
    
    // build file path 
    FILE *fp;
    char file[MAX_CHAR];
    strcpy(file, "/proc/");
    strcat(file, pid);

    // stat file 
    char stat[MAX_CHAR];
    strcpy(stat, file);
    strcat(stat, "/stat");

    // statm file 
    char statm[MAX_CHAR];
    strcpy(statm, file);
    strcat(statm, "/statm");

    // cmdline file 
    char cmdline[MAX_CHAR];
    strcpy(cmdline, file);
    strcat(cmdline, "/cmdline");
    
    // stored vars 
    char *state; 
    char *utime;
    char *stime;
    char *vmem;
   
    // PRINT PID
    printf("%s: ", pid);

    // OPEN AND PARSE STAT
    // only open if s, S, U has been tagged 
    if (flags[1] == 1 || flags[2] == 1 || flags[3] == 1) { 
   	 fp = fopen(stat, "r");
   	 if (fp == NULL) {
		 printf("Could not open file %s", stat);
	 	 exit(1);;
   	 }
         // find right field and print only if option is tagged   
    	 char stat_info[MAX_CHAR];
   	 for (int i = 1; i < 16; i++) {
	   	 if (i == 3 && flags[1] == 1) {
		    	fscanf(fp, "%s", stat_info);
		    	state = stat_info;
		    	printf("%s ", state);
            	 }  else if (i == 14 && flags[2] == 1) {
		    	fscanf(fp, "%s", stat_info);
		    	utime = stat_info;
		    	printf("utime=%s ", utime);
            	 } else if (i == 15 && flags[3] == 1) {
		    	fscanf(fp, "%s", stat_info);
		    	stime = stat_info;
		    	printf("stime=%s ", stime);
	    	 } else {
		    	fscanf(fp, "%s", stat_info);
	    	 }
    	}
    	 fclose(fp);
    }

    // OPEN AND PARSE STATM
    // ony open if v has been tagged 
    if (flags[4] == 1) {
    	fp = fopen(statm, "r");
    	if (fp == NULL) {
        	printf("Could not open file %s", statm);
        	exit(1);
    	}
	
	// scan and print 
    	char statm_info[MAX_CHAR];
    	fscanf(fp, "%s", statm_info);
    	vmem = statm_info;
    	printf("vmem=%s ", vmem);

    	fclose(fp);
    }

    // OPEN AND PARSE CMDLINE
    // only open is c has been tagged
    if (flags[5] == 1) { 
    	fp = fopen(cmdline, "r");
    	if (fp == NULL) {
		printf("Could not open file %s", cmdline);
		exit(1);
    	}	 
	
	printf("[");
	// print chars in cmdline file until end of file
    	int cmd_char;
    	do {
		cmd_char = fgetc(fp);
		if(feof(fp)) {
			break;
	    	} 
	    	printf("%c", cmd_char);
    	} while(1);
	printf("]");

    	fclose(fp); 
    }

    printf("\n");

    return 0;
}

