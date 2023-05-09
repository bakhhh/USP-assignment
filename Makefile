#makefile to compile my code
#Name: Sohail Bakhshi


CC		 = gcc
EXEC	 = calculator
CFLAGS = -g -Wall 
OBJ 	 = calculator.o getResults.o listFiles.o 


$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) 

calculator.o : calculator.c 
	$(CC) $(CFLAGS) calculator.c -c

getResults.o : getResults.c getResults.h
	$(CC) $(CFLAGS) getResults.c -c

listFiles.o : listFiles.c listFiles.h
	$(CC) $(CFLAGS) listFiles.c -c

clean:
	rm -f $(EXEC) $(OBJ)


