#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
	
struct record { 
	char name[30];
	int room;
	int quantity;
} rec;

struct node {
	char name[30];
	int room;
	int quantity;
	struct node *next;
};

typedef struct node *nodeptr;

nodeptr getnode() {
	nodeptr p;
	p = ((nodeptr)malloc(sizeof(struct node)));
	return p;
}

nodeptr add_node_at_first(nodeptr *p, char item_name[], int room, int quantity) {
	
	nodeptr newnode;
	nodeptr ptr = *p;
	
	int error = 0;
	
	while (ptr != NULL) {
	
		if (strcmp(item_name, ptr->name) == 0 && room == ptr->room) { /* Check for redundancy */
			error = 1; 
		}
		ptr = ptr->next;
	} 
	
	if (error == 0) { /* If not redundant create new node */
		newnode = getnode();
		strcpy(newnode->name, item_name);
		newnode->room = room;
		newnode->quantity = quantity;
		newnode->next = *p;
		return newnode; /* Return pointer to new node */
	} else {
		return *p; /* Return old pointer to list */
	} 
}

void freenode(nodeptr p) {
	free (p);
}

void search(nodeptr *p, char item_name[]) {
	
	nodeptr ptr = *p;
	
	while (ptr != NULL) {
			
		if (strcmp(ptr->name, item_name) == 0) {
			printf ("\t| %10s	\t| %3d	|	 %3d	|\n\n", ptr->name, ptr->room, ptr->quantity);
			ptr = ptr->next;	
		} else {
			ptr = ptr->next;
		}
	}
}

void display(nodeptr *p) {
	
	nodeptr ptr = *p;
	
	while (ptr != NULL) {
		
		printf ("\t| %10s	\t| %3d	|	 %3d	|\n\n", ptr->name, ptr->room, ptr->quantity);
		ptr = ptr->next;
	}
}

nodeptr delete_node(nodeptr *p, char item_name[], int room) {
	
	nodeptr ptr = *p;
	int flag = 0;
	
	if (strcmp(ptr->name, item_name) == 0 && room == ptr->room) { /* Delete first node */
		nodeptr temp;
			
		temp = ptr;
		ptr = ptr->next;
		
		flag = 1;
			
		free(temp);
		
		printf ("\t Deletion Successful \n");
		getch();
				
		return ptr; /* Return pointer to first node */
	} else {
		ptr = ptr->next;
		
		while (ptr != NULL) { /* Delete node inbetween */
			
			if (strcmp(ptr->name, item_name) == 0 && room == ptr->room) {
				
				nodeptr temp;
				
				temp = ptr;
				ptr = ptr->next;
				
				free(temp);
				
				flag = 1;
				
				printf ("\t Deletion Successful \n");
				getch();
				
				return *p;	/* Return pointer to first node */
			} else {
				ptr = ptr->next;
			}
		} 
	}
	
	if (flag = 0) {
		printf ("\t Item not found \n");
		getch();
		return *p; /* If no items deleted return pointer to first node */
	}
}

void clear() {		/* Source: cprogramming.com */
	
  DWORD n;                         /* Number of characters written */
  DWORD size;                      /* number of visible characters */
  COORD coord = {0};               /* Top left screen position */
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  /* Get a handle to the console */
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

  GetConsoleScreenBufferInfo ( h, &csbi );

  /* Find the number of characters to overwrite */
  size = csbi.dwSize.X * csbi.dwSize.Y;

  /* Overwrite the screen buffer with whitespace */
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );

  /* Reset the cursor to the top left position */
  SetConsoleCursorPosition ( h, coord );
}

