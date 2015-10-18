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
BOOLEAN display_items(struct ppd_system * system)
{
    struct ppd_node * ptr = system->item_list->head;
	int i = 0;
	double price = 0.0;

	printf("\n\nDisplay Items\n\n");

	printf("Items Menu");
	printf("\n­­­­­­­­­­\n");
	printf("%-6s|%-20s|%-10s|%-21s\n","ID","Name","Available","Price");
	printf("­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­\n");
	for(i = 0; i < system->item_list->count; i++)
	{
	price = (double)((ptr->data->price.dollars * 100) + (double)(ptr->data->price.cents)) / 100;
	printf("%-6s|%-20s|%-10d|$ %-21.2f\n",ptr->data->id,ptr->data->name,ptr->data->on_hand,price);
	ptr = ptr->next;
	}
	printf("\n");
    return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when a purchase succeeds and false when it does not
 **/
BOOLEAN purchase_item(struct ppd_system * system)
{
    struct ppd_node * ptr = system->item_list->head;
	BOOLEAN valid = FALSE;
	char input[IDLEN + 1];
	double price = 0.0;
	int inputmoney = 0,i = 0,changecheck = 0,totalmoney = 0;

	struct coin tempcash_register[NUM_DENOMS];

		for(i = 0; i < NUM_DENOMS; i++)
	{
		tempcash_register[i].denom = i;

		tempcash_register[i].count = 0;
	}





	printf("\n\nPurchase Items");
    printf("\n­­­­­­­­­­\n");

	do
	{

	 if(readStringInput(input,IDLEN + 1, "Please enter the id of the item you wish to purchase:", "Error; invalid input") == FALSE)
	 {
		 return FALSE;
	 }

	 for (i = 0; i < system->item_list->count; i++)
	 {
		 if ( strcmp(ptr->data->id,input) == 0)
		 {
			 break;
		 }
		 ptr = ptr->next;
	 }

	if (i == system->item_list->count)
	{
		ptr = system->item_list->head;
		printf("\nitem not found\n");
		continue;
	}

	if(ptr->data->on_hand == 0)
	{
		ptr = system->item_list->head;
		printf("\nSorry; product is sold out\n");
		continue;
	}

	valid = TRUE;

	} while (!valid);

	price = (double)((ptr->data->price.dollars * 100) + (double)(ptr->data->price.cents)) / 100;

	printf("\nYou have selected: %s - %s this will cost you $%.2f.\n",ptr->data->name,ptr->data->desc,price);

	printf("Please hand over the money – type in the value of each note/coin in cents.\n");

	printf("Press enter or ctrl­d on a new line to cancel this purchase:\n");

	valid = FALSE;

	while (price > 0)
	{
		printf("You still need to give us $%.2f: ",price);

		do
		{	valid = FALSE;
			if(getInteger(&inputmoney, 4, "", 5, 1000) == FALSE)
			{
				printf("\nTransaction cancelled, any input will now be refunded:\n");
				refund(tempcash_register);
				return FALSE;
			}

			if(inputmoney != 5 && inputmoney != 10 &&
			  inputmoney != 20 && inputmoney != 50 &&
			  inputmoney != 100 && inputmoney != 200 &&
			  inputmoney != 500 && inputmoney != 1000)
			  {
				printf("\nError; you entered %d; please enter correct denominations only aka 5,10,100,500\nTry again:",inputmoney);
				continue;
			  }

			valid = TRUE;

		} while (!valid);

		switch(inputmoney)
		{
			case 5 :
				tempcash_register[0].count++;
				break;
			case 10 :
				tempcash_register[1].count++;
				break;
			case 20 :
				tempcash_register[2].count++;
				break;
			case 50 :
				tempcash_register[3].count++;
				break;
			case 100 :
				tempcash_register[4].count++;
				break;
			case 200 :
				tempcash_register[5].count++;
				break;
			case 500 :
				tempcash_register[6].count++;
				break;
			case 1000 :
				tempcash_register[7].count++;
				break;
		}


		price = ((price * 100) - inputmoney) / 100;
	}


	price *= -1;

	changecheck = price * 100;




	for(i = 0; i < NUM_DENOMS; i++)
	{

		system->cash_register[i].count += tempcash_register[i].count;

	}

	for(i = 0; i < NUM_DENOMS; i++)
	{
		switch(system->cash_register[i].denom)
		{
			case FIVE_CENTS :
				totalmoney += system->cash_register[FIVE_CENTS].count * 5;
				break;
			case TEN_CENTS :
				totalmoney += system->cash_register[TEN_CENTS].count * 10;
				break;
			case TWENTY_CENTS :
				totalmoney += system->cash_register[TWENTY_CENTS].count * 20;
				break;
			case FIFTY_CENTS :
				totalmoney += system->cash_register[FIFTY_CENTS].count * 50;
				break;
			case ONE_DOLLAR :
				totalmoney += system->cash_register[ONE_DOLLAR].count * 100;
				break;
			case TWO_DOLLARS :
				totalmoney += system->cash_register[TWO_DOLLARS].count * 200;
				break;
			case FIVE_DOLLARS :
				totalmoney += system->cash_register[FIVE_DOLLARS].count * 500;
				break;
			case TEN_DOLLARS :
				totalmoney += system->cash_register[TEN_DOLLARS].count * 1000;
				break;
		}
	/* printf("\n\n%d %d %d\n\n",changecheck,totalmoney,(totalmoney / changecheck)); */

	}
	/* printf("\n\n%d %d %d\n\n",changecheck,totalmoney,(totalmoney / changecheck)); */
	if ((totalmoney / changecheck) < 1)
	{
		printf("\nSorry there is not enough change in the system for the amount you entered\nYour money will now be refunded:\n");

		for(i = 0; i < NUM_DENOMS; i++)
	{
		system->cash_register[i].count -= tempcash_register[i].count;

	}
	refund(tempcash_register);
	}

	printf("You gave $%.2f extra\nYour change is:\n",price);

	while(price != 0.00)
	{
		if(price >= 10 && system->cash_register[7].count > 0)
		{
			price -= 10;
			printf("10 Dollars\n");
			system->cash_register[7].count--;
		}
		else if(price >= 5 && system->cash_register[6].count > 0)
		{
			price -= 5;
			printf("5 Dollars\n");
			system->cash_register[6].count--;
		}
		else if(price >= 2 && system->cash_register[5].count > 0)
		{
			price -= 2;
			printf("2 Dollars\n");
			system->cash_register[5].count--;
		}
		else if(price >= 1 && system->cash_register[4].count > 0)
		{
			price -= 1;
			printf("1 Dollar\n");
			system->cash_register[4].count--;
		}
		else if(price >= 0.50 && system->cash_register[3].count > 0)
		{
			price -= 0.50;
			printf("50 Cents\n");
			system->cash_register[3].count--;
		}
		else if(price >= 0.20 && system->cash_register[2].count > 0)
		{
			price -= 0.20;
			printf("20 Cents\n");
			system->cash_register[2].count--;
		}
		else if(price >= 0.10 && system->cash_register[1].count > 0)
		{
			price -= 0.10;
			printf("10 Cents\n");
			system->cash_register[1].count--;
		}
		else if(price >= 0.05 && system->cash_register[0].count > 0)
		{
			price -= 0.05;
			printf("5 Cents\n");
			system->cash_register[0].count--;
		}
	}

	ptr->data->on_hand--;

	printf("Thank you, Here is your %s\n",ptr->data->name);
	printf("Please come again soon\n");

	return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when a save succeeds and false when it does not
 **/
BOOLEAN save_system(struct ppd_system * system)
{
    FILE * stock;
    FILE * coins;
    int i = 0;
    double price = 0.0;
    struct ppd_node * ptr = system->item_list->head;
	printf("\n\nSave and Exit\n\n");

    stock = fopen(system->stock_file_name ,"w+");
    coins = fopen(system->coin_file_name ,"w+");

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

    for (i = 0; i < system->item_list->count; i++) {

        price = (double)((ptr->data->price.dollars * 100) + ptr->data->price.cents) / 100;

        fprintf(stock, "%s|%s|%s|%.2f|%d\n",ptr->data->id,ptr->data->name,ptr->data->desc,price,ptr->data->on_hand);

        ptr = ptr->next;
    }

    for(i = NUM_DENOMS; i >= 0; i--)
    {
        switch(system->cash_register[i].denom)
        {
            case TEN_DOLLARS :
                fprintf(coins,"1000,%d\n",system->cash_register[i].count);
                break;
            case FIVE_DOLLARS :
                fprintf(coins,"500,%d\n",system->cash_register[i].count);
                break;
            case TWO_DOLLARS :
                fprintf(coins,"200,%d\n",system->cash_register[i].count);
                break;
            case ONE_DOLLAR :
                fprintf(coins,"100,%d\n",system->cash_register[i].count);
                break;
            case FIFTY_CENTS :
                fprintf(coins,"50,%d\n",system->cash_register[i].count);
                break;
            case TWENTY_CENTS :
                fprintf(coins,"20,%d\n",system->cash_register[i].count);
                break;
            case TEN_CENTS :
                fprintf(coins,"10,%d\n",system->cash_register[i].count);
                break;
            case FIVE_CENTS :
                fprintf(coins,"5,%d\n",system->cash_register[i].count);
                break;

        }


    }

    printf("\n\nAll data successfully saved, closing files and exiting...\n\n");

    fclose(stock);
    fclose(coins);

	system_free(system);

	return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when adding an item succeeds and false when it does not
 **/
BOOLEAN add_item(struct ppd_system * system)
{
	BOOLEAN finished = FALSE;
	BOOLEAN valid = FALSE;
	int i = 0;
	char tempid[IDLEN + 1];
	char tempname[NAMELEN + 1];
	char tempdesc[DESCLEN + 1];
	char tempprice[MAX_PRICE_LEN + 1];
	stock_detail newstockdetail = 0;
	struct ppd_node * ptr = system->item_list->head;
	int dollars = 0, cents = 0;
	double price = 0.0;


	for(i = 0; i < system->item_list->count - 1; i++)
	{
	ptr = ptr->next;
	}


	ptr->next = malloc(sizeof(struct ppd_node));
	ptr->next->data = malloc(sizeof(struct ppd_stock));


	strcpy(ptr->next->data->id,"");
	strcpy(ptr->next->data->name,"");
	strcpy(ptr->next->data->desc,"");
	ptr->next->data->on_hand = 0;
	ptr->next->data->price.dollars = dollars;
	ptr->next->data->price.cents = cents;

    printf("\n\nAdd Item\n\n");

	while(!finished)
	{

		switch(newstockdetail)
		{
		case ID :
			/* snprintf (tempid,IDLEN + 1,"I%04d\0", system->item_list->count + 1); */
			sprintf (tempid,"I%04d", system->item_list->count + 1);





			strcpy(ptr->next->data->id,tempid);

			break;
		case NAME :


			if(readStringInput(tempname,NAMELEN + 1, "\nEnter the item name:", "Error; invalid input") == FALSE)
			{
				free(ptr->next->data);
				free(ptr->next);

				return FALSE;
			}






			strcpy(ptr->next->data->name,tempname);



			break;
		case DESC :

			if(readStringInput(tempdesc,DESCLEN + 1, "\nEnter the item description:", "Error; invalid input") == FALSE)
			{
				free(ptr->next->data);
				free(ptr->next);

			}






			strcpy(ptr->next->data->desc,tempdesc);


			break;
		case PRICE :

			while(!valid)
			{
			if(readStringInput(tempprice,MAX_PRICE_LEN + 1, "\nEnter the price for this item aka 2.50:", "Error; invalid input") == FALSE)
			{
				free(ptr->next->data);
				free(ptr->next);

			}





			price = strtod(tempprice, NULL);
			if (price == 0.0)
			{
			printf("Error with input=%.2f; could not read input as price, please check only numbers are input",price);
			continue;
			}
			else {
			valid = TRUE;
			}
			}
			dollars = (int)price;
			cents = fmod((price * 100),100);

			cents -= fmod(cents,5);

			ptr->next->data->price.dollars = dollars;
			ptr->next->data->price.cents = cents;
			break;
		case ON_HAND :
			ptr->next->data->on_hand = DEFAULT_STOCK_LEVEL;



			finished = TRUE;
			break;

		}
	newstockdetail++;
	}



	system->item_list->count++;

	system_sort(system);

    return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when removing an item succeeds and false when it does not
 **/
BOOLEAN remove_item(struct ppd_system * system)
{
	struct ppd_node * delptr = system->item_list->head;
	struct ppd_node * prevdelptr = system->item_list->head;
	int i = 0,j = 0;
	char input[IDLEN + 1];
	BOOLEAN valid = FALSE;
    printf("\n\nRemove Item\n\n");

	do
	{

	 if(readStringInput(input,IDLEN + 1, "Enter the item id of the item to remove from the menu:", "Error; invalid input") == FALSE)
	 {
		 return FALSE;
	 }

	 for (i = 0; i < system->item_list->count; i++)
	 {
		 if ( strcmp(delptr->data->id,input) == 0)
		 {
			 break;
		 }
		 delptr = delptr->next;
	 }

	if (i == system->item_list->count)
	{
		delptr = system->item_list->head;
		printf("\nitem not found\n");
		continue;
	}


	valid = TRUE;

	} while (!valid);

	if(delptr == system->item_list->head)
	{
	system->item_list->head = delptr->next;

	printf("\n%s - %s - %s has been removed from the system.\n",delptr->data->id,delptr->data->name,delptr->data->desc);


	free(delptr->data);
	free(delptr);
	system->item_list->count--;
	return FALSE;
	}

	for (j = 0; j < i - 1; j++)
	{

		 prevdelptr = prevdelptr->next;
	}

	printf("\n%s - %s - %s has been removed from the system.\n",delptr->data->id,delptr->data->name,delptr->data->desc);

	prevdelptr->next = delptr->next;

	free(delptr->data);
	free(delptr);

	 system->item_list->count--;

    return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_stock(struct ppd_system * system)
{
	struct ppd_node * ptr = system->item_list->head;
	int i = 0;
	printf("\n\nReset Stock\n\n");

	 for (i = 0; i < system->item_list->count; i++)
	 {
		 ptr->data->on_hand = DEFAULT_STOCK_LEVEL;
		 ptr = ptr->next;
	 }

	printf("\n\nall stock has been reset to the default level of %d \n\n",DEFAULT_STOCK_LEVEL);

    return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_coins(struct ppd_system * system)
{
	int i = 0;
	printf("\n\nReset Coins\n\n");

	for(i = 0; i < NUM_DENOMS; i++)
	{
		system->cash_register[i].count = DEFAULT_COIN_COUNT;
	}

   printf("\n\nall coins have been reset to the default level of %d \n\n",DEFAULT_COIN_COUNT);

    return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this function cannot fail
 **/
BOOLEAN display_coins(struct ppd_system * system)
{
	int i = 0;
	printf("\n\nDisplay Coins\n\n");

	printf("Coins Summary");
	printf("\n­­­­­­­­­­­­­\n");
	printf("%-15s| %5s\n","Denomination","Count");
	printf("­­­­­­­­­­­­­­­­­­­­­-\n");
	for(i = 0; i < NUM_DENOMS; i++)
	{
		switch(system->cash_register[i].denom)
		{
			case FIVE_CENTS :
				printf("%-15s|    %-5d\n","5 cents",system->cash_register[i].count);
				break;
			case TEN_CENTS :
				printf("%-15s |    %-5d\n","10 cents",system->cash_register[i].count);
				break;
			case TWENTY_CENTS :
				printf("%-15s |    %-5d\n","20 cents",system->cash_register[i].count);
				break;
			case FIFTY_CENTS :
				printf("%-15s |    %-5d\n","50 cents",system->cash_register[i].count);
				break;
			case ONE_DOLLAR :
				printf("%-15s |    %-5d\n","1 dollar",system->cash_register[i].count);
				break;
			case TWO_DOLLARS :
				printf("%-15s |    %-5d\n","2 dollar",system->cash_register[i].count);
				break;
			case FIVE_DOLLARS :
				printf("%-15s |    %-5d\n","5 dollar",system->cash_register[i].count);
				break;
			case TEN_DOLLARS :
				printf("%-15s |    %-5d\n","10 dollar",system->cash_register[i].count);
				break;
		}
	/* printf("\n\n%d %d %d\n\n",changecheck,totalmoney,(totalmoney / changecheck)); */

	}

    return FALSE;
}

BOOLEAN abort_program(struct ppd_system * system)
{

	printf("\n\nAbort Program\n\n");

	system_free(system);

	return TRUE;
}

void refund(struct coin tempcash_register[])
{
int i = 0,j = 0;
for(i = 0; i < NUM_DENOMS; i++)
	{
		switch(tempcash_register[i].denom)
		{
			case FIVE_CENTS :
				for(j = 0; j < tempcash_register[FIVE_CENTS].count; j++) {
					printf("5 Cents\n");
				}
				break;
			case TEN_CENTS :
				for(j = 0; j < tempcash_register[TEN_CENTS].count; j++) {
					printf("10 Cents\n");
				}
				break;
			case TWENTY_CENTS :
				for(j = 0; j < tempcash_register[TWENTY_CENTS].count; j++) {
					printf("20 Cents\n");
				}
				break;
			case FIFTY_CENTS :
				for(j = 0; j < tempcash_register[FIFTY_CENTS].count; j++) {
					printf("50 Cents\n");
				}
				break;
			case ONE_DOLLAR :
				for(j = 0; j < tempcash_register[ONE_DOLLAR].count; j++) {
					printf("1 Dollar\n");
				}
				break;
			case TWO_DOLLARS :
				for(j = 0; j < tempcash_register[TWO_DOLLARS].count; j++) {
					printf("2 Dollars\n");
				}
				break;
			case FIVE_DOLLARS :
				for(j = 0; j < tempcash_register[FIVE_DOLLARS].count; j++) {
					printf("5 Dollars\n");
				}
				break;
			case TEN_DOLLARS :
				for(j = 0; j < tempcash_register[TEN_DOLLARS].count; j++) {
					printf("10 Dollars\n");
				}
				break;
		}
	}

}
