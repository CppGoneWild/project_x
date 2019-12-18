CXX = clang++

NAME = x.out

SRC = external/ImGui/imgui-SFML.cpp \
      external/ImGui/imgui.cpp \
      external/ImGui/imgui_demo.cpp \
      external/ImGui/imgui_draw.cpp \
      \
      external/logg/Entry.cpp \
      external/logg/I_Output.cpp \
      external/logg/MetaData.cpp \
      external/logg/StreamOutput.cpp \
      external/logg/Timer.cpp \
      \
      src/ux/Calandar.cpp \
      \
      src/time.cpp \
      src/main.cpp

OBJ = $(SRC:.cpp=.o)

INCLUDE_SFML_FLAGS =
INCLUDE_OTHER_FLAGS = -Isrc/ -Iexternal/ -Iexternal/ImGui
WARNING_FLAGS = -Wall -Wextra
DEBUG_FLAGS = -g -DDEBUG

LD_SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
LD_IMGUI_FLAGS = -lGL

CXXFLAGS = -std=c++17 $(WARNING_FLAGS) $(INCLUDE_OTHER_FLAGS) $(INCLUDE_SFML_FLAGS) $(DEBUG_FLAGS)
LDFLAGS = $(LD_IMGUI_FLAGS) $(LD_SFML_FLAGS)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : clean all
