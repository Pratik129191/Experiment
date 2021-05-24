/*
*									==========: Logic of This Program :==========
*
*	At first a structure type data-type is created which defines every squares of the chess-board. Then with that data-type
*	we initialise a global 2D array of Chess-table where queens will be placed. Here every squares of the table hold three
*	attributes which will be initialised by  0 at first ----
*	a)	queen:-	if any queen is placed on that square then its value will be 1;
*	b)	saved:-	whenever a queen is placed on a sqaure then its value will be 1 to save information for later that here queen
*				has been placed before. It is mainly required at backtracking time.
*	c)	staus:-	if any queen is placed on any square then its value will be one level up. Simultaneously the values of all
*				neighbour squares  status of that queen will also be one level up, just to ensure that queens can't be placed
*				on those squares.
*	Now we take the number of queens as input from the user and start placing queens from the position (0,0)
*
*/

#include<stdio.h>
#include<stdlib.h>

// for decorating purpose ----
#define GREEN_BACKGROUND "\033[42m"
#define RED_FOREGROUND "\033[0;31m"
#define BOLD_YELLOW_FOREGROUND "\033[1;33m"
#define BOLD_CYAN_FOREGROUND "\033[1;36m"
#define RESET "\033[0m"

// structure of each square on the chess-board ----
typedef struct queen_placing_square
{
	int queen;
	int saved;
	int status;
}square;

// declaring global array or chess-board to place queens ----
square queen_base[50][50];

// declaring utility functions ----
void change_status_of_all_neighbours(int row, int column, int length);
void reset_status_of_all_neighbours(int row, int column, int length);
void place_queens_in_base(int row, int column, int length);
void backtrack_to_the_previous_queen(int row, int cloumn, int length);
int available_position_to_place_queen_in_next_row(int row, int column, int length);		// it only returns the column number.
int available_position_to_place_queen_in_this_row(int row, int column, int length);		// it only returns the column number.
void reset_all_attributes_of_queen_base_squares(int length);
void display_positions_of_queens(int length);

// decorating functions ----
void graphically_display_positions(int length);
void print_queen();
void print_total_border(int length);
void print_column_numbers(int length);

int main()
{
	int length;
	printf("Enter The Number Queens (2 < QUEENS <= 50):- ");
	scanf("%d", &length);

	// initialising all square's attributes of the chess-board ----
	for (int row = 0; row < length; row++)
	{
		for (int column = 0; column < length; column++)
		{
			queen_base[row][column].queen = 0;
			queen_base[row][column].status = 0;
			queen_base[row][column].saved = 0;
		}
	}

	// placing the queens ----
	place_queens_in_base(0, 0, length);

	// displaying after placing queens ----
	display_positions_of_queens(length);
	int choice = -1;
	printf(BOLD_CYAN_FOREGROUND "Do You Want to See The Graphical Representation of Chess-Board After Placing Queens (1: YES & 0: NO) :- " RESET);
	scanf("%d", &choice);
	if (choice == 1)
	{
		graphically_display_positions(length);
	}
	else
	{
		exit(0);
	}
}

void change_status_of_all_neighbours(int row, int column, int length)
{
	// changing status of queen square ----
	queen_base[row][column].status++;

	// changing status of all squares in right side of the queen ----
	for (int i = column + 1; i < length; i++)
	{
		queen_base[row][i].status++;
	}

	// changing status of all squares in left side of the queen ----
	for (int i = column - 1; i >= 0; i--)
	{
		queen_base[row][i].status++;
	}

	// changing status of all squares in down side of the queen ----
	for (int i = row + 1; i < length; i++)
	{
		queen_base[i][column].status++;
	}

	// changing status of all squares in upper side of the queen ----
	for (int i = row - 1; i >= 0; i--)
	{
		queen_base[i][column].status++;
	}

	// changing status of all squares in south-east side of the queen ----
	int r = row + 1, c = column + 1;
	while (r < length && c < length)
	{
		queen_base[r][c].status++;
		r++;
		c++;
	}

	// changing status of all squares in north-west side of the queen ----
	r = row - 1; c = column - 1;
	while (r >= 0 && c >= 0)
	{
		queen_base[r][c].status++;
		r--;
		c--;
	}

	// changing status of all squares in south-west side of the queen ----
	r = row + 1, c = column - 1;
	while (r < length && c >= 0)
	{
		queen_base[r][c].status++;
		r++;
		c--;
	}

	// changing status of all squares in north-east side of the queen ----
	r = row - 1; c = column + 1;
	while (r >= 0 && c < length)
	{
		queen_base[r][c].status++;
		r--;
		c++;
	}
}

void reset_status_of_all_neighbours(int row, int column, int length)
{
	// resetting status of queen square ----
	queen_base[row][column].status--;

	// resetting status of all squares in right side of the queen ----
	for (int i = column + 1; i < length; i++)
	{
		queen_base[row][i].status--;
	}

	// resetting status of all squares in left side of the queen ----
	for (int i = column - 1; i >= 0; i--)
	{
		queen_base[row][i].status--;
	}

	// resetting status of all squares in down side of the queen ----
	for (int i = row + 1; i < length; i++)
	{
		queen_base[i][column].status--;
	}

	// resetting status of all squares in upper side of the queen ----
	for (int i = row - 1; i >= 0; i--)
	{
		queen_base[i][column].status--;
	}

	// resetting status of all squares in south-east side of the queen ----
	int r = row + 1, c = column + 1;
	while (r < length && c < length)
	{
		queen_base[r][c].status--;
		r++;
		c++;
	}

	// resetting status of all squares in north-west side of the queen ----
	r = row - 1; c = column - 1;
	while (r >= 0 && c >= 0)
	{
		queen_base[r][c].status--;
		r--;
		c++;
	}

	// resetting status of all squares in south-west side of the queen ----
	r = row + 1, c = column - 1;
	while (r < length && c >= 0)
	{
		queen_base[r][c].status--;
		r++;
		c--;
	}

	// resetting status of all squares in north-east side of the queen ----
	r = row - 1; c = column + 1;
	while (r >= 0 && c < length)
	{
		queen_base[r][c].status--;
		r--;
		c++;
	}
}

void place_queens_in_base(int row, int column, int length)
{
	if (row >= length)
	{
		// this condition proves that we have successfully placed all queens in base ----
		return;
	}
	else
	{
		queen_base[row][column].queen = 1;
		queen_base[row][column].saved = 1;
		change_status_of_all_neighbours(row, column, length);

		// find a available place in next row to place the queen ----
		int col = -1;
		col = available_position_to_place_queen_in_next_row(row, col, length);
		if (col == -1)
		{
			// if not found and possible position then ----
			backtrack_to_the_previous_queen(row, column, length);
		}
		else
		{
			place_queens_in_base(row + 1, col, length);
		}
	}
}

void backtrack_to_the_previous_queen(int row, int column, int length)
{
	if (row == 0)
	{
		/*
		*	here we have reached in the satrting row by backtracking so,
		*	again reset attributes of all squares to its initialised state
		*	and place the queen in next column where it was previously placed and 
		*	check again by placing queen to find a safe position.
		*/
		reset_all_attributes_of_queen_base_squares(length);
		place_queens_in_base(row, column + 1, length);
	}
	else
	{
		queen_base[row][column].queen = 0;
		reset_status_of_all_neighbours(row, column, length);
		int col = -1;
		col = available_position_to_place_queen_in_this_row(row, column, length);
		if (col == -1)
		{
			/*
			*	if any available position not found then find the column number in previous row where queen
			*	was present and bactrack to that queen.
			*/
			int pcol = -1;
			for (int i = 0; i < length; i++)
			{
				if (queen_base[row - 1][i].queen == 1)
				{
					pcol = i;
				}
			}
			backtrack_to_the_previous_queen(row - 1, pcol, length);
		}
		else
		{
			place_queens_in_base(row, col, length);
		}
	}
}

int available_position_to_place_queen_in_next_row(int row, int column, int length)
{
	int pos = -1;
	for (int col = 0; col < length; col++)
	{
		if (queen_base[row + 1][col].queen == 0 && queen_base[row + 1][col].status == 0)
		{
			pos = col;
		}
	}
	return pos;
}

int available_position_to_place_queen_in_this_row(int row, int column, int length)
{
	int pos = -1;
	for (int col = 0; col < length; col++)
	{
		if (queen_base[row][col].queen == 0 && queen_base[row][col].status == 0 && queen_base[row][col].saved == 0)
		{
			pos = col;
		}
	}
	return pos;
}

void reset_all_attributes_of_queen_base_squares(int length)
{
	for (int row = 0; row < length; row++)
	{
		for (int column = 0; column < length; column++)
		{
			queen_base[row][column].queen = 0;
			queen_base[row][column].saved = 0;
			queen_base[row][column].status = 0;
		}
	}
}

void display_positions_of_queens(int length)
{
	printf(RED_FOREGROUND "\n\n==========: Positions of Queens are :==========\n\n" RESET);
	printf("Here First Column & First Row is Started from Index 0.\n\n");
	for (int row = 0; row < length; row++)
	{
		for (int column = 0; column < length; column++)
		{
			if (queen_base[row][column].queen == 1)
			{
				printf("\t{\t( %d, %d )\t}\n", row, column);
			}
		}
	}
	printf("\n\n");
}

void graphically_display_positions(int length)
{
	printf(RED_FOREGROUND "\n\n==========: Graphically Representing the Chess-Board with Queens :==========\n\n" RESET);
	print_column_numbers(length);
	print_total_border(length);
	for (int row = 0; row < length; row++)
	{
		printf("\t");
		printf(BOLD_YELLOW_FOREGROUND);
		printf("%d ", row);
		printf(RESET);
		printf("|");
		for (int column = 0; column < length; column++)
		{
			if (queen_base[row][column].queen == 1)
			{
				print_queen();
			}
			else
			{
				printf("    |");
			}
		}
		printf("\n");
		print_total_border(length);
	}
}

void print_queen()
{
	printf(GREEN_BACKGROUND " QN " RESET);
	printf("|");
}

void print_total_border(int length)
{
	printf("\t  ");
	printf("|");
	for (int i = 0; i < length; i++)
	{
		printf("----|");
	}
	printf("\n");
}

void print_column_numbers(int length)
{
	printf("\t  ");
	printf(BOLD_YELLOW_FOREGROUND);
	for (int i = 0; i < length; i++)
	{
		printf("  %d  ", i);
	}
	printf("\n" RESET);
}
