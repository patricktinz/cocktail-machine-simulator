# author Patrick Tinz
CC = g++

OBJ = Cocktail.o CocktailMachine.o  CocktailSimulator.o Dispenser.o Ingredient.o Menue.o main.o

# program name
TARGET = cocktail

FLAGS = -g -std=c++14 -Wall -MMD -fmessage-length=0

all: $(TARGET)

# "make clean" delete all *.o files
clean:
	rm cocktail $(OBJ)

%.o : %.cpp
	$(CC) -c $(FLAGS) -o $@ $<

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)