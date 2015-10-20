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

#include "ppd_options.h"

/**
 * @file ppd_options.c this is where you need to implement the main
 * options for your program. You may however have the actual work done
 * in functions defined elsewhere.
 * @note if there is an error you should handle it within the function
 * and not simply return FALSE unless it is a fatal error for the
 * task at hand. You want people to use your software, afterall, and
 * badly behaving software doesn't get used.
 **/

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this particular function should never fail.
 **/
BOOLEAN display_items(struct ppd_system * system) {

    struct ppd_node * current = system->item_list->head;
    double price = 0.0;
    int item = 0;
    /*printf("\e[1;1H\e[2J"); */
  	printf("\n%s\n%s\n%s\n",
        "Display Items: ",
        "Items Menu",
        "----------"
    );

  	printf("%-6s\t|%-20s\t|%-10s\t|%-21s\n%s\n",
        "ID",
        "Name",
        "Available",
        "Price",
        "-----------------------------------------------"
    );

  	for(item = 0; item < system->item_list->count; item++) {
        /* calculate double value of item price */
      	price = (double)((current->data->price.dollars * 100) + (double)(current->data->price.cents)) / 100;
        /* print product in table format */
      	printf("%-6s\t|%-20s\t|%-10d\t|$ %-21.2f\n",
            current->data->id,
            current->data->name,
            current->data->on_hand,
            price
        );
        /* iterate to the next item in list */
      	current = current->next;
  	}

  	printf("\n");
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when a purchase succeeds and false when it does not
 **/
BOOLEAN purchase_item(struct ppd_system * system)
{

    /* Load variables and prepare the system for purchase */
  	BOOLEAN valid = FALSE;
    struct ppd_node * current = system->item_list->head;
  	struct coin change_system[NUM_DENOMS];

  	int denomination = 0,
        item = 0,
        inserted = 0,
        cashOnHand = 0,
        totalMoney = 0;

  	char selection[IDLEN + 1],
        coinString[PRICELEN + 2],
        * end;

  	double itemPrice = 0.0;

    /* initialise change system */
	for(denomination = 0; denomination < NUM_DENOMS; denomination++) {
		change_system[denomination].denom = denomination;
		change_system[denomination].count = 0;
  	}

    /* Print out the purchase menu and options */
  	printf("\n%s\n­­­­­­­­­­", "You have chosen to purchase an item.");

  	while (!valid) {
        if (display_items(system)){
            printf("\n%s\n", "Enter the ID of the item you want to buy (eg. I0004): ");
        }

        if (getInput( selection, (IDLEN + 2)) == FALSE) {
            printf("Oops! Invalid input.");
            return FALSE;
      	} else {
            printf("%s%s\n", "You entered: ", selection);
        }

        for (item = 0; item < system->item_list->count; item++) {
            /* check item_list for match */

            if ( strcmp(current->data->id, selection) == 0) {
      	       break;
            }
            current = current->next;
        }

      	if (item == system->item_list->count) {
    		current = system->item_list->head;
    		printf("\n%s\n", "There is no item in inventory with that ID");
    		continue;
      	}

      	if(current->data->on_hand == 0) {
    		current = system->item_list->head;
    		printf("\n%s\n", "Sorry! That item is out of stock. Pick another?");
    		continue;
      	}

      	valid = TRUE;
  	}

  	itemPrice = (double)((current->data->price.dollars * 100) + (double)(current->data->price.cents)) / 100;

  	printf("\n%s%s - %s%s\n%.2f.\n%s\n%s\n",
        "You have chosen: ",
        current->data->name,
        current->data->desc,
        "This costs: $",
        itemPrice,
        "Insert the full amount in cents using coin or note denominations.",
        "To cancel this purchase, enter a blank line."
    );

  	valid = FALSE;

  	while (itemPrice > 0) {
		printf("%s %.2f. \n", "You still need to give us $", itemPrice);
		while(valid == FALSE) {
            valid = FALSE;
            /* get user input on coins / note */
            if (getInput( coinString, (PRICELEN + 2)) == FALSE) {
                printf("\nTransaction cancelled, any input will now be refunded:\n");
				reverse(change_system);
          	} else {
                /* returned input is string, convert to int */
                inserted = (int) strtol(coinString, &end, 10);
                printf("%s%d\n", "You entered: ", inserted);
            }

  			if(inserted != 5 && inserted != 10 && inserted != 20 && inserted != 50 && inserted != 100 && inserted != 200 && inserted != 500 && inserted != 1000) {
  				printf("%s%d%s\n",
                    "Oops! You inserted: ",
                    inserted,
                    "c. You can only insert 5, 10, 100, 500 or 1000!"
                );
      			continue;
  			} else {
                valid = TRUE;
            }
		}
        printf("%s\n", "This is a valid denomination.");

		switch(inserted) {
  			case 5 :
                /* 5c inserted */
				change_system[0].count += 1;
				break;

  			case 10 :
                /* 10c inserted */
				change_system[1].count += 1;
				break;

  			case 20 :
                /* 20c inserted */
				change_system[2].count += 1;
				break;

  			case 50 :
                /* 50c inserted */
				change_system[3].count += 1;
				break;

  			case 100 :
                /* $1 inserted */
				change_system[4].count += 1;
				break;

  			case 200 :
                /* $2 inserted */
				change_system[5].count += 1;
				break;

  			case 500 :
                /* $5 inserted */
				change_system[6].count += 1;
				break;

  			case 1000 :
                /* $10 inserted */
				change_system[7].count += 1;
				break;
		}

		itemPrice = ((itemPrice * 100) - inserted) / 100;
  	}

  	itemPrice *= -1;
  	cashOnHand = itemPrice * 100;

  	for(denomination = 0; denomination < NUM_DENOMS; denomination++) {
  		system->cash_register[denomination].count += change_system[denomination].count;
  	}

  	for(denomination = 0; denomination < NUM_DENOMS; denomination++) {
		switch(system->cash_register[denomination].denom) {
  			case FIVE_CENTS :
    				totalMoney += system->cash_register[FIVE_CENTS].count * 5;
    				break;
  			case TEN_CENTS :
    				totalMoney += system->cash_register[TEN_CENTS].count * 10;
    				break;
  			case TWENTY_CENTS :
    				totalMoney += system->cash_register[TWENTY_CENTS].count * 20;
    				break;
  			case FIFTY_CENTS :
    				totalMoney += system->cash_register[FIFTY_CENTS].count * 50;
    				break;
  			case ONE_DOLLAR :
    				totalMoney += system->cash_register[ONE_DOLLAR].count * 100;
    				break;
  			case TWO_DOLLARS :
    				totalMoney += system->cash_register[TWO_DOLLARS].count * 200;
    				break;
  			case FIVE_DOLLARS :
    				totalMoney += system->cash_register[FIVE_DOLLARS].count * 500;
    				break;
  			case TEN_DOLLARS :
    				totalMoney += system->cash_register[TEN_DOLLARS].count * 1000;
    				break;
		}
  	}

  	if ((totalMoney / cashOnHand) < 1) {
    	printf("\n%s\n%s\n",
            "Sorry the machine doesn\'t have enough change for that denomination.",
            "Refunding your money now."
        );

        for(denomination = 0; denomination < NUM_DENOMS; denomination++) {
  	        system->cash_register[denomination].count -= change_system[denomination].count;
        }

        /* return denominations to change system */
  	    reverse(change_system);
  	}

  	printf("You inserted too much m8.\nYour change is: ");

  	while(itemPrice != 0.00) {
		if( system->cash_register[7].count > 0 && itemPrice >= 10 ) {
  			itemPrice -= 10;
  			printf("$10\n");
  			system->cash_register[7].count--;
		} else if ( system->cash_register[6].count > 0 && itemPrice >= 5 ) {
  			itemPrice -= 5;
  			printf("$5\n");
  			system->cash_register[6].count--;
		} else if ( system->cash_register[5].count > 0 && itemPrice >= 2 ) {
  			itemPrice -= 2;
  			printf("$2\n");
  			system->cash_register[5].count--;
		} else if ( system->cash_register[4].count > 0 && itemPrice >= 1 ) {
  			itemPrice -= 1;
  			printf("$1\n");
  			system->cash_register[4].count--;
		} else if ( system->cash_register[3].count > 0 && itemPrice >= 0.50 ) {
  			itemPrice -= 0.50;
  			printf("$0.50\n");
  			system->cash_register[3].count--;
		} else if ( system->cash_register[2].count > 0 && itemPrice >= 0.20 ) {
  			itemPrice -= 0.20;
  			printf("$0.20\n");
  			system->cash_register[2].count--;
		} else if ( system->cash_register[1].count > 0 && itemPrice >= 0.10 ) {
  			itemPrice -= 0.10;
  			printf("$0.10\n");
  			system->cash_register[1].count--;
		} 	else if ( system->cash_register[0].count > 0 && itemPrice >= 0.05 ) {
  			itemPrice -= 0.05;
  			printf("$0.05\n");
  			system->cash_register[0].count--;
		}
  	}

  	current->data->on_hand -= 1;
  	printf("Success! Thanks for your purchase. Returning to menu. \n");
  	return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when a save succeeds and false when it does not
 **/
BOOLEAN save_system(struct ppd_system * system) {
    printf("\n%s\n", "Save and Exit: ");

    int stock = 1;
    int coins = 2;

    save_list(system, stock);
    save_list(system, coins);

    printf("\n%s\n","Lists saved.");
    free_malloc(system);

    printf("\n%s\n", "Success! Saved and exiting.");

    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when adding an item succeeds and false when it does not
 **/
BOOLEAN add_item(struct ppd_system * system)
{

  	BOOLEAN valid = FALSE;

    /* ensure incoming pointer is valid */
    assert(system->item_list);

    /* declare all variables required */
  	struct ppd_node * previous;
  	struct ppd_node * current;
	struct ppd_node * new;

    int step = 0,
        number_of_product_attributes = 4,
        item = 0,
        itemPriceLength,
        itemPriceInput,
        itemCents = 0,
        itemDollars = 0,
        itemOnHand = 0;

    char itemId[IDLEN + 1],
        itemName[NAMELEN + 1],
        itemDescription[DESCLEN + 1],
        itemPriceRaw[PRICELEN + 1];
    char * priceEndPtr;

    double itemPrice = 0.0;

    printf("\n%s\n", "Adding Item: ");

    /* allocate space for the new node */
    new = malloc(sizeof(struct ppd_node));

    if (!new) {
        printf("failed to create a new node\n");
        return FALSE;
    }

    /* GET ALL THE DATA FROM USER, LOOP ON ERRORS */
    while (step < number_of_product_attributes) {
        switch (step) {
            case 0:
                /* set item ID */
                sprintf(itemId, "%s%04d", "I", (system->item_list->count + 1));
                break;

            case 1:
                /* set item name */
                printf("Enter a name for this new item: \n");
                if(getInput(itemName, (NAMELEN + 1)) == FALSE) {
                    printf("Error adding name");
                    continue;
                } else {
                    step += 1;
                }
                break;

            case 2:
                /* set item description */
                printf("Enter a description for this new item: \n");
                if(getInput(itemDescription, (DESCLEN + 1)) == FALSE) {
                    printf("Error adding description");
                    continue;
                } else {
                    step += 1;
                }
                break;

            case 3:
                /* set item price */
                /* collect user input and validate */
                printf("Enter a price for this new item in dollars: \n");
                if(getInput(itemPriceRaw, (PRICELEN + 1)) == FALSE) {
                    printf("Error adding price");
                    continue;
                } else {
                    /* convert string input to integer and validate */
                    itemPrice = strtod(itemPriceRaw, &priceEndPtr);

                    if (!itemPrice || itemPrice < 0 ) {
                        printf("Error! This is not a valid price.");
                        continue;
                    } else {

                        /* Convert price input to correct formats and add to variables.*/
                        itemDollars = (int)itemPrice;
                        itemCents = fmod((itemPrice * 100), 100);
                        itemCents -= fmod(itemCents, 5);
                        step += 1;
                    }
                }
                break;
        }
    }

    /* populate new list item */
    new->next = NULL;
    strcpy(new->data->id, itemId);
    strcpy(new->data->name, itemName);
    strcpy(new->data->desc, itemDescription);
    new->data->on_hand = DEFAULT_STOCK_LEVEL;
    new->data->price.dollars = itemDollars;
    new->data->price.cents = itemCents;

    current = system->item_list->head;

    /* **************************************************************
     * REWORK SORT - based near perfectly off my assessed LAB2 code
     * if we are at the begging of the list just assign the new node
     * to the head of the list */

    if(system->item_list->head == NULL)
    {
        system->item_list->head = new;
        /* increment the count of items in the list */
        system->item_list->count += 1;
        /* job done */
        return TRUE;
    }
    /* grab the beginning of the list and find the insertion point
     * for our data. */
    current = system->item_list->head;
    while(current != NULL && strcmp(current->data->name, new->data->name) > 0) {
        /* grab the current pointer and assign it to previous so we
         * can insert data between two nodes
         */
        previous = current;
        current = current->next;
    }

    /* insertion at the beginning of the list */
    if(previous == NULL)
    {
        new->next = system->item_list->head;
        system->item_list->head = new;
    }
    /* insertion at the end - redundant if statement because of the
     * else statement further on
     **/
    else if(!current)
    {
        new->next = NULL;
        previous->next = new;
    }
    else
    {
        previous->next = new;
        new->next = current;
    }
    /* increment the count of items in the list */
    system->item_list->count += 1;

    /* done */
    printf("Success! The new element was added into the list in sorted order.\n");
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when removing an item succeeds and false when it does not
 **/
BOOLEAN remove_item(struct ppd_system * system) {
	BOOLEAN gotInput = FALSE;

	struct ppd_node * previous = NULL;
    struct ppd_node * current = system->item_list->head;

    int item = 0;

	char delete[IDLEN + 1];

    printf("\n%s\n", "Remove Item: ");

	while (!gotInput) {

        printf("Enter the ID of the item you want to delete (eg. I0004): \n");
        if (getInput( delete, IDLEN + 1) == FALSE) {
            return FALSE;
        } else {
            gotInput = TRUE;
            /* Input received, to test now */
            for (item = 0; item < system->item_list->count; item++) {
                /* check if match found between current and element for deletion */
                if ( strcmp(current->data->id, delete) == 0) {
                    previous->next = current->next;
                    free(current->data);
                    free(current);

                    system->item_list->count--;
                    printf("Success! Element has been removed from the list.");
                    break;
                } else {
                    previous = current;
                    current = current->next;
                }
            }

            /* If we have iterated to the end of the list */
            if (item == system->item_list->count) {
                current = system->item_list->head;
                printf("\nitem not found\n");
                continue;
            }
        }
	}

    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_stock(struct ppd_system * system) {
    struct ppd_node * current = system->item_list->head;
	int item;
	printf("\n%s\n", "Reset Stock: ");

	 for (item = 0; item < system->item_list->count; item++) {
		 current->data->on_hand = DEFAULT_STOCK_LEVEL;
		 current = current->next;
	 }

	printf("\n%s\n", "Success! Stock has been reset to the defaults levels.");

    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/

BOOLEAN reset_coins(struct ppd_system * system) {
    int denomination;
	printf("\n%s\n", "Reset Coins: ");

	for(denomination = 0; denomination < NUM_DENOMS; denomination++) {
		system->cash_register[denomination].count = DEFAULT_COIN_COUNT;
	}

   printf("\n%s\n", "Success! Coins have been reset to their defaults levels.");

    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this function cannot fail
 **/
BOOLEAN display_coins(struct ppd_system * system)
{
    int denominations = 0;
	printf("\n%s\n%s\n%-15s| %5s\n-\n",
        "Display Coins: ",
        "Coins Summary",
        "Denomination",
        "Count"
    );

	for(denominations = 0; denominations < NUM_DENOMS; denominations++)
	{
		switch(system->cash_register[denominations].denom)
		{
			case FIVE_CENTS :
				printf("%-15s|    %-5d\n","5 cents",system->cash_register[denominations].count);
				break;
			case TEN_CENTS :
				printf("%-15s |    %-5d\n","10 cents",system->cash_register[denominations].count);
				break;
			case TWENTY_CENTS :
				printf("%-15s |    %-5d\n","20 cents",system->cash_register[denominations].count);
				break;
			case FIFTY_CENTS :
				printf("%-15s |    %-5d\n","50 cents",system->cash_register[denominations].count);
				break;
			case ONE_DOLLAR :
				printf("%-15s |    %-5d\n","1 dollar",system->cash_register[denominations].count);
				break;
			case TWO_DOLLARS :
				printf("%-15s |    %-5d\n","2 dollar",system->cash_register[denominations].count);
				break;
			case FIVE_DOLLARS :
				printf("%-15s |    %-5d\n","5 dollar",system->cash_register[denominations].count);
				break;
			case TEN_DOLLARS :
				printf("%-15s |    %-5d\n","10 dollar",system->cash_register[denominations].count);
				break;
		}

	}

    return TRUE;
}
