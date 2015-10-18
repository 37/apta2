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
/* void init_menu( struct menu_item* menu, int i) */
void init_menu( struct menu_item* menu)
{
int i = 0;
char * menuItemNames[NUM_OF_MENUITEMS] = {

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

BOOLEAN (*function[NUM_OF_MENUITEMS])(struct ppd_system*) = {

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

for(i = 0;i < NUM_OF_MENUITEMS; i++)
{
	strcpy(menu[i].name,menuItemNames[i]);

	menu[i].function = function[i];
}


/*
switch(i)
{
	case 0 :
	strcpy(menu->name,"Display Items");
	menu->function = display_items;
	break;
	case 1 :
	strcpy(menu->name,"Purchase Items");
	menu->function = purchase_item;
	break;
	case 2 :
	strcpy(menu->name,"Save and Exit");
	menu->function = save_system;
	break;
	case 3 :
	strcpy(menu->name,"Add Item");
	menu->function = add_item;
	break;
	case 4 :
	strcpy(menu->name,"Remove Item");
	menu->function = remove_item;
	break;
	case 5 :
	strcpy(menu->name,"Display Coins");
	menu->function = display_coins;
	break;
	case 6 :
	strcpy(menu->name,"Reset Stock");
	menu->function = reset_stock;
	break;
	case 7 :
	strcpy(menu->name,"Reset Coins");
	menu->function = reset_coins;
	break;
	case 8 :
	strcpy(menu->name,"Abort Program");
	menu->function = abort_program;
	break;

}
*/


}

int run_menu( struct menu_item options[]) {
		int index = 0, k = 0;
		/* clear console  and print menu */
		printf("\e[1;1H\e[2J%s\n", "Vending Machine Menu:");

		for( index = 0; index < NUM_OF_MENUITEMS; index++) {

				printf("%d|\t%s\n", (index + 1), options[index].name);

				if(index == 2) {
						printf("\n%s\n", "Administrator options:");
				}

		}

		printf("\n%s\n", "What action would you like to take? (1-9) :");

		getInteger(&k, 1, "", 1, 9);

		return k - 1;


}
