Pour effectuer ce test, il faut modifier le code :
  Enlevez les caractères délimitant un commentaire entre les ligne 52 et 57 du ficher eval.c.
  De même pour la ligne 61 et 75 du même fichier.
  Enlevez les caractères délimitant un commentaire entre les ligne 163 et 164 du ficher repl.c.

Ce test permet de vérifier que la forme define a une influence uniquement sur l'environnement courant et que set! modifie la première occurence d'une variable mais dans l'ensemble des environnements.
addenv() est une fonction créant un nouvel environnement.
Lorsque l'utilisateur entre addenv, un nouvel environnement est créé.
Ce fonctionnement permet uniquement de tester define et set! et sera bien sûr à modifier à l'incrément suivant.
