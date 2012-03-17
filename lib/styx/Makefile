# Nom de la bibliotheque statique
NAME	=	libstyx.a

# Noms des fichiers source (noms.c)
SRC	=	styx_sax.cc \
		styx_sax_attr.cc \
		styx_dom.cc \
		styx_dom_node.cc \
		styx_dom_namespace.cc

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
