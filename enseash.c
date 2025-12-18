#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(void){
	char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	char *prompt = "enseash % ";

    write(STDOUT_FILENO, welcome, strlen(welcome)); //On utilise "STDOUT_FILENO" pour l'afficher directement dans le terminal
													//On recupère la taille du message pour correctement l'afficher avec le write.

	while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt));
        while(1){   // ici, on met un while(1) pour bloquer et prendre une capture d'écran. Il sera retiré dans les questions futures.
        }
	}

}

