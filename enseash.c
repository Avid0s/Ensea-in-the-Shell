//test

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(void){
	char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	char *prompt = "enseash % ";
    int BUFSIZE = strlen(welcome); //On veut la taille de notre message pour utiliser write apres


    write(STDOUT_FILENO, welcome,BUFSIZE); // on utilise "1" pour l'afficher directement dans le terminal

	while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt));
        while(1){   // ici, on met un while(1) pour bloquer et prendre une capture d'écran.

        }
	}

}

