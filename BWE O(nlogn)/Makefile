CC=g++
CXXFLAGS = -std=gnu++17 -Wall -Wextra
NAME = bwe-nlogn
SRC = bwe-nlogn.hpp bwe-nlogn_tools.cpp bwe-nlogn_main.cpp
OBJS = bwe-nlogn_tools.o bwe-nlogn_main.o

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(NAME)

distclean:
	rm -f $(NAME)
