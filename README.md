# Ensea-in-the-Shell
Rendus des exercices pour les TP de Programmation Système en deuxiemme année à l'ENSEA, semestre 7.

## 1. Affichage d’un message d’accueil, suivi d’un prompt simple.
<img width="700" height="86" alt="image" src="https://github.com/user-attachments/assets/a437a2ba-8f97-4bc9-9d51-4425c2a033ea" />\
Notre code commence par instancier le message d'introduction et le prompt, et définit la taille du message d'introduction pour ensuite l'afficher.\
Ensuite il lance une boucle while(1) qui va tourner constamment qui correspond au "runtime" de notre micro shell, affiche le prompt, et attends avec une autre boucle while(1). Cette deuxième boucle sera retirée sur la suite et sert uniquement sur cet exercice pour ne pas afficher le prompt en boucle.

## 2. Exécution de la commande saisie et retour au prompt (REPL : read–eval–print loop) :
<img width="779" height="216" alt="image" src="https://github.com/user-attachments/assets/964db006-aada-4630-b0d1-ee9371cba883" />\

### a) Lecture de la commande saisie,
Nous lisons la commande fortune avec la fonction "read" comme précédemment.

### b) Exécution d’une commande simple (sans argument),
Nous créeons un fork qui execute lui la commane fortune (ce qui affiche la citation) puis se ferme automatiquement après cette execution.

### c) Retour au prompt enseash % et attente de la commande suivante.
Avec le wait(null) le fork parent attends la fin de l'execution pour continuer dans le runtime du shell


## 3. Gestion de la sortie du shell avec la commande “exit” ou un <ctrl>+d
   

