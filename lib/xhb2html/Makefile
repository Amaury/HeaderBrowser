# Nom de la bibliotheque statique
NAME	=	libxhb2html.a

# Noms des fichiers source (noms.c)
SRC	=	create_functions.cc \
		create_macro_functions.cc \
		create_unions.cc \
		create_class.cc \
		create_globals.cc \
		create_objects.cc \
		create_enum_constants.cc \
		create_header_dir.cc \
		create_structs.cc \
		create_enums.cc \
		create_macro_constants.cc \
		create_typedefs.cc \
		xhb2html.cc


# #####################################################################

# Chemins vers les fichiers a inclure
IPATH	=	-I./html-output-headers -I. -I../../include

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
