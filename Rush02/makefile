CFLAGS= -Werror -Wextra -Wall
TARGET= test
FILE= process_data.o process_input.o main.o process_data2.o

.phony: all fclean

all: $(TARGET)

$(TARGET): $(FILE)
	gcc -o $(TARGET) $(FILE) 

%.o: %.c 
	gcc -c $(CFLAGS) -o $@ $< 

fclean:
	rm -f *.o $(TARGET) 