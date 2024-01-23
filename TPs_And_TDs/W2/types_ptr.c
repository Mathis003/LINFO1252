/*
Déclarez la variable x comme un pointeur sur un int de manière à ce que cette séquence d’instructions soit illégale

int i = 0;
x = &i;

De même que cette instruction

*x = 0;
*/
const int *const x;

/*
Supposez que la ligne suivante se trouve dans un autre fichier, dans l’espace global.

int x;

Écrivez la déclaration qui vous permet d’utiliser cette même variable x depuis le fichier courant (typiquement, cette ligne se trouvera dans un header).
*/
extern int x;


/*
Déclarez la variable x comme un int accessible uniquement depuis le fichier actuel (ou plutôt, l’unité de compilation actuelle).
*/
static int x;

/*
Déclarez la variable x comme un pointeur sur un int en faisant en sorte que l’instruction suivant soit illégale.

*x = 4;

Tout en autorisant cette séquence d’instructions

int i = 0;
x = &i;
*/
const int *x;

/*
Déclarez la variable x comme un pointeur sur un int en faisant en sorte que la séquence d’instructions suivante soit illégale.

int i = 0;
x = &i;

Tout en autorisant cette instruction-ci.

*x = 0;
*/
int *const x;