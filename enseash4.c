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
    int last_exit = 0;
    int last_signal = 0;
    char prompt_buf[128];

    char *argv_exec[2];
    argv_exec[0] = input;   // commande tapée
    argv_exec[1] = NULL;    

    

    write(1, welcome,BUFSIZE); // on utilise "STDOUT_FILENO" pour l'afficher directement dans le terminal
    

	while (1) {
		
		
		if (last_signal != 0) {
			
			sprintf(prompt_buf, "enseash [sign:%d] %% ", last_signal);
					/*char *prompt2 = "enseash [sign:";
		            write(STDOUT_FILENO,"enseash [sign:", strlen(prompt2));					
		            WriteNum()
		            write(STDOUT_FILENO,"", strlen(prompt));*/

		        } else {
		        	sprintf(prompt_buf, "enseash [exit:%d] %% ", last_exit);
		        	//write(STDOUT_FILENO,"enseash [exit:"last_exit"]  ", strlen(prompt));
		        }
		
		
		
		
		
		
		write(STDOUT_FILENO, prompt_buf, strlen(prompt_buf));
		
       // write(STDOUT_FILENO, prompt, strlen(prompt));
        message_size= read(STDIN_FILENO,input, sizeof(input)-1);  // on utilise "STDIN_FILENO" pour lire l'entrée
        input[message_size-1] = '\0';  // pour definir la fin du message, et on enleve \n
        if ((strcmp(input ,"exit\0") ==0)  || ((strcmp(input ,"\0") ==0) )  ){ // on fait une comparaison des mots du message en éntrée et 'exit', et on break si c'est exit.
        													// on n'oublie pas le /n/0 car quand on appuie sur la touche 'entrée' cela fait /n
        													// le CTRL+D est équivalent à unmessage vide --> \0 donc on utilise cette comparaison
        	write(STDOUT_FILENO, ciao, strlen(ciao));
        	break;
	}
        
            pid_t pid = fork();
            if (pid == 0){
            	execvp(argv_exec[0], argv_exec);
                        //execlp("", "", NULL);
                        
            } else {
                    // parent attend la fin de l'enfant, car sinon on ne voit plus le prompt réapparaitre
            					int status;
            	                waitpid(pid, &status, 0);
            	                if (WIFEXITED(status)) {
            	                    last_exit = WEXITSTATUS(status);
            	                    last_signal = 0;
            	                } else if (WIFSIGNALED(status)) {
            	                    last_signal = WTERMSIG(status);
            	                    last_exit = 0;
                }
            }
            
        
           
       
	
	
	
	}												

}
