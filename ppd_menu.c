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

#include "ppd_menu.h"
/**
 * @file ppd_menu.c handles the initialised and management of the menu
 * array
 **/

/**
 * @param menu the menu item array to initialise
 **/
void init_menu( struct menu_item * menu) {

    int item = 0;
    char * menuLabels[MENU_SIZE] = {
        "Display Items",
        "Purchase Items",
        "Save and Exit",
        "Add Item",
        "Remove Item",
        "Display Coins",
        "Reset Stock",
        "Reset Coins",
        "Abort Program"
    };

    BOOLEAN ( * function[MENU_SIZE] )( struct ppd_system * ) = {
        display_items,
        purchase_item,
        save_system,
        add_item,
        remove_item,
        display_coins,
        reset_stock,
        reset_coins,
        abort_program
    };

    for(item = 0; item < MENU_SIZE; i++) {
    	strcpy(menu[item].name, menuLabels[item]);
    	menu[item].function = function[i];
    }
}

int display_menu( struct menu_item menu[]) {
	int index = 0,
        selection = 0,
        optionLength = 3,
        optionMin = 1,
        optionMax = 9,
        inputLength,
        convertedInput;

    char inputString[MAXINT + 2];
    char * end;

    while (!selection || selection == 0) {
        /* display the menu */
        printf("%s\n%s\n%s\n",
            "______________________________",
            "Vending Machine Menu:",
            "______________________________"
        );

    	for( index = 0; index < NUM_OF_MENUITEMS; index++) {

    		printf("%d|\t%s\n", (index + 1), menu[index].name);

    		if(index == 2) {
    				printf("\n%s\n", "Administrator options:");
    		}

    	}

    	printf("\n%s\n", "What action would you like to take? (1-9) :");

        /* collect user input and validate */
        fgets(inputString, optionLength, stdin);

        inputLength = strlen(inputString) - 1;
        if (inputString[inputLength] == '\n'){
            inputString[inputLength] = '\0';
        }

        /* convert string input to integer and validate */
        convertedInput = (int) strtol(inputString, &end, 10);

        if (!convertedInput || convertedInput < optionMin || convertedInput > optionMax) {
            printf("Error! This is not a valid selection.");
        } else {
            selection = convertedInput;
        }
    }

	return selection;

}
