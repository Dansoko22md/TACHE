prog:main.o personnage.o 
	gcc  main.o personnage.o -o prog -lSDL  -lSDL_image -lSDL_mixer -lSDL_ttf -g
main.o:main.c
	gcc -c main.c  -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf  -g
personnage.o:personnage.c
	gcc -c personnage.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g

