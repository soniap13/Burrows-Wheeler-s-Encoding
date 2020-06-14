CC=g++
CXXFLAGS = -std=gnu++17 -Wall -Wextra
NAME = bwe
SRC =  HuffmanEncoder.cpp TreeNode.cpp suffix_tree.cpp bwe_tools.cpp bwe_main.cpp
OBJS =  HuffmanEncoder.o TreeNode.o suffix_tree.o bwe_tools.o bwe_main.o

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(NAME)

distclean:
	rm -f $(NAME)
