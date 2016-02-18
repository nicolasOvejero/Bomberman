GREEN           =       @if [ -t 1 ]; then tput setaf 2 ; fi
BLUE            =       @if [ -t 1 ]; then tput setaf 4 ; fi
RESET           =       @if [ -t 1 ]; then tput sgr0 ; fi

CXX		=	g++

NAME		=	bomberman

SRCSDIR		=       srcs/
INCSDIR		=       incs/
OBJSDIR		=       objs/

SRCS		=	$(SRCSDIR)Marvin.cpp		\
			$(SRCSDIR)Bomb.cpp		\
			$(SRCSDIR)Intro.cpp		\
			$(SRCSDIR)LoadTexture.cpp	\
			$(SRCSDIR)Menu.cpp		\
			$(SRCSDIR)SubMenu.cpp		\
			$(SRCSDIR)PlayMenu.cpp		\
			$(SRCSDIR)Cube.cpp		\
			$(SRCSDIR)Text.cpp		\
			$(SRCSDIR)MenuOption.cpp	\
			$(SRCSDIR)Map.cpp		\
			$(SRCSDIR)Thread.cpp		\
			$(SRCSDIR)Sound.cpp		\
			$(SRCSDIR)Camera.cpp		\
			$(SRCSDIR)IA.cpp		\
			$(SRCSDIR)Game.cpp		\
			$(SRCSDIR)MyExept.cpp		\
			$(SRCSDIR)Bonus.cpp		\
			$(SRCSDIR)Save.cpp		\
			$(SRCSDIR)BasicShader.cpp	\
			$(SRCSDIR)main.cpp		\

OBJS		=	$(SRCS:$(SRCSDIR)%.cpp=$(OBJSDIR)%.o)

#CXXFLAGS	+=	-Wextra -Wall -Werror
CXXFLAGS	+=	-L`pwd`/libs -Wl,-rpath=`pwd`/libs

CXXFLAGS	+=	-std=c++11 -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -ldl -DLOG=false
CXXFLAGS	+=	-lX11 -lGLU -lXext
CXXFLAGS	+=	-lSDL2_mixer
CXXFLAGS	+=	-lpthread

LDFLAGS		=	-I./includes
LDFLAGS		+=	-I./incs

all:		$(NAME)

$(OBJSDIR)%.o:	$(SRCSDIR)%.cpp
		@mkdir -p objs
		@$(CXX) -c -o $@ $< $(LDFLAGS) $(CXXFLAGS) 2> ./.tmp || echo -n ""
		@if [ -s ./.tmp ]; then \
			if [ -t 1 ]; then tput setaf 1 ; fi ; \
			echo " [ Error ] $<" ; \
			if [ -t 1 ]; then tput sgr0 ; fi ;\
			cat ./.tmp ; rm -fr ./.tmp ; exit 1; \
		else \
			if [ -t 1 ]; then tput setaf 4 ; fi ;\
			echo -n " [ OK ] " ; \
			if [ -t 1 ]; then tput sgr0 ; fi ;\
			rm -fr ./.tmp ; \
		fi
		$(GREEN)
		@echo "$< "
		$(RESET)

$(NAME):	$(OBJS)
		$(GREEN)
		@echo -n "Compiling : "
		$(RESET)
		@$(CXX) -MMD -MP $(OBJS) -o $(NAME) $(LDFLAGS) $(CXXFLAGS)
		$(BLUE)
		@echo "[ OK ]"
		$(RESET)

clean:
		$(GREEN)
		@echo -n "Erasing objects : "
		$(RESET)
		@rm -rf $(OBJS)
		@rm -Rf $(OBJSDIR)
		$(BLUE)
		@echo "[ OK ]"
		$(RESET)

fclean:		clean
		$(GREEN)
		@echo -n "Erasing binary : "
		$(RESET)
		@rm -rf $(NAME)
		$(BLUE)
		@echo "[ OK ]"
		$(RESET)

re:		fclean all
