/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2015 Assignment #2
 * Full Name        : Keaton Okkonen
 * Student Number   : s3432651
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/

#include "ppd_main.h"
#include "ppd_menu.h"
#include "ppd_options.h"
#include "ppd_utility.h"

/**
 * @file ppd_main.c contains the main function implementation and any
 * helper functions for main such as a display_usage() function.
 **/

/**
 * manages the running of the program, initialises data structures, loads
 * data and handles the processing of options. The bulk of this function
 * should simply be calling other functions to get the job done.
 **/
int main(int argc, char **argv)
{

    /* validate command line arguments */
    if(argc != 3) {
		printf("%s\n", "Oops! Your command line arguments are incorrect.");
        return EXIT_FAILURE;
	}

	if(strcmp(argv[1], "stock.dat") != 0 && strcmp(argv[2], "coins.dat") != 0) {
		printf("Oops! Please check your command line arguments: eg ./ppd *items*.dat *funds*.dat \n");
		return EXIT_FAILURE;
	}

    /* represents the data structures to manage the system */
    struct ppd_system system;
    int selection = 0;
    BOOLEAN running = TRUE;

    /* init the system */
    system.stock_file_name = argv[1];
    system.coin_file_name = argv[2];
    system_init(&system);
    printf("System initialised. Please wait.");

    /* load data from .dat files */
    load_data(&system, system.coin_file_name, system.stock_file_name);

    /* initialise the menu system */
    menu_item menu[MENU_SIZE];
    init_menu(menu);

    while (running) {
        /* loop, asking for options from the menu */
        selection = display_menu(menu);
        printf("%s%d%s", "Option ", selection, " has been selected.");

        /* run each option selected */
        if(menu[(selection - 1)].function( &system ) == FALSE) {
            printf("\n\n%s\n", "Sorry! Something went wrong. Now exiting.");
            running = FALSE;
        }

    }

    /* User has opted to quit */

    /* make sure you always free all memory and close all files
     * before you exit the program
     */
    return EXIT_SUCCESS;
}
