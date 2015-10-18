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
int main(int argc, char **argv) {
  /* represents the data structures to manage the system */
  struct ppd_system system;
	int selection = 0;
	menu_item menu[NUM_OF_MENUITEMS];
	BOOLEAN finished = FALSE;

	/* validate command line arguments */



	/* SHOULD I USE A DEFINED CONSTANT INSTAED OF 3? */
	if(argc != 3) {
		printf("%s\n", "Error; invalid arguments");
    return EXIT_FAILURE;
	}

	if(strcmp(argv[1], "stock.dat") != 0 && strcmp(argv[2], "coins.dat") != 0) {
		printf("Error; misspelled arguments or incorrect order, aka should be *.exe stock.dat coins.dat \n");
		return EXIT_FAILURE;
	}

  /* init the system */


	/* should be here ? */
	system.stock_file_name = argv[1];

	system.coin_file_name = argv[2];

	system_init(&system);

   /* load data */
	 load_data(&system ,system.coin_file_name ,system.stock_file_name);

	/* test if everything has been initialised correctly */

	/* printf("\n\n\n%s\n", system.item_list->head->next->next->data->name); */


    /* initialise the menu system */
	/*for (i = 0; i < NUM_OF_MENUITEMS; i++)
	{
	init_menu(&menu[i],i);

	}
	*/

	init_menu(menu);


	while (!finished)
	{

    /* loop, asking for options from the menu */
	selection = run_menu(menu);
    /* run each option selected */

	finished = menu[selection].function(&system);

	}
    /* until the user quits */

    /* make sure you always free all memory and close all files
     * before you exit the program
     */
    return EXIT_SUCCESS;
}
