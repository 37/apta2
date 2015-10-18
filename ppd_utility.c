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

void read_rest_of_line(void)
{
    int ch;
    /* keep retrieving characters from stdin until we
     * are at the end of the buffer
     */
    while(ch = getc(stdin), ch!='\n' && ch != EOF)
        ;
    /* reset error flags on stdin */
    clearerr(stdin);
}

/**
 * @param system a pointer to a @ref ppd_system struct that contains
 * all the data in the system we are manipulating
 * @param coins_name the name of the coins file
 * @param stock name the name of the stock file
 **/
BOOLEAN load_data(struct ppd_system * system , const char * coins_name,
const char * stock_name)
{
	FILE * stock;
	FILE * coins;
	char line[DESCLEN + NAMELEN + IDLEN + MAX_ON_HAND_LEN + MAX_PRICE_LEN + 1];
	char * token;
	stock_detail currtoken = 0;
	int itemNo = 0;
	int coincount = 0,i = NUM_DENOMS - 1;
	unsigned priceDollars = 0;
	double priceCents = 0.0;





	struct ppd_node * current =system->item_list->head;






	stock = fopen(system->stock_file_name ,"r");
	coins = fopen(system->coin_file_name ,"r");

	if(stock == NULL)
	{
	printf("Error opening stock file\n");
	return FALSE;
	}
	else if (coins == NULL)
	{
	printf("Error opening coins file\n");
	return FALSE;
	}
	else
	{
	printf("files successfully opened\n");
	}

	while(fgets(line,DESCLEN + NAMELEN + IDLEN + MAX_ON_HAND_LEN + MAX_PRICE_LEN + 1,stock) != NULL)
	{
	token = strtok(line,STOCK_DELIM);
	currtoken = 0;




		while(token != NULL)
		{

			switch(currtoken)
			{
			case ID:
			/*	strcpy(system->item_list->head->data->id, token); */
				strcpy(current->data->id, token);
				break;
			case NAME:
			/*	strcpy(system->item_list->head->data->name, token); */
				strcpy(current->data->name, token);
				break;
			case DESC:
			/*	strcpy(system->item_list->head->data->desc, token); */
				strcpy(current->data->desc, token);
				break;
			case PRICE:
			/*	system->item_list->head->data->price.dollars = atoi(token); */
			/*	system->item_list->head->data->price.cents = atof(token) - floor(atoi(token)); */
				priceDollars = (int) strtol(token, NULL,10);
				priceCents = strtod (token, NULL);



				priceCents = fmod((priceCents * 100), 100 );
				priceCents -= fmod(priceCents,5);

				current->data->price.dollars = priceDollars;
				current->data->price.cents = priceCents;
				break;
			case ON_HAND:
			/*	system->item_list->head->data->on_hand = atoi(token); */
				current->data->on_hand = atoi(token);
				break;
			}



		token = strtok(NULL,STOCK_DELIM);
		currtoken++;



		}
			/*printf("item %d: %s %s %s %d %d %d\n",itemNo,system->item_list->head->data->id,
			system->item_list->head->data->name,system->item_list->head->data->desc,
			system->item_list->head->data->price.dollars,
			system->item_list->head->data->price.cents,system->item_list->head->data->on_hand);*/

			printf("item %d: %s %s %s %d %d %d\n",itemNo,current->data->id,
			current->data->name,current->data->desc,
			current->data->price.dollars,
			current->data->price.cents,current->data->on_hand);

			itemNo++;







			current->next = malloc(sizeof(struct ppd_node));
			current->next->data = malloc(sizeof(struct ppd_stock));


			current = current->next;

			system->item_list->count++;







	}
	printf("\nstock successfully loaded\n");








	while(fgets(line,MAX_COINLEN + 1,coins) != NULL)
	{

	if (i < 0)
	{
	printf("Error; invalid format of coins file, aka too many lines or incorrect delimeters");
	return FALSE;
	}

	token = strtok(line,COIN_DELIM);

	token = strtok(NULL,COIN_DELIM);

	coincount = (int) strtol(token, NULL,10);

	system->cash_register[i].count = coincount;

	printf(" entry %d has %d \n",system->cash_register[i].denom,system->cash_register[i].count);

	i--;







	}

	printf("\ncoins successfully loaded\n");

	printf("\nall data successfully loaded, closing files...\n\n");
	fclose(stock);
	fclose(coins);

	system_sort(system);

    return TRUE;
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all
 * the data for the system we are creating
 **/
BOOLEAN system_init(struct ppd_system * system)
{
	int i = 0;
	/* old (sizeof(system->cash_register)/sizeof(system->cash_register[0])) */
	for(i = 0; i < NUM_DENOMS; i++)
	{
		system->cash_register[i].denom = i;

		system->cash_register[i].count = 0;
	}

	/* system->stock_file_name = *argv[1]; */

	/* system->coin_file_name = *argv[2]; */

	system->item_list = malloc(sizeof(struct ppd_list ));
	system->item_list->head = malloc(sizeof(struct ppd_node));
	system->item_list->head->data = malloc(sizeof(struct ppd_stock));
	system->item_list->head->next = malloc(sizeof(struct ppd_stock));

	system->item_list->count = 0;

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


BOOLEAN getInteger(int* integer, unsigned length, char* prompt, int min, int max)
 {
    int finished = FALSE;
    char tempString[MAXINT + 2];
    int tempInteger = 0;
    char* endPtr;
	char * line;

    /* Continue to interact with the user until the input is valid. */
    do
    {
       /* Provide a custom prompt. */


       /* Accept input. "+2" is for the \n and \0 characters. */
       line = fgets(tempString, length + 2, stdin);

	    if(line == NULL) {
			return FALSE;
		}

		if(strcmp(tempString, "\n") == 0) {
			return FALSE;
		}

       /* A string that doesn't have a newline character is too long. */
       if (tempString[strlen(tempString) - 1] != '\n')
       {
          printf("Input was too long.\n");
           read_rest_of_line();
       }
       else
       {
          /* Overwrite the \n character with \0. */
          tempString[strlen(tempString) - 1] = '\0';

          /* Convert string to an integer. */
          tempInteger = (int) strtol(tempString, &endPtr, 10);

          /* Validate integer result. */
          if (strcmp(endPtr, "") != 0)
          {
             printf("Input was not numeric.\n");
          }
          else if (tempInteger < min || tempInteger > max)
          {
             printf("Input was not within range %d - %d.\n", min, max);
          }
          else
          {
             finished = TRUE;
          }
       }
    } while (finished == FALSE);

   /* Make the result integer available to calling function. */
    *integer = tempInteger;

    return TRUE;
 }

 BOOLEAN readStringInput(char theString[], int sizeLimit, char *message, char *errorMessage) {

    char tempString[DESCLEN + NAMELEN + IDLEN + MAX_ON_HAND_LEN + MAX_PRICE_LEN + 2];
	char * line;
    int finished = FALSE;

    do {
		/* default prompt to user*/
        printf("%s", message);

		/* sets the return value of fgets to the char point line*/
        line = fgets(tempString, sizeLimit + 2, stdin);
		/*if fgets returns null meaning ctrl D was entered, return FALSE and kill the function, meaning return to main menu*/
		if(line == NULL) {
			return FALSE;
		}
		if(strcmp(tempString, "\n") == 0) {
			return FALSE;
		}
		/* if the user exceed the size and the last char entered isnt a return key enter, error message and clear buffer*/
        if(tempString[strlen(tempString) - 1] != '\n') {

            printf("%s\n", errorMessage);

            read_rest_of_line();

        } else {
			/*gets rid of the new line char and replaces it with a null terminator*/
            tempString[strlen(tempString) - 1] = '\0';

            finished = TRUE;

        }

    } while (!finished);

    strcpy(theString, tempString);
	return TRUE;
}

void system_sort(struct ppd_system * system)
{
	struct ppd_node * linkedlist[100];
	struct ppd_node * curr = system->item_list->head;
	struct ppd_stock * temp;
	int i = 0,j = 0;

	for(i = 0; i < system->item_list->count; i++)
	{
		linkedlist[i] = curr;
		curr = curr->next;

	}

	for(i = 0; i < system->item_list->count; i++)
	{
		for(j = i + 1;j < system->item_list->count; j++)
		{

		if( strcmp(linkedlist[i]->data->name,linkedlist[j]->data->name) > 0)
		{
		temp = linkedlist[i]->data;
		linkedlist[i]->data = linkedlist[j]->data;
		linkedlist[j]->data = temp;
		}

		}




	}



}
