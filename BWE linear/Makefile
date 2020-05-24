CC=g++
CXXFLAGS = -std=gnu++17 -Wall -Wextra
NAME = bwe-linear
SRC = bwe-linear.hpp bwe-linear_tools.cpp bwe-linear_main.cpp
OBJS = bwe-linear_tools.o bwe-linear_main.o

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(NAME)

distclean:
	rm -f $(NAME)
