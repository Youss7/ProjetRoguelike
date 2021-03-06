
#le compilateur c utilisé
CC = gcc

#les options de compilation
FLAGS = -Wall -Wextra

#le nom du programme
NAME = roguelike

#le nom du dossier contenant les sources
SRCDIR = source

#les fichiers source
SRC = $(wildcard $(SRCDIR)/*/*.c)

#les fichiers compilés
OBJ = $(SRC:.c=.o)

#le nom du dossier contenant les sources des tests
TESTDIR = test

#le nom du dossier contenant la documentation
DOCDIR = doc

LIBS = -lpthread

build: $(OBJ)
	$(CC) $(FLAGS) $^ $(LIBS) -o $(NAME).exe

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(SRCDIR)/*/*.o *.exe

rebuild: clean build

run: build
	./$(NAME).exe

debug:
	$(CC) $(FLAGS) -g $(SRC) -o $(NAME)
	gdb -e $(NAME)_debug.exe

#génère la documentation
docgen:
	rm -rf ./$(DOCDIR)
	mkdir ./$(DOCDIR)
	doxygen

#copie la documentation générée dans le dossier nom_utilisateur/public_html/nom_projet, et change leur permissions pour les rendre lisibles par tous, ainsi, si cette command est lancée depuis un ordinateur de l'université, la documentation sera mise à jour et consultables à l'adresse http://info.univ-lemans.fr/~nom_utilisateur/roguelike/index.html
docpost: docgen
	rm -rf ~/public_html/$(NAME)
	mkdir -p ~/public_html/$(NAME)
	cp -R $(DOCDIR)/html/* ~/public_html/$(NAME)
	chmod -R 755 ~/public_html/$(NAME)

all: clean build docgen

commit: clean
	git add *
	git commit -a

push: commit
	git push
