++++++++++ set cell 0 to the number of fibonacci iterations: for this example it is set to 10
>+.   set cell 1 to 1
>+.   set cell 2 to 1
<<[>  loop for cell 0 number of iterations

[>>+>+<<<-]            move contents of cell 1 to 3 and 4

>>[<+>-]>              add cell 3 to cell 2

[<<<+>>>-]             move contents of cell 4 to cell 1

<<[>+<-] <[>>>+<<<-]   move contents of cells 1 and 2 to 4 and 3

>>[<<+>>-] >[<<+>>-]   move contents of cell 3 to 1 and 4 to 2

<<<.<-]                output the ascii character that corresponds to
                       the fibonacci number



The following is the program without comments
It also changes the program so that it asks for input instead of
setting the first cell to the number of fibonacci numbers to be
calculated
[-][

,>+.>+.<<[>[>>+>+<<<-]>>[<+>-]>[<<<+>>>-]<<[>+<-]<[>>>+<<<-]>>[<<+>>-]>[<<+>>-]<<<#<-]


]
