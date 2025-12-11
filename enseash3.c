#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>   // pour utiliser wait dans le fork


int main(void){
	char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	char *prompt = "enseash % ";
	char input[128];
	int message_size;
    int BUFSIZE = strlen(welcome); //On veut la taille de notre message pour utiliser write apres
    char *ciao = "Bye bye...\n";


    

    write(1, welcome,BUFSIZE); // on utilise "STDOUT_FILENO" pour l'afficher directement dans le terminal
    

	while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt));
        message_size= read(STDIN_FILENO,input, sizeof(input)-1);  // on utilise "STDIN_FILENO" pour lire l'entrée
        input[message_size] = '\0';  // pour definir la fin du message
        if ((strcmp(input ,"exit\n\0") ==0)  || ((strcmp(input ,"\0") ==0) )  ){ // on fait une comparaison des mots du message en éntrée et 'exit', et on break si c'est exit.
        													// on n'oublie pas le /n/0 car quand on appuie sur la touche 'entrée' cela fait /n
        													// le CTRL+D est équivalent à unmessage vide --> \0 donc on utilise cette comparaison
        	write(STDOUT_FILENO, ciao, strlen(ciao));
        	break;
	}
        if (strcmp(input, "fortune\n\0") == 0) {
            pid_t pid = fork();
            if (pid == 0){
                        execlp("fortune", "fortune", NULL);
                        
            } else {
                    // parent attend la fin de l'enfant, car sinon on ne voit plus le prompt réapparaitre
                    wait(NULL);
                }
            
        }
           
       
	
	
	
	}												

}

