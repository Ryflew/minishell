Consigne :

• Vous devez programmer un mini interpréteur de commandes UNIX.
• Cet interpréteur doit afficher un prompt (un simple "$> " par exemple) et attendre
que vous tapiez une ligne de commande, validée par un retour à la ligne.
• Le prompt n’est de nouveau affiché qu’après la fin de l’exécution de la commande.
• Les lignes de commande sont simples, pas de pipes, pas de redirections ou autres
fonctions avancées.
• Les exécutables sont ceux que l’on peut trouver dans les chemins indiqués dans la
variable PATH.
• Dans le cas où l’exécutable ne peut être trouvé, il faut afficher un message d’erreur
et réafficher le prompt.
• Vous devez gérer les erreurs sans utiliser errno, en affichant un message adapté
sur la sortie d’erreur.
• Vous devez gérer correctement le PATH et l’environnement (copie du char **environ
système).
• Vous devez implémenter une série de builtins : echo, cd, setenv, unsetenv, env,
exit.
• Vous choisissez le shell de référence que vous souhaitez.

Bonus :

• La gestion des signaux, et notamment Ctrl-C. L’utilisation de variables globales
est autorisé dans le cadre de la gestion des signaux.
• La gestion des droits d’exécution dans le PATH.
• La complétion.
• La séparation des commandes avec le " ;".
• D’autres bonus que vous jugez utiles.
