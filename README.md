# Ensea-in-the-Shell
Rendus des exercices pour les TP de Programmation Système en deuxiemme année à l'ENSEA, semestre 7.

## 1. Affichage d’un message d’accueil, suivi d’un prompt simple.
<img width="597" height="88" alt="image" src="https://github.com/user-attachments/assets/c196246a-561f-44f0-9e8e-143a20b1fb10" />\
Notre code commence par instancier le message d'introduction et le prompt, et définit la taille du message d'introduction pour ensuite l'afficher.\
Ensuite il lance une boucle while(1) qui va tourner constamment qui correspond au "runtime" de notre micro shell, affiche le prompt, et attends avec une autre boucle while(1). Cette deuxième boucle sera retirée sur la suite et sert uniquement sur cet exercice pour ne pas afficher le prompt en boucle.


## 2. Exécution de la commande saisie et retour au prompt (REPL : read–eval–print loop) :
<img width="616" height="190" alt="image" src="https://github.com/user-attachments/assets/b69e6060-a690-4e34-81b8-f4d0a97f41cd" />\
Puisque nosu sommes revenus sur cette question , vous pouvez observer des elements de fonctions suivantes.
### a) Lecture de la commande saisie,
Nous lisons la commande donnée avec la fonction "read" comme précédemment.

### b) Exécution d’une commande simple (sans argument),
Nous créeons un fork qui execute lui la commande donnée puis se ferme automatiquement après cette execution. 

### c) Retour au prompt enseash % et attente de la commande suivante.
Avec le wait(null) le fork parent reste ouvert attends la mort de son fils, puis attends la prochaine commande.


## 3. Gestion de la sortie du shell avec la commande “exit” ou un <ctrl>+d
<img width="721" height="205" alt="image" src="https://github.com/user-attachments/assets/c5b6b219-33a9-4dcd-a0c9-1c8b3749d427" />\
Nous detectons le "exit" de la meme manière que la commande simple, mais nous vérifions aussi avec un or (||) si c'est un message vide avec juste "\0", ce qui correspond aussi à une sortie.


## 4.Affichage du code de retour (ou du signal) de la commande précédente dans le prompt :
<img width="722" height="103" alt="image" src="https://github.com/user-attachments/assets/42caddfa-b730-46a5-9480-12eb6ae4193e" />\
Nous recuperons la valeur de signal ou exit renvoyée par la fonction, puis nous l'affichons dans notre prompt avec la fonction **sprintf**


## 5. Mesure du temps d’exécution de la commande en utilisant l’appel clock_gettime :
<img width="158" height="89" alt="image" src="https://github.com/user-attachments/assets/19b7f51d-04c9-4f42-89f2-d9b05d8eca15" />\
Nous utilisons la fonction **gettime** avant et après l'execution de la commande, pui nous faisons une soustraction des deux valeures, ce qui nous donne le temsp d'execution. Nosu l'affichons de la meme manière que la question précedente avec le **sprintf**


## 6. Exécution d’une commande complexe (avec arguments) ;
<img width="1063" height="81" alt="image" src="https://github.com/user-attachments/assets/bc55a5d8-acb6-419b-808c-311f22acb6a4" />\
Nous prenons en compte maintenant jusqu'a 16 arguments, nous recuperons chaque argument individuel de l'input en les separant grace à l'espace qui les sépare, pusi nosu les executons grace à la fonction **execvp** qui est faite pour.



