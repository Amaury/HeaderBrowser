# Nom de la bibliotheque statique
NAME	=	libhead2xhb.a

# Noms des fichiers source (noms.c)
SRC	=	head2xhb.cc \
		parseheaderfile.cc \
		parsehbtag.cc \
		parsehbtagclass.cc \
		parsehbtagdefine.cc \
		parsehbtagenum.cc \
		parsehbtagfunction.cc \
		parsehbtagheader.cc \
		parsehbtagstruct.cc \
		parsehbtagtypedef.cc \
		parsehbtagvar.cc
# #####################################################################

# Chemins vers les fichiers a inclure
IPATH	=	-I. -I../../include

# Options de compilation
EXEOPT	=	-O2	# -g pour debugger

# #####################################################################

CC	=	g++ -Wall -pedantic
RM	=	/bin/rm -f
OBJS	=	$(SRC:.cc=.o)

CFLAGS	=	$(IPATH)
LDFLAGS	=	$(EXEOPT) $(LDPATH)

# #####################################################################

$(NAME): $(OBJS)
	ar -r $(NAME) $(OBJS)
	ranlib $(NAME)
	mv $(NAME) ..

clean:
	$(RM) $(NAME) $(OBJS) *~

all: clean $(NAME)

.cc.o:
	$(CC) $(CFLAGS) -c $<
