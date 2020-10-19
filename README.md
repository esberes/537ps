In the program, we created a version of the ps command. Through 4 modules main, read_options, process_list, and read_options we are able to take the users inputs from the command line and printing the appropriate information. 

main: initates ps process. 

read_options: This module is used to read user input in the command line. Users can enable/disable the following options:p, s, U, S, v, c. If a user enters an option other than those stated, the program will exit. Options are tagged in an array pointer called flags. If an option is tagged, its value will be 1, else 0.

process_list: This module first checks whether the p option has been tagged or not. If it has been flagged, the pid will be checked to ensure its validity. If valid, parse_files is called immediately to extract information about the particular pid provided by the user. If pid is not valid, the process with terminate. If p has not been flagged, the module compares the user UID to each UID of processes in proc. If they are equal, parse_files is called to extract information.

parse_files: This module parses through the stat, statm and cmdline files and prints the appropriate information. In the stat file, we extract the state, utime and stime fields.In the statm file, we extract the size field. Finally, we extract the command line that started the particular process in the cmdline file. The information is printed depending on whether the option is flagged or not.

Authors: Libby Howard and Ellie Beres
