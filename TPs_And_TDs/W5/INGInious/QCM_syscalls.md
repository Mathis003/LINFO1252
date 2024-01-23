# Questions sur les Appels Système

## Allocation de Mémoire sur le Heap

**Quels appels système sont utilisés pour l'allocation de mémoire sur le heap ?**

Les appels système utilisés pour l'allocation de mémoire sur le heap sont `brk` et `sbrk`.

## Implémentation des Breakpoints

**Quel appel système peut-être utilisé pour implémenter des breakpoints ?**

L'appel système `ptrace` peut être utilisé pour implémenter des breakpoints.

## Erreur EFAULT

**Lors de l'exécution de l'un de mes codes, j'observe qu'une erreur EFAULT a lieu. Qui peut-être le syscall responsable de cette erreur ? (sélectionnez toutes les réponses possibles)**

Les syscalls qui peuvent être responsables de l'erreur EFAULT sont :
- `execve`
- `gettimeofday`
- `write`

## Syscall Fork

**En considérant la page du syscall fork, sélectionnez toutes les affirmations correctes.**

- Un processus enfant hérite des descripteurs de fichier ouverts par son processus père.
- En cas de succès, fork retourne 0 dans le processus enfant.
- Les compteurs de temps CPU (liés au syscall times) sont remis à zéro dans le processus enfant.

## Syscalls Wait, Waitpid, et Waitid

**Lisez attentivement la page des syscalls wait, waitpid et waitid, puis sélectionnez toutes les affirmations correctes.**

- Dans waitpid, si l'argument options vaut WNOHANG et que le processus enfant n'est pas encore terminé, waitpid retourne immédiatement.
- wait et waitpid peuvent stocker le statut de retour du processus enfant et ensuite tester que celui-ci a terminé normalement avec la macro WIFEXITED.

## Syscalls Relatifs au Temps

**Il existe beaucoup de syscalls relatifs au temps. Explorez les et sélectionnez toutes les affirmations correctes.**

- L'appel système clock_gettime peut prendre en argument un pointeur vers une structure timespec.
- L'appel système time peut prendre comme argument un pointeur vers une variable time_t qui contiendra le nombre de secondes écoulées depuis l'Epoch.