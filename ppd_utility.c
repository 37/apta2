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

#include "ppd_utility.h"
/**
 * @file ppd_utility.c contains implementations of important functions for
 * the system. If you are not sure where to implement a new function,
 * here is probably a good spot.
 **/


BOOLEAN getInput(char writeTo[], int max) {
    /* collect user input and validate */
    char itemPriceRaw[max];

    fgets(itemPriceRaw, (PRICELEN + 1), stdin);

    itemPriceLength = strlen(itemPriceRaw) - 1;
    if (itemPriceRaw[itemPriceLength] == '\n'){
        itemPriceRaw[itemPriceLength] = '\0';
    } else {
        return FALSE;
    }

    strcpy(writeTo, itemPriceRaw);
    return TRUE;
}

BOOLEAN exit_program(struct ppd_system * system)
{
	printf("Now exiting program.\n");
	system_free(system);
	return TRUE;
}

void save_list(struct ppd_system* system, char * data_type) {

    struct ppd_node * current = system->item_list->head;

    int count = 0,
        denomination = 0;

    /* using IF to split functionality as you can't easily switch a string */
    if (strcmp(data_type, "stock") == 0) {

        /* code */
        double itemPrice = 0.0;
        FILE * openFile = fopen(system->coin_file_name, "w+");
        if (!openFile) {
            printf("Oops! Couldn\'t open the coins list.\n");
        }

        for (count = 0; count < system->item_list->count; count++) {

            /* calculate and set itemPrice for item*/
            itemPrice = (double)((current->data->price.dollars * 100) + current->data->price.cents) / 100;
            /* write changes to items file */
            fprintf(openFile, "%s|%s|%s|%.2f|%d\n",
                current->data->id,
                current->data->name,
                current->data->desc,
                itemPrice,
                current->data->on_hand
            );

            current = current->next;
        }
    } else if (strcmp(data_type, "coins") == 0) {
        /* code */

        FILE * openFile = fopen(system->stock_file_name, "w+");

        if (!openFile) {
            printf("Oops! Couldn\'t open the coins list.\n");
        }

        /* write changes to coins file */
        for(denomination = NUM_DENOMS; denomination >= 0; denomination--) {
            switch(system->cash_register[denomination].denom) {
                case FIVE_CENTS :
                    fprintf(openFile, "%s%d\n",
                        "5,",
                        system->cash_register[denomination].count
                    );
                    break;
                case TEN_CENTS :
                    fprintf(openFile, "%s%d\n",
                        "10,",
                        system->cash_register[denomination].count
                    );
                    break;
                case TWENTY_CENTS :
                    fprintf(openFile, "%s%d\n",
                        "20,",
                        system->cash_register[denomination].count
                    );
                    break;
                case FIFTY_CENTS :
                    fprintf(openFile, "%s%d\n",
                        "50,",
                        system->cash_register[denomination].count
                    );
                    break;
                case ONE_DOLLAR :
                    fprintf(openFile, "%s%d\n",
                        "100,",
                        system->cash_register[denomination].count
                    );
                    break;
                case TWO_DOLLARS :
                    fprintf(openFile,"%s%d\n",
                        "200,",
                        system->cash_register[denomination].count
                    );
                    break;
                case FIVE_DOLLARS :
                    fprintf(openFile, "%s%d\n",
                        "500,",
                        system->cash_register[denomination].count
                    );
                    break;
                case TEN_DOLLARS :
                    fprintf(openFile, "%s%d\n",
                        "1000,",
                        system->cash_register[denomination].count
                    );
                    break;
            }
        }
    }

    /* changes writte, close file */
    printf("%s%s%s\n",
        "List for ",
        data_type,
        " successfully saved."
    );

    fclose(openFile);
}


void free_malloc(struct ppd_system* system) {
    struct ppd_node * prev = system->item_list->head;
	struct ppd_node * next = system->item_list->head;
	int i = 0;

	for (i = 0; i < system->item_list->count; i++)
	{
		next = prev->next;
		free(prev->data);
		free(prev);
		prev = next;
	}

	free(system->item_list);
}



/**
 * @param system a pointer to a @ref ppd_system struct that contains
 * all the data in the system we are manipulating
 * @param coins_name the name of the coins file
 * @param stock name the name of the stock file
 **/
BOOLEAN load_data(struct ppd_system * system, const char * coins_name, const char * stock_name) {

    FILE * coinFile = fopen(system->coin_file_name ,"r");
    FILE * stockFile = fopen(system->stock_file_name ,"r");

    ppd_item_attr product_object_step = 0;
    BOOLEAN loadInProgress = TRUE;

	struct ppd_node * current = system->item_list->head;

    int currentItem = 0,
        currentCoin = 0,
        denomination = (NUM_DENOMS - 1);

    char line[LINECHARS],
        * chunk;

    double itemPrice = 0.0;
    unsigned itemPriceDollars = 0;
    unsigned itemPriceCents = 0;

    if (!coinFile || !stockFile) {
        printf("Oops! There was a problem opening your data files. Please check them and try again.\n");
        return FALSE;
    } else {
        printf("successfully opened data files.\n");
    }

    while (fgets(line, LINECHARS , stockFile) {

        /* split and chunk lines by the '|' delimeter */
        chunk = strtok(line, "|");
		product_object_step = 0;

		while(chunk != NULL) {

            /* run chunk against the product object */
			switch(product_object_step) {
    			case id:
    				strcpy(current->data->id, chunk);
    				break;

    			case name:
    				strcpy(current->data->name, chunk);
    				break;

    			case description:
    				strcpy(current->data->desc, chunk);
    				break;

    			case price:
    				itemPriceDollars = (int) strtol(chunk, NULL,10);
    				itemPriceCents = strtod (chunk, NULL);
    				itemPriceCents = fmod((itemPriceCents * 100), 100);
    				itemPriceCents -= fmod(itemPriceCents, 5);
    				current->data->price.dollars = priceDollars;
    				current->data->price.cents = priceCents;
    				break;

    			case onHand:
    				current->data->on_hand = atoi(chunk);
    				break;
			}

    		token = strtok(NULL, STOCK_DELIM);
    		product_object_step += 1;

		}

        printf("item %d: %s %s %s %d %d %d\n",
            itemNo,
            current->data->id,
            current->data->name,
            current->data->desc,
            current->data->price.dollars,
            current->data->price.cents,
            current->data->on_hand
        );

        current->next = malloc(sizeof(struct ppd_node)),
        current->next->data = malloc(sizeof(struct ppd_stock)
        itemNo += 1;
		current = current->next;
		system->item_list->count++;

    }

    printf("\n Success! Stock has been validated and loaded into memory.");

    while(fgets(line, COINLEN + 1, coins)) {

        if (denomination < 0) {
            printf("Oops! Your coin file contains an invalid line. Check it and try again.");
            return FALSE;
        }

        chunk = strtok(line, COIN_DELIM);
        chunk = strtok(NULL, COIN_DELIM);
        currentCoin = (int) strtol(token, NULL, 10);

        system->cash_register[i].count = currentCoin;
        printf("Success! Coins validated and loaded into memory.");
        denomination -= 1;

    }

    fclose(stockFile);
    fclose(coinFile);
    return TRUE;
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all
 * the data for the system we are creating
 **/
BOOLEAN system_init(struct ppd_system * system)
{
    int denomination = 0;
    void* listMem = malloc(sizeof(struct ppd_list ));
    void* nodeMem = malloc(sizeof(struct ppd_node));
    void* stockMem = malloc(sizeof(struct ppd_stock));

    for(denomination; denomination < NUM_DENOMS; denomination++) {
        system->cash_register[i].count = 0;
        system->cash_register[i].denom = denomination;
    }

    system->item_list = listMem;
    system->item_list->head = nodeMem;
    system->item_list->head->data = stockMem;
    system->item_list->head->next = stockMem;
    system->item_list->count = 0;

    /* unsure if needs strcpy or can just assign str value */
    strcpy(system->item_list->head->data->id, "");
	strcpy(system->item_list->head->data->name, "");
	strcpy(system->item_list->head->data->desc, "");

	system->item_list->head->data->on_hand = 0;
	system->item_list->head->data->price.dollars = 0;
	system->item_list->head->data->price.cents = 0;

    return TRUE;
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all
 * the data for the system we are creating
 **/
void system_free(struct ppd_system * system)
{
    struct ppd_node * prev = system->item_list->head;
    struct ppd_node * next = system->item_list->head;

    int item = 0;

    /* iterate through item_list and all elements */
    for (item = 0; item < system->item_list->count; item++)
    {
        next = prev->next;
        free(prev->data);
        free(prev);
        prev = next;
    }

    /* once all list elements have been freed, free the list as a whole */
    free(system->item_list);
}
