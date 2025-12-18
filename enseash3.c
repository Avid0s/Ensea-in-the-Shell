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
    char *ciao = "Bye bye...\n";

    write(STDOUT_FILENO, welcome,strlen(welcome)); // on utilise "STDOUT_FILENO" pour l'afficher directement dans le terminal
    
	while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt));
        message_size= read(STDIN_FILENO,input, sizeof(input)-1);  // on utilise "STDIN_FILENO" pour lire l'entrée
        input[message_size-1] = '\0';  // pour definir la fin du message, et on enleve \n
        if ((strcmp(input ,"exit\0") ==0)  || ((strcmp(input ,"\0") ==0) )  ){ // on fait une comparaison des mots du message en éntrée et 'exit', et on break si c'est exit.
        													// le CTRL+D est équivalent à unmessage vide --> \0 donc on utilise cette deuxiemme comparaison
        	write(STDOUT_FILENO, ciao, strlen(ciao));
        	break;
		}
        
        pid_t pid = fork();
        if (pid == 0){
            execvp(argv_exec[0], argv_exec);
                        
            } else {
                    // parent attend la fin de l'enfant, car sinon on ne voit plus le prompt réapparaitre
                    wait(NULL);
            }
            
        }
	
	}												

}

