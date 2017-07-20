NAME := sorcery
CXX := g++-5
CXXFLAGS := -Wall -Werror=vla -std=c++14 -MMD
SRC := $(shell find $(SOURCEDIR) -name '*.cc')
OBJ := $(SRC:.cc=.o)
DEP := $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

-include $(DEP)

clean:
	rm -f *.o

.PHONY: clean
