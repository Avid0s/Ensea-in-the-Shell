# Ensea-in-the-Shell
Rendus des exercices pour les TP de Programmation Système en deuxiemme année à l'ENSEA, semestre 7.

## 1. Affichage d’un message d’accueil, suivi d’un prompt simple.
<img width="597" height="88" alt="image" src="https://github.com/user-attachments/assets/c196246a-561f-44f0-9e8e-143a20b1fb10" />\
Notre code commence par instancier le message d'introduction et le prompt sous la forme de chaines de caractères, et définit la taille du message d'introduction pour ensuite l'afficher.\
Ensuite il lance une boucle while(1) qui va tourner constamment qui correspond au "runtime" de notre micro shell, affiche le prompt, et attends avec une autre boucle while(1). Cette deuxième boucle sera retirée sur la suite et sert uniquement sur cet exercice pour ne pas afficher le prompt en boucle.


## 2. Exécution de la commande saisie et retour au prompt (REPL : read–eval–print loop) :
<img width="616" height="190" alt="image" src="https://github.com/user-attachments/assets/b69e6060-a690-4e34-81b8-f4d0a97f41cd" />\
### a) Lecture de la commande saisie,
Nous lisons la commande donnée avec la fonction "read" comme précédemment, et la saugardons sous la forme d'une chaine de caractères.

### b) Exécution d’une commande simple (sans argument),
Nous créeons un fork qui execute lui la commande donnée dans ce nouveau terminal , puis se ferme automatiquement après cette execution. 

### c) Retour au prompt enseash % et attente de la commande suivante.
Avec le wait(null) le fork parent reste ouvert attends la mort de son fils, après cela, il reviens en fonctionnement normal et attends la prochaine commande.


## 3. Gestion de la sortie du shell avec la commande “exit” ou un <ctrl>+d
<img width="721" height="205" alt="image" src="https://github.com/user-attachments/assets/c5b6b219-33a9-4dcd-a0c9-1c8b3749d427" />\
Nous sauvegardons le "exit" de la meme manière que la commande simple avec un read, puis nous faisons une comparaison pour voir si le message correspon à la chaine de caractères "exit\0", et nous vérifions aussi avec un or (||) si c'est un message vide avec juste "\0", ce qui correspond aussi à une sortie sous la forme d'un "ctrl+d".


## 4.Affichage du code de retour (ou du signal) de la commande précédente dans le prompt :
<img width="722" height="103" alt="image" src="https://github.com/user-attachments/assets/42caddfa-b730-46a5-9480-12eb6ae4193e" />\
Nous recuperons la valeur de signal ou de l'exit renvoyée par la fonction, puis nous utilisons la fonction **sprintf** pour créer une chaine de caracyères avec cette variable dedans, puis nous affichons cette chaine de caractères de la meme manière que le prompt, mais avec une verification en if pour afficher soit le signal, soit le exit number en dependant de celui qui est non nul.


## 5. Mesure du temps d’exécution de la commande en utilisant l’appel clock_gettime :
<img width="158" height="89" alt="image" src="https://github.com/user-attachments/assets/19b7f51d-04c9-4f42-89f2-d9b05d8eca15" />\
Nous utilisons la fonction **gettime** avant et après l'execution de la commande, puis nous faisons une soustraction des deux valeures, ce qui nous donne le temps d'execution. Nous l'affichons de la meme manière que la question précedente avec le **sprintf** à la suite du prompt et le exit et signal number.


## 6. Exécution d’une commande complexe (avec arguments) :
<img width="1063" height="81" alt="image" src="https://github.com/user-attachments/assets/bc55a5d8-acb6-419b-808c-311f22acb6a4" />\
Nous prenons en compte maintenant jusqu'a 16 arguments. Nous parcourons le message de commande tant qu'il n'est pas nul, et separons les arguments differents en regardant les emplacements d'espaces dans le message. Puis nous les executons avec la meme partie de code que celle precedemment utilisée sur la Q2, maintenant modifiée pour utiliser la fonction **execvp** qui est faite pour l'execution de commandes avec arguments.

## 7. "Gestion des redirections vers stdin et stdout avec ‘<’ et ‘>’ :
<img width="607" height="429" alt="image" src="https://github.com/user-attachments/assets/e1c652d7-0897-4afc-86fc-43f5025b43f6" />
De la meme manière que pour trouver les espaces entre arguments, nous cherchons les caractères ">" et "<" dans l'input. Sur un ">" le fichier est ouvert en WriteOnly, sur un "<" en ReadOnly, puis la commande avant le "<" ou ">" est executée, dans le cas du ">" ce qui est renvoyé dans la commande est ecrit dans le fichier, et le fichier est fermé

## 8. Gestion de la redirection de type pipe avec ‘|’ :
<img width="969" height="121" alt="image" src="https://github.com/user-attachments/assets/62935ec4-b4dd-4784-b41f-cdfc17dd5cfc" />/
Gestion des pipe permettant de chainer 2 commandes (comme ls |wc -l ). Le shell cree un pipe, redirige stdout de la 1ere commande vers stdin de la 2eme commande, et execute les 2 en parallele.
