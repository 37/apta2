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
/**
 * @file ppd_menu.h defines the @ref menu_item type and the init_menu
 * function which you need to call to initialise it
 **/
#ifndef MENU_H
#define MENU_H
/**
 * The maximum length of a menu item's text
 **/
#define MENU_NAME_LEN 50

/**
 * represents a menu item to be displayed and executed in the program
 **/
typedef struct menu_item {
    /**
     * the text to be displayed in the menu
     **/
    char name[MENU_NAME_LEN + 1];
    /**
     * pointer to the function to be called when this item is selected
     **/
    BOOLEAN (*function)(struct ppd_system*);
} menu_item;
/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of @ref menu_item with a name and a pointer to the function
 * that will be called for that function.
 *
 * Please note that you are expected to initialise the code in such a way
 * that the code will be easy to maintain. Do not hard code values, and
 * do not use magic numbers for array indexes etc. You are expected to use
 * good coding practices at all times. Do not hardcode array indexes -
 * you are expected to write code that is maintainable which in this case
 * means initialization in a loop. A typedef might assist in making this
 * code more readable.
 **/
void init_menu( struct menu_item*);
#endif
