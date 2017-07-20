NAME := sorcery
CXX := g++-5
CXXFLAGS := -Wall -Werror=vla -std=c++14 -MMD
#SRC := $(shell find $(SOURCEDIR) -name '*.cc')
SRC := Card.cc Enchantments.cc Minion.cc Player.cc Ritual.cc Sorcery.cc Spell.cc
OBJ := $(SRC:.cc=.o)
DEP := $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

-include $(DEP)

clean:
	rm -f *.o

.PHONY: clean
