# #####################################################################
# Makefile pour programme en C++
# #####################################################################
NAME	=	headerbrowser
SRC	=	main.cc
# #####################################################################
IPATH	=	-I. -I../include
LDPATH	=	-L. -L../lib -lxhb2html -lhead2xhb -lstyx
EXEOPT	=	-g2
# #####################################################################
CC	=	g++ -Wall -pedantic
RM	=	/bin/rm -f
OBJS	=	$(SRC:.cc=.o)

CFLAGS	=	$(IPATH)
LDFLAGS	=	$(EXEOPT) $(LDPATH)
# #####################################################################
$(NAME): $(OBJS) $(SRC)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(NAME) $(OBJS) *~
	rm -rf hbresult-html

all: clean $(NAME)

.cc.o:
	$(CC) $(CFLAGS) -c $<
