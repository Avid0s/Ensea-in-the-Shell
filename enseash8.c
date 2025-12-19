#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>   // pour utiliser wait dans le fork
#include <time.h>  // c'est pour la question 5

int main(void){
	char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	char *prompt = "enseash % ";
	char input[128];
	int message_size;
    char *ciao = "Bye bye...\n";
    int last_exit = 0;
    int last_signal = 0;
    char prompt_buf[128];

    char *argv_exec[16];
    

    
    
    
    struct timespec start, end;
    long difference_ms; // On veut le temps en ms
    

    write(STDOUT_FILENO, welcome,strlen(welcome)); // on utilise "STDOUT_FILENO" pour l'afficher directement dans le terminal
    

	while (1) {
		
		
		if (last_signal != 0) {
			
			sprintf(prompt_buf, "enseash [sign:%d|%ldms] %% ", last_signal,difference_ms); //on a rajouté le temps en ms
					

		        } else {
		        	sprintf(prompt_buf, "enseash [exit:%d|%ldms] %% ", last_exit, difference_ms);
		        }
		
		
		
		
		
		
		write(STDOUT_FILENO, prompt_buf, strlen(prompt_buf));
		
        message_size= read(STDIN_FILENO,input, sizeof(input)-1);  // on utilise "STDIN_FILENO" pour lire l'entrée
        input[message_size-1] = '\0';  // pour definir la fin du message, et on enleve \n
        if ((strcmp(input ,"exit\0") ==0)  || ((strcmp(input ,"\0") ==0) )  ){ // on fait une comparaison des mots du message en éntrée et 'exit', et on break si c'est exit.
        													// on n'oublie pas le /n/0 car quand on appuie sur la touche 'entrée' cela fait /n
        													// le CTRL+D est équivalent à unmessage vide --> \0 donc on utilise cette comparaison
        	write(STDOUT_FILENO, ciao, strlen(ciao));
            
        	break;
	}
        
        
        
        int argc_exec = 0;

        char *token = strtok(input, " "); // découpe sur l'entrée
        while(token != NULL && argc_exec < 15) {
                	        argv_exec[argc_exec++] = token;
                	        token = strtok(NULL, " ");			// on va executer 1 par 1 les différents arguments
                	    }
        argv_exec[argc_exec] = NULL; //  pour le execvp 
       

        clock_gettime(CLOCK_MONOTONIC, &start);  // on prend le temps au début
        
        
        
        int pipe_index = -1;				// si -1 alors pas de |
        for (int i = 0; argv_exec[i] != NULL; i++) {
            if (strcmp(argv_exec[i], "|") == 0) {
                pipe_index = i;				//on affecte à pipe_index, l'index où il y a "|"
                break;
            }
        }

        
        if (pipe_index==-1){				// c'est ce qu'on ajoute pour la Q8 : si il n'y a pas de "|", ça marche comme à la Q7, sinon, dans le else on rajoute la démarche
			pid_t pid = fork();
			if (pid == 0){
				
				for (int i = 0; argv_exec[i] != NULL; i++) {
					if (strcmp(argv_exec[i], ">") == 0) {
									int fd = open(argv_exec[i+1], O_WRONLY | O_CREAT);
									if (fd < 0) { perror("open"); _exit(1); }
									dup2(fd, STDOUT_FILENO); // redirige stdout
									close(fd);
									argv_exec[i] = NULL; // coupe argv pour execvp
					}else if (strcmp(argv_exec[i], "<") == 0) {
									int fd = open(argv_exec[i+1], O_RDONLY);
									if (fd < 0) { perror("open"); _exit(1); }
									dup2(fd, STDIN_FILENO); // redirige stdin
									close(fd);
									argv_exec[i] = NULL;
						}
					}
				
				
				
				
				
					execvp(argv_exec[0], argv_exec);
					

							//execlp("", "", NULL);
							
				} else {
						// parent attend la fin de l'enfant, car sinon on ne voit plus le prompt réapparaitre
									int status;
									waitpid(pid, &status, 0);
									clock_gettime(CLOCK_MONOTONIC, &end); // la fin du chrono
									
									difference_ms = (end.tv_sec - start.tv_sec) * 1000 +
													 (end.tv_nsec - start.tv_nsec) / 1000000;
									
									if (WIFEXITED(status)) {
										last_exit = WEXITSTATUS(status);
										last_signal = 0;
									} else if (WIFSIGNALED(status)) {
										last_signal = WTERMSIG(status);
										last_exit = 0;
					}
					
				}   
		
		}else {
			
				int fd[2];		//fd[1] pour ecriture et fd[0] pour lecture
			    pipe(fd);

			    argv_exec[pipe_index] = NULL; // on coupe les arguments au niveau de "|"
			    
			    // argv_exec = {"ls", "|", "wc", "-l", NULL} devient argv_exec = {"ls", NULL, "wc", "-l", NULL}

 
// On sépare les 2 commandes : 
			    char **cmd1 = argv_exec;
			    char **cmd2 = &argv_exec[pipe_index + 1];

			    //tout ce que cmd1 ecrit va dans le pipe
			    pid_t pid1 = fork();
			    if (pid1 == 0) {
			        dup2(fd[1], STDOUT_FILENO);
			        close(fd[0]);
			        close(fd[1]);
			        execvp(cmd1[0], cmd1);
			        _exit(1);
			    }
			    pid_t pid2 = fork();
			    if (pid2 == 0) {
			           dup2(fd[0], STDIN_FILENO);
			           close(fd[0]);
			           close(fd[1]);
			           execvp(cmd2[0], cmd2);
			           _exit(1);
			       }

			     close(fd[0]);	//fermeture du pipe
			     close(fd[1]);
			       
			     int status2;		     
			     waitpid(pid1, NULL, 0);
			     waitpid(pid2, &status2, 0);
			     clock_gettime(CLOCK_MONOTONIC, &end);

			     difference_ms = (end.tv_sec - start.tv_sec) * 1000 +
			                     (end.tv_nsec - start.tv_nsec) / 1000000;

			     if (WIFEXITED(status2)) {
			         last_exit = WEXITSTATUS(status2);
			         last_signal = 0;
			     } else if (WIFSIGNALED(status2)) {
			         last_signal = WTERMSIG(status2);
			         last_exit = 0;
			     }

			
		}

}
}