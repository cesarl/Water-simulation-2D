NAME		=	exec

CC		=	g++

RM		=	rm -f

CPPFLAGS	=	-W -Wextra -Wall -Werror -MMD -g -O2

LDFLAGS		=	-L/usr/lib -lallegro -lallegro_dialog -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_image -lGLU

CPPFLAGS	+=	-I. -I/usr/include/allegro5 \
			-I../src/debug \
			-I../src/manager \
			-I../src/utilities \
			-I../src/component \
			-I../src/loader \
			-I../src/system \
			-I../src/generator \
			-I../src

SRCS		=	../src/debug/ILogger.cpp \
			../src/debug/Exception.cpp \
			../src/manager/Resource.cpp \
			../src/utilities/Vector3d.cpp \
			../src/manager/ComponentManager.cpp \
			../src/manager/EntityManager.cpp \
			../src/manager/SystemManager.cpp \
			main.cpp


OBJS		=	$(SRCS:.cpp=.o)

DEPS		=	$(SRCS:.cpp=.d)

ECHO		=	echo -e

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(CPPFLAGS)
			@$(ECHO) '\033[1;37;44m> Compiled {\033[4m$(NAME)}\033[0m'

clean		:
			@$(RM) $(OBJS) $(DEPS)
			@$(ECHO) '\033[1;37;41m> Directory cleaned\033[0m'

fclean		:	clean
			@$(RM) $(NAME)
			@$(ECHO) '\033[1;37;41m> Remove executable\033[0m'

re		:	fclean all

.PHONY		:	all clean re

-include $(DEPS)
