/* 
	Project		:	Resource Management System
	Author		:	Sushil Awale
	Date		:	17 - 10 - 2016
	References	: 	1. Data Structures Using C and C++, Pg 468 - 489
					2. www.stackoverflow.com
					3. www.cprogramming.com
*/

/* Header Section */
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#define TABLESIZE 1000
#define TABLESIZE_ROOM 60

/* Function declaration Section */
void log_in();
void admin_page();
void user_page();
void add_items();
void search_items();
void view_items();
void view_all_items();
void view_by_room();
void delete_items();
int hash(char []);
void transfer_to_primary();
void transfer_to_primary_room_wise();
int hash_by_room(int);

/* Global Variables */
FILE *fp, *ftemp;
nodeptr hash_table[TABLESIZE];
nodeptr hash_table_room[TABLESIZE_ROOM];
nodeptr listptr;
	
int main () {
	
	fp = fopen ("rms_data.txt", "a+");
	
	log_in(); /* Goto login page */
	
	getch ();
	
	fclose(fp);
}

void log_in() {
	
	clear();
	
	int session;
	char pass[20];
	
	/* Display Menu */
	
	printf ("\t Resource Managment System \n"); 
	printf ("\t _________________________ \n\n");
	printf ("\t 1. Admin \n");
	printf ("\t 2. User \n");
	printf ("\t 3. Exit \n");
	scanf ("\t %d", &session);
	
	switch (session) {
		case 1:
			clear();
			
			/* Authentication for admin */
			printf ("\t Enter Password : \t");
			scanf ("%s", pass);
	
			if (strcmp (pass, "password") == 0 ) {
			 	admin_page(); /* Goto Admin Page */
			} else {
				printf ("\t Invalid Entry. Press enter to try again.");
				getch();
				log_in();	
			}
		case 2:
			user_page(); /* Goto User Page */		
		case 3:
			exit (-1);
		default:
			printf ("\t Invalid Entry. Press enter to try again. \n");
			getch();
			log_in();
	}
}

void admin_page() {
	
	clear();
	
	int menu;
	
	/* Display Menu */	
	printf ("\t Welcome Admin! \n\n");
	
	printf ("\t Function Menu \n");
	printf ("\t _____________ \n\n");
	
	printf ("\t 1. Add new items \n");
	printf ("\t 2. Search items \n");
	printf ("\t 3. View items \n");
	printf ("\t 4. Delete items \n");
	printf ("\t 5. Exit \n");
	scanf ("%d", &menu);
	
	switch (menu) {
		case 1:
			add_items(); /* Goto add items page */
			admin_page(); /* Go back to admin page */
		case 2:
			search_items(); /* Goto search items page */
			admin_page(); /* Go back to admin page */
		case 3:
			view_items(); /* Goto view items page */
			admin_page(); /* Go back to admin page */
		case 4:
			delete_items(); /* Goto delete items page */
			admin_page(); /* Go back to admin page */
		case 5:
			exit(-1);
		default:
			printf ("\t Invalid Entry. Press enter to try again. \n");
			getch();
			admin_page(); /* Go back to admin page */
	}
}

void user_page() {
	
	clear();
	
	int menu;
	
	/* Display Menu */
	printf ("\t Hello User! \n\n");
	printf ("\t Function Menu \n");
	printf ("\t _____________ \n\n");
	
	printf ("\t 1. Search items \n");
	printf ("\t 2. View items \n");
	printf ("\t 3. Exit \n");
	scanf ("\t %d", &menu);
	
	switch (menu) {
		case 1:
			search_items(); /* Go search items page */
			user_page();
		case 2:
			view_items(); /* Go view items page */
			user_page();
		case 3:
			exit(-1);
		default:
			printf ("\t Invalid Entry. Press enter to try again. \n");
			getch();
			user_page();
	}
}

void add_items() {
	
	clear();
	
	int count, repeat;
	
	do {
	
	printf ("\t Enter item name \t");
	scanf ("%s", rec.name);
	
	printf ("\t Enter room no. \t");
	scanf ("%d", &rec.room);
	
	printf ("\t Enter quantity \t");
	scanf ("%d", &rec.quantity);
	
	fprintf (fp, "%s %d %d \n", rec.name, rec.room, rec.quantity);	/* Write in file */
	
	count++;
	
	printf ("\t Press '1' to enter new item. Else press '0' \n");
	scanf ("\t %d", &repeat);
	
	} while (repeat == 1);
	
	printf ("\t %d item/s have been added \n", count);
	
	transfer_to_primary(); /* Transfer all data from file to primary memory */
	
	getch();
}

void search_items() {
	
	clear();
	
	transfer_to_primary(); /* Transfer all data from file to primary memory */
	
	char item_name[50];
	int k, count, flag = 0;
	
	printf ("\t Enter item name \t");
	scanf ("\t %s", item_name);
	
	clear();
	
	for (k = 0; item_name[k]; k++) {		/* Convert to upper case */
  			item_name[k] = toupper(item_name[k]);
	}
	
	listptr = hash_table[hash(item_name)]; /* Retrieve pointer to linked list */
	 
	if (listptr == NULL) {
		printf ("\t Item Not Found \n");
	} else if (listptr != NULL) {
		
		printf ("\t________________________________________________\n\n");
		printf ("\t| Item Name	\t| Room  | Quantity	|\n");
		printf ("\t________________________________________________\n\n");
		
		search(&listptr, item_name); /* Call search function in header file */	
	}
	getch();
}

void view_items() {
	
	clear();
	
	transfer_to_primary_room_wise(); /* Transfer all data from file to primary memory based on room */
	
	int menu;
	
	/* Display Menu */
	printf ("\t View Menu \n");
	printf ("\t _____________ \n\n");
	
	printf ("\t 1. View all items \n");
	printf ("\t 2. View items by room \n");
	printf ("\t 3. Go back to main menu \n");
	scanf ("\t %d", &menu);
	
	switch (menu) {
		case 1:
			view_all_items();
			return;
		case 2:
			view_by_room();
			return;
		case 3:
			return;
		default:
			printf ("\t Invalid Entry. Press enter to try again. \n");
			getch();
			view_items();
	}
}

void view_all_items () {
	
	clear();
	
	int index = 0, flag = 0;
	
	printf ("\t_____________________________________________\n\n");
	printf ("\t| Item Name	\t| Room  | Quantity	|\n");
	printf ("\t_____________________________________________\n\n");
		
	while (index < TABLESIZE_ROOM) {
		display(&hash_table_room[index]); /* Call display function */
		flag = 1;
		index++;
	}
	
	if (flag == 0) {
		printf ("\t There are no items \n");
	}
	getch();
}	

void view_by_room() {
	
	clear();
	
	int room_index;
	/* List of rooms */
	printf ("\t Rooms \n");
	printf ("\t _____ \n \n");
	
	printf ("\t| Room 101 |\t | Room 102 |\t | Room 103 |\t | Room 104 |\t | Room 105 |\n");
	printf ("\t| Room 201 |\t | Room 202 |\t | Room 203 |\t | Room 204 |\t | Room 205 |\n");
	printf ("\t| Room 301 |\t | Room 302 |\t | Room 303 |\t | Room 304 |\t | Room 305 |\n");
	printf ("\t| Room 401 |\t | Room 402 |\t | Room 403 |\t | Room 404 |\t | Room 405 |\n");
	printf ("\t| Room 501 |\t | Room 502 |\t | Room 503 |\t | Room 504 |\t | Room 505 |\n");
	printf ("\t _______________________________________________________________________ \n \n");
	
	printf ("\t Enter room no. \t");
	scanf ("\t %d", &room_index);
	
	listptr = hash_table_room[hash_by_room(room_index)]; /* Retrieve pointer to linked list */
	 
	if (listptr == NULL) {
		printf ("\t There are no items \n");
	} else if (listptr != NULL) {
		
		printf ("\t_____________________________________________\n\n");
		printf ("\t| Item Name	\t| Room  | Quantity	|\n");
		printf ("\t_____________________________________________\n\n");
		
		display(&listptr);	 /* Call display function in header file */
	}
		
	getch();
}

void delete_items() {

	clear();
	
	transfer_to_primary(); /* Transfer all data from file to primary memory */
	
	char item_name[50];
	int k, room, index;
	
	printf ("\t Enter item name \t");
	scanf ("%s", item_name);
	
	printf ("\t Enter room no. \t");
	scanf ("%d", &room);
	
	for (k = 0; item_name[k]; k++) {		/* Convert to upper case */
  			item_name[k] = toupper(item_name[k]);
	}
	
	listptr = hash_table[hash(item_name)]; /* Retrieve pointer to list */
	 
	if (listptr == NULL) {
		printf ("\t Item not found \n");
	} else if (listptr != NULL) {
		hash_table[hash(item_name)] = delete_node(&listptr, item_name, room); 
		/* Call delete node funciton and return the pointer of the linked list */
	} 
	
	/* Re-write all the data in temporary file and then copy it into new file */
	ftemp = fopen("temp.txt", "w"); /* Temporary file */
	
	while (index < TABLESIZE) {
		
		listptr = hash_table[index];
		
		while (listptr != NULL) {
			
			/* Copy all the data from linked list nodes to RECORD structure and then write it in file */
			strcpy (rec.name, listptr->name);
			rec.room = listptr->room;
			rec.quantity = listptr->quantity;
			listptr = listptr->next;	
			
			fprintf (fp, "%s %d %d \n", rec.name, rec.room, rec.quantity);
		}
		index++;
	}
	rewind(fp);
	fclose(ftemp);
	fclose(fp);
	
	remove("rms_data.txt"); /* Delete old file */
	rename ("test.txt", "rms_data.txt"); /* Rename temporary file */
}

int hash(char item_name[]) {
	
	int loop, index = 0;
	
	/* Generate ASCII code of first three letters */
	for (loop = 0; loop < 3; loop++) {
		index = index * 100;
		index = index + item_name[loop];
	}
	/* Return the above result divided by TABLESIZE - 1 and subtracted by 222 */
	/* 222 is the lowest number generated */
	return (index % (TABLESIZE - 1) - 222);
}

void transfer_to_primary() {
	
	rewind(fp);
	
	char ch;
	int k, index;
	
	do {
		
		fscanf (fp, "%s %d %d", rec.name, &rec.room, &rec.quantity); /* Read data from file */
	
		for (k = 0; rec.name[k]; k++) {		/* Convert to upper case */
  			rec.name[k] = toupper(rec.name[k]);
		}
		
		index = hash(rec.name); /* Generate hash key */
			
		if (hash_table[index] == NULL) { 
			
			hash_table[index] = listptr; /* Create a new linked list pointer*/
			
			hash_table[index] = add_node_at_first(&listptr, rec.name, rec.room, rec.quantity);
			/* Add new item and re-store the new list ptr */
			
		} else if (hash_table[index] != NULL) {
			
			listptr = hash_table[index]; /* Retrieve the exisiting list pointer*/
			
			hash_table[index] = add_node_at_first(&listptr, rec.name, rec.room, rec.quantity);
			/* Add new item and re-store the new list ptr */
		}	
					   
	} while (ch = getc(fp) != EOF); /* Read data from file until end of file */
	
	return;
}

void transfer_to_primary_room_wise() {
	
	rewind(fp);
	
	char ch;
	int index, k;
	
	do {
		
		fscanf (fp, "%s %d %d", rec.name, &rec.room, &rec.quantity); /* Read data from file */
		
		for (k = 0; rec.name[k]; k++) {		/* Convert to upper case */
  			rec.name[k] = toupper(rec.name[k]);
		}
		
		index = hash_by_room(rec.room); /* Generate Hash key */
		
		if (hash_table_room[index] == NULL) { 
		
			hash_table_room[index] = listptr; /* Create a new list pointer*/
			
			hash_table_room[index] = add_node_at_first(&listptr, rec.name, rec.room, rec.quantity);
			/* Add new item and re-store the new list ptr */
			
		} else if (hash_table_room[index] != NULL) {
			
			listptr = hash_table_room[index]; /* Retrieve the exisiting list pointer*/		
			
			hash_table_room[index] = add_node_at_first(&listptr, rec.name, rec.room, rec.quantity);
			/* Add new item and re-store the new list ptr */
		}	
			   
	} while (ch = getc(fp) != EOF); /* Read data from file until end of file */
	
	return;
}

int hash_by_room (int room) {
	
	int temp;
	/* Generate the concatenation of first number and last number */
	temp = room / 10;
	room = temp + room - temp * 10;
	
	return room;
} 
