NAME = PmergeMe

SRC =	main.cpp	\
		PmergeMe.cpp

OBJ = $(SRC:.cpp=.o)

DEP = $(OBJ:.o=.d)

FLAGS = -Wall -Wextra -Werror -std=c++98 -MMD

-include $(DEP)

CXX = c++

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf $(DEP)

fclean: clean
	rm -rf $(NAME)

re: fclean all
