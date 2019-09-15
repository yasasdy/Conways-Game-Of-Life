#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 40
#define WIDTH 40
#define LIVE_CELL 1
#define DEAD_CELL 0

typedef int TableType[HEIGHT][WIDTH];

void srand(unsigned int seed);						//pseudo random number generator
int main_menu();							//main menu function
int machine_game_menu();						//machine menu function         
int human_game_menu();							//human menu function	        
void end_game();							//end game function		
void load_random(TableType table);					//generate random pattern	
void user_input(TableType table);					//generate user pattern					
int neighbour_value(TableType table, int row, int col);			// count neighbour function
int neighbour_count(TableType table, int row, int col);		
void calculate(TableType table);
void print_user_pattern(TableType table);
void print_machine_pattern(TableType table);


void print_user_pattern(TableType table)
{
	int row, col;

//	======================
//  	@ Human Destiny Game @
//   	======================

	printf("\033[H");
  	for ( row = 0; row < HEIGHT; row++ ) 
	{
    		for ( col = 0; col < WIDTH; col++ ) 
		{
       			if (table[row][col] == LIVE_CELL)
			{
				printf("\033[07m  \033[0m\033[37m\033[40;01m");
			}
 			else 
			{
				printf("  ");
   			}
    		}
		printf("\033[E");
	}
	fflush(stdout);
}

void print_machine_pattern(TableType table)
{
	int row, col;
	
//	======================
// 	@Machine Destiny Game@
//	======================

	printf("\033[H");
  	for ( row = 0; row < HEIGHT; row++ ) 
	{
    		for ( col = 0; col < WIDTH; col++ ) 
		{
       			if (table[row][col] == LIVE_CELL)
			{
				printf("\033[07m  \033[0m\033[37m\033[40;01m");
			}
 			else 
			{
				printf("  ");
   			}
    		}
		printf("\033[E");
	}
	fflush(stdout);
}

void user_input(TableType table) 
{
	int y,z;
	for(y=0;y<HEIGHT;y++)
	{
		for(z=0;z<WIDTH;z++)
		{
			table[y][z]=DEAD_CELL;
		}
	}

	int i,j;
	int n;
	int height, width;
	

	printf("Enter the amount of initial organisms: ");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		printf("Enter dimensions (x y) where organism %d will live: ", i + 1);
		scanf("%d %d", &height, &width);
		table[height][width] = LIVE_CELL;
	}
	printf("@ Your input will look like as follows @");
	for(i = 0; i < HEIGHT; i++)
	{
		for(j = 0; j < WIDTH; j++)
		{
			if( table[i][j] == LIVE_CELL )
				{printf(" * ");}
			else
				printf("  ");
		}
		printf("\n");
	}
	int w=0;
	while(w<20)
	{
		printf("\n");
	w++;
	}
}

void load_random(TableType table)
{
	int y,z;
	for(y=0;y<HEIGHT;y++)
	{
		for(z=0;z<WIDTH;z++)
		{
			table[y][z]=DEAD_CELL;	
		}
	}

	int x, row, col, i;
	x = ( rand() % 600 ) + 0;
	for(i = 1;i <= x; i++)
	{
		row = ( rand() % 60) + 0;
		col = ( rand() % 60 ) + 0;
      		table[row][col] = LIVE_CELL; 			
  	}
}

int neighbour_value(TableType table, int row, int col)
{
	if (row < 0 || row >= HEIGHT 
		|| col < 0 || col >= WIDTH
		|| table[row][col] != LIVE_CELL )
	{ 
		return 0;
	} 
	else 
	{
		return 1;
	}
}

int neighbour_count(TableType table, int row, int col)
{
	int neighbour = 0;

	neighbour += neighbour_value(table, row - 1, col - 1);
	neighbour += neighbour_value(table, row - 1, col);
	neighbour += neighbour_value(table, row - 1, col + 1);
	neighbour += neighbour_value(table, row, col - 1);
	neighbour += neighbour_value(table, row, col + 1);
	neighbour += neighbour_value(table, row + 1, col - 1);
	neighbour += neighbour_value(table, row + 1, col);
	neighbour += neighbour_value(table, row + 1, col + 1);
	
	return neighbour;
}

void calculate(TableType table)
{
	TableType tableB;
	int neighbour, height, width;

	for (height = 0; height < HEIGHT; height++) 
	{
		for (width = 0; width < WIDTH; width++) 
		{
			neighbour = neighbour_count(table, height, width);
			if (neighbour==3) 
			{
				tableB[height][width] = LIVE_CELL;
			} 
			else if (neighbour == 2 && table[height][width] == LIVE_CELL) 
			{
				tableB[height][width] = LIVE_CELL;
			} 
			else
 			{
				tableB[height][width] = DEAD_CELL;
			}
		}
	}
	for (height = 0; height < HEIGHT; height++) 
	{
		for (width = 0; width < WIDTH; width++) 
		{
			table[height][width] = tableB[height][width];
		}
	}
}

int main_menu()
{
     int opt1;
     printf("\n\t\t######******######\n");
  	 printf("\t\t@= GAME OF LIFE =@\n");
   	 printf("\t\t######******######\n");
   	 printf("\n\t     -Welcome to Game Of Life-\n");
   	 printf("\nRules Of The Game.\n");
   	 printf("1. A cells  is born in an empty  box when it has exactly 3 neighbors.\n");
   	 printf("2. A cells dies from loneliness if it has fewer than 2 neighbors.\n");
   	 printf("3. A cells dies of overcrowding if it has more than 3 neighbors.\n");
   	 printf("4. Otherwise, the cells  survives.\n");
   	 printf("\nPlease select the option from Main Menu.\n");
   	 printf("\t\t:Main Menu:\n");
 	 printf("1.Machine Destiny Game\n");
 	 printf("2.Human Destiny Game\n");
 	 printf("3.Sample Input\n");
	 printf("4.Quit Game\n");
	 printf("\tYour Selection: ");
     scanf ("%d", &opt1);
     return opt1; 	
      
}

int machine_game_menu()
{
      int opt2;
      printf("\n\t\t========================\n");
      printf("\t\t@ Machine Destiny Game @\n");
      printf("\t\t========================\n");
      printf("In this game, computer will generate the pattern of cell randomly for you.\n");
      printf("All you have to do is sit back and watch the cell progress.\n");
      printf("Please choose option below to proceed and have fun!\n");
      printf("1.Start Game\n");
      printf("2.Main Menu\n");
      printf("\tYour Selection: ");
      scanf ("%d", &opt2);
      int i=0;
	while(i<50)
	{
		printf("\n");
	i++;
	}
      return opt2;
}

int human_game_menu()
{
     int opt3,i, j,t;
	 printf("\n\t\t======================\n");
     printf("\t\t@ Human Destiny Game @\n");
     printf("\t\t======================\n");
     printf("In this game, you are free to choose the pattern of cell.\n");
     printf("Then, you can see the cell progress based on your cell pattern.\n");
     printf("1.Want to see the scale of the plane\n2.Continue with the game\nenter your choice : ");
     scanf("%d",&t);
			
     	if(t==1)
	{
		for(i=0; i<=HEIGHT ;i++)
		{
			for(j=0; j<=WIDTH; j++)
			{
        	               if(i==0)
			       {
					if(j<10 && j!=0)
					 {
        	                 		 printf(" 0%d",j);
        	                    	 }
	        	                 else
					 {
        	                      		printf(" %d",j);
					 }
				}	
                        	else
				{
				        if(j==0)	
					{
		                             if(i<10)
					     {
						printf(" 0%d",i);
					     }
		                             else
					     {
			                              printf(" %d",i);
					     }
					}
					else
						printf(" * ");
				}
          		}
			printf("\n");
		}
         }
 	 printf("Please choose option below to proceed and have fun!\n");
  	 printf("1.Enter Pattern\n");
   	 printf("2.Main Menu\n");
   	 printf("\tYour Selection: ");
   	 scanf ("%d", &opt3);

   	 return opt3;
}

void end_game()
{
	 printf("\n\t\t=============\n");
 	 printf("\t\t@ Quit Game @\n");
  	 printf("\t\t=============\n");
   	 printf("Thank you for trying this game. I hope you have found a lot of fun here.\n");
}


int sample_menu()
{
	printf("1.Figure eight\n2.infinite growth line\n3.pentadecathalon\n");
	int i;
	printf("\tYour Selection: ");
	scanf("%d",&i);
return i;
}




void sample_input(TableType table)
{
	int t,i,j;
	for(i=0;i<HEIGHT;i++)
	{
		 for(j=0;j<WIDTH;j++)
		 {
	   		table[i][j]=0;
		 }
   	}
	
	t= sample_menu();
	if(t==1)
	{
		 for(i=7;i<10;i++)
		 {
			   for(j=7;j<10;j++)
			   {
		    		table[i][j]=LIVE_CELL;
			   }
		 }
		 for(i=10;i<13;i++)
		 {
	   		for(j=10;j<13;j++)
			{
			    table[i][j]=LIVE_CELL;
			}
		 }
	}
	if(t==2)
	{
		for(j=10;j<30;j++)
		{
		   table[j][10]=LIVE_CELL; 
		}
	}
	if(t==3)
	{
		for(j=10;j<20;j++)
		{
			  if(j!=12|| j!=17)
			  {
	     			table[j][10] = LIVE_CELL;
			  }
	        }
	  	table[12][9]=LIVE_CELL;
	  	table[12][11]=LIVE_CELL;
	  	table[17][9]=LIVE_CELL;
	  	table[17][11]=LIVE_CELL;
	}
	int u=0;
	while(u != 100)
	{
		 printf("\n");
	 u++;
	}
}
  
 

int main()
{
  int opt1, opt2, opt3, opt4, k = 1;
  
  TableType table;
  srand ( time ( NULL ) );
  
	
	do
	{	   	
	     opt1 = main_menu();  
	     if (opt1 == 1)
	     {
		    do
		    {
		       opt2 = machine_game_menu();
			        if(opt2 == 1)
				{
			            printf("@Machine Destiny Game@\n");
				    load_random( table );
				    do
				    {
				    	print_machine_pattern( table );
					calculate( table );
					usleep(450000);	
		       		    }while(1);
                           	}
                    		if(opt2 > 2)
				{
		            		printf("\t\t-WRONG INPUT-\n\n");
                           	}
		    }while(opt2 > 2);
	     }
	     else if (opt1 == 2)
	     {
            	do
		{
		       opt3 = human_game_menu();
			        if(opt3 == 1)
				{
				    printf("@Human Destiny Game@\n");
				    printf("Enter Pattern\n");
				    user_input( table );
				    do
				    {
			    		print_user_pattern( table ); 
					calculate( table );
					usleep(4500000);
	               		    }while(1);
                           	}
                    		if(opt3 > 2)
			 	{
					    printf("\t\t-WRONG INPUT-\n\n");
                           	}
		 }while(opt3 > 2);	
	     }
	     else if(opt1 == 3)
	     {
	
		sample_input(table);
				do
				    {
			    		print_user_pattern( table );
					calculate( table );
					usleep(450000);
	               		    }while(1);


	    }
		
	     else if (opt1 == 4)
	     {
		 end_game();
		 break;
	     }
	     else 
	     {
		 printf("\t\t-WRONG INPUT-\n\n");
	     }
	}while( opt1 > 3 || opt2 == 2 || opt3 == 2 || opt4 == 2 );
           
                 
                 
  
  return 0;
}
