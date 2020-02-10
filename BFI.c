
/**********************************************************************/
/*                                                                    */
/* Program Name: BFI - Brain Fudge Interpreter                        */
/* Author:       Nathan B. Campbell                                   */
/* Date Written: January 6, 2020                                      */
/*                                                                    */
/**********************************************************************/

/**********************************************************************/
/*                                                                    */
/* I pledge this assignment is my own first time work.                */
/* I pledge I did not copy or try to copy any work from the Internet. */
/* I pledge the only person I asked for help from was my teacher.     */
/* I pledge I did not attempt to help any student on this assignment. */
/* I understand if I violate this pledge I will receive a 0 grade.    */
/*                                                                    */
/*                                                                    */
/*                      Signed: _____________________________________ */
/*                                           (signature)              */
/*                                                                    */
/*                                                                    */
/**********************************************************************/

/**********************************************************************/
/*                                                                    */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/**********************************************************************/
/*                        Symbolic Constants                          */
/**********************************************************************/
#define MEMORY_SIZE    30000          /* Size of the memory cell list */
#define MAX_CELL       MEMORY_SIZE-1  /* Maximum memory cell          */
#define MIN_CELL       0              /* Minimum memory cell          */
#define FILE_NAME      argv[1]        /* Name of the source file      */
#define NO_SOURCE_ERR  1              /* No source file found error   */
#define OVERFLOW_ERR   2              /* Maximum memory overflow      */
#define UNDERFLOW_ERR  3              /* Minimum memory underflow     */

#define MOVE_RIGHT     '>'            /* Move pointer right operation */
#define MOVE_LEFT      '<'            /* Move pointer left operation  */
#define INCREMENT_CELL '+'            /* Increment cell operation     */
#define DECREMENT_CELL '-'            /* Decrement cell operation     */
#define OUTPUT_CELL    '.'            /* Output cell operation        */
#define INPUT_CELL     ','            /* Input cell operation         */
#define JUMP_FORWARD   '['            /* Jump forward if cell is 0 op */
#define JUMP_BACKWARD  ']'            /* Jump back if cell is !0 op   */

#define DEBUG          '#'            /* Debug operation              */
/**********************************************************************/
/*                        Function Prototypes                         */
/**********************************************************************/
void debug(int *memory_cell_list_start, int number_of_cells, int current_cell);
   /* Prints all memory cells and their values                        */
void move_memory_right(int *current_cell, int maximum_cell);
   /* Moves the current memory cell to the right                      */
void move_memory_left(int *current_cell, int minimum_cell);
   /* Moves the current memory cell to the left                       */
void jump_forward(int *memory_cell_list, int current_cell, FILE *source_file,
                  char jump_forward_symbol, char jump_backward_symbol);
   /* Jumps past the matching operator if the current cell is zero    */
void jump_backward(int *memory_cell_list, int current_cell, FILE *source_file,
                   char jump_forward_symbol, char jump_backward_symbol);
   /* Jumps back to the matching operator if the current cell is not  */
   /* zero                                                            */

/**********************************************************************/
/*                           Main Function                            */
/**********************************************************************/
int main(int argc, char *argv[])
{
   FILE *source_file;                    /* Points to the source file */
   int  current_cell = 0,                /* Current memory cell       */
        memory_cell_list[MEMORY_SIZE] = {0}; 
                                         /* List of memory cells      */
   char current_operation;               /* Current operation         */
   
   /* Open the source file, if no source file was selected, error     */
   if ((source_file = fopen(FILE_NAME, "r")) == NULL)
   {
      printf("\nError #%d occurred in main().", NO_SOURCE_ERR);
      printf("\nCannot find the source file to interpret.");
      printf("\nThe program is aborting.");
      exit(NO_SOURCE_ERR);
   }

   /* Loop processing the source file until the end of file is found  */
   while (!feof(source_file))
   {
      current_operation = fgetc(source_file);
      switch (current_operation)
      {
         /* Move the current memory cell right                        */
         case MOVE_RIGHT:
            move_memory_right(&current_cell, MAX_CELL);
            break;
         /* Move the current memory cell left                         */
         case MOVE_LEFT:
            move_memory_left(&current_cell, MIN_CELL);
            break;
         /* Increment the current memory cell                         */
         case INCREMENT_CELL:
            memory_cell_list[current_cell] += 1;
            break;
         /* Decrement the current memory cell                         */
         case DECREMENT_CELL:
            memory_cell_list[current_cell] -= 1;
            break;
         /* Output the current memory cell                            */
         case OUTPUT_CELL:
            printf("%c", memory_cell_list[current_cell]);
            break;
         /* Input a character to the current memory cell              */
         case INPUT_CELL:
            memory_cell_list[current_cell] = (int) getchar();
            break;
         /* If the current cell's value is zero, jump past the        */
         /* matching jump backward command                            */
         case JUMP_FORWARD:
            jump_forward(memory_cell_list, current_cell, source_file, JUMP_FORWARD, JUMP_BACKWARD);
            break;
         /* If the current cell's value is not zero, jump back to the */
         /* matching jump forward symbol                              */
         case JUMP_BACKWARD:
            jump_backward(memory_cell_list, current_cell, source_file, JUMP_FORWARD, JUMP_BACKWARD);
            break;
         /* Print memory cells and values                             */
         case DEBUG:
            debug(memory_cell_list, MEMORY_SIZE, current_cell);
            break;
         default:
            break;
      }
   }
   
   fclose(source_file);
   return 0;
}

/**********************************************************************/
/*             Prints all memory cells and their values               */
/**********************************************************************/
void debug(int *memory_cell_list_start, int cell_count, int current_cell)
{
   int *memory_cell;                   /* Points to every memory cell */
   
   printf("\nCurrent memory cell pointer: %d", current_cell);
   printf("\nCurrent memory cell pointer: %c", memory_cell_list_start[current_cell]);
   printf("\n");
   for (memory_cell = memory_cell_list_start; 
       (memory_cell - memory_cell_list_start) < cell_count; memory_cell++)
      printf("[%ld]", memory_cell - memory_cell_list_start);
   printf("\n");
   for (memory_cell = memory_cell_list_start; 
       (memory_cell - memory_cell_list_start) < cell_count; memory_cell++)
      printf("[%d]", *memory_cell);
   printf("\n");
   for (memory_cell = memory_cell_list_start; 
       (memory_cell - memory_cell_list_start) < cell_count; memory_cell++)
      printf("[%c]", *memory_cell);
   printf("\n");
   return;
}

/**********************************************************************/
/*            Moves the current memory cell to the right              */
/**********************************************************************/
void move_memory_right(int *current_cell, int maximum_cell)
{
   if ((*current_cell + 1) > maximum_cell)
   {
      printf("\nError #%d occurred in move_memory_right().", OVERFLOW_ERR);
      printf("\nMaximum memory cell overflow.");
      printf("\nThe program is aborting.");
      exit(OVERFLOW_ERR);
   }
   else
   {
      *current_cell += 1;
   }
   return;
}

/**********************************************************************/
/*            Moves the current memory cell to the left               */
/**********************************************************************/
void move_memory_left(int *current_cell, int minimum_cell)
{
   if ((*current_cell - 1) < minimum_cell)
   {
      printf("\nError #%d occurred in move_memory_left().", UNDERFLOW_ERR);
      printf("\nMinimum memory cell overflow.");
      printf("\nThe program is aborting.");
      exit(UNDERFLOW_ERR);
   }
   else
   {
      *current_cell -= 1;
   }
   return;
}

/**********************************************************************/
/*    Jumps past the matching operator if the current cell is zero    */
/**********************************************************************/
void jump_forward(int *memory_cell_list, int current_cell, FILE *source_file,
                  char jump_forward_symbol, char jump_backward_symbol)
{
   int match_found = 1;    /* Indicates that a matching jump backward */
                           /* operation has been found if set to zero */
   char current_operation; /* Current operation                       */
   
   if (memory_cell_list[current_cell] == 0)
   {
      while ((current_operation != EOF) && match_found != 0)
      {
         current_operation = fgetc(source_file);
         if (current_operation == jump_forward_symbol)
         {
            match_found += 1;
         }
         else if (current_operation == jump_backward_symbol)
         {
            match_found -= 1;
         }
      }
   }
   return;
}

/**********************************************************************/
/*    Jumps past the matching operator if the current cell is zero    */
/**********************************************************************/
void jump_backward(int *memory_cell_list, int current_cell, FILE *source_file,
                   char jump_forward_symbol, char jump_backward_symbol)
{
   int match_found = 1;    /* Indicates that a matching jump backward */
                           /* operation has been found if set to zero */
   char current_operation; /* Current operation                       */
   
   if (memory_cell_list[current_cell] != 0)
   {
      while (ftell(source_file) && match_found != 0)
      {
         fseek(source_file, -2L, SEEK_CUR);
         current_operation = fgetc(source_file);
         if (current_operation == jump_forward_symbol)
         {
            match_found -= 1;
         }
         else if (current_operation == jump_backward_symbol)
         {
            match_found += 1;
         }
      }
   }
   return;
}
