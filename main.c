#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "read_options.h"

/* @file main.c
 * @authors: Ellie Beres and Libby Howard 
 *
 * This module initiates the ps process. 
 * 
 * @param argc - number of cmdine arguments 
 *        argv - structure containing arguments passed in by user 
 */

int main (int argc, char **argv)
{
	read_options(argc, argv); 
	return 0;
}
