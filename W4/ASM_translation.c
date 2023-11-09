// Les fonctions suivantes ont été écrite en assembleur. Traduisez les en une version équivalente en C.



// mp:
//   subl $8, %esp
//   movl 16(%esp), %edx
//   movl 12(%esp), %ecx
//   movl %ecx,%eax
//   addl %ecx,%ecx
//   addl %eax,%ecx
//   cmpl %edx,%ecx
//   jle m1
//   movl %edx, %eax
//   addl $8, %esp
//   ret
//  m1:
//   movl %ecx, %eax
//   addl $8, %esp
//   ret


/*
Explication supplémentaire du code assembleur:

mp:                         Étiquette du bloc "mp"
  subl $8, %esp             Soustrait 8 de la valeur dans ESP pour allouer de l'espace sur la pile      (Libère de la place pour les deux paramètres)
  movl 16(%esp), %edx       Charge la valeur à l'adresse ESP + 16 dans EDX                              (Récupère le deuxième paramètre)
  movl 12(%esp), %ecx       Charge la valeur à l'adresse ESP + 12 dans ECX                              (Récupère le premier paramètre)
  
  movl %ecx,%eax            Copie la valeur de ECX dans EAX
  addl %ecx,%ecx            Double la valeur de ECX                                                     (Bloc qui effectue "int result = 3 * param1;")
  addl %eax,%ecx            Ajoute la valeur de EAX à ECX
  
  cmpl %edx,%ecx            Compare les valeurs de EDX et ECX
  jle m1                    Si EDX est inférieur ou égal à ECX => saut à l'étiquette "m1"               (Bloc qui effectue "if (result >= param2) {m1}")
  
  movl %edx, %eax           Copie la valeur de EDX dans EAX                                             (Ligne inutile, je pense => effectue "param1 = param2;")
  addl $8, %esp             Ajoute 8 à ESP pour libérer de l'espace sur la pile                         (Libère la mémoire utilisée pour les paramètres)
  ret                       Fin du BLOC "mp"                                                            (return statement)
  
 m1:                        Étiquette du bloc "m1"
  movl %ecx, %eax           Copie la valeur de ECX dans EAX                                             (Bloc qui effectue "result = param2;")
  addl $8, %esp             Ajoute 8 à ESP pour libérer de l'espace sur la pile                         (Libère la mémoire utilisée pour les paramètres)
  ret                       Fin du BLOC "m1"                                                            (return statement)
*/


int mp(int param1, int param2)
{
    int result = 3 * param1;
    if (param2 <= result) result = param2;
    return result;
}


// f:
//   subl $8, %esp
//   movl 20(%esp), %edx
//   movl 16(%esp), %ecx
//   movl 12(%esp), %ebx
//   addl %ebx, %ecx
//   cmpl %edx, %ecx
//   jle m31
//   movl %edx, %eax
//   addl $8, %esp
//   ret
// m31:
//   movl %ecx, %eax
//   addl $8, %esp
//   ret

int f(int param1, int param2, int param3)
{
    int result = param1 + param2;
    if (param3 <= result) result = param3;
    return result;
}


// fct:
//     movl 4(%esp), %eax
//     cmpl $0,%eax
//     jg n
//     movl $-1,%eax
//     ret
// n:  movl $0,%ebx
//     movl %eax, %ecx
//     movl $0, %eax
//     movl $0, %edx
// l:  addl $2, %ebx
//     addl %ebx, %eax
//     addl $1, %edx
//     cmpl %ecx, %edx
//     jl l
//     ret

int fct(int param)
{
    if (param <= 0) return -1;
    else
    {
        int ebx = 0;
        int eax = 0;
        int edx = 0;
        int ecx = param; 
        do {
            ebx += 2;
            eax += ebx;
            edx++;
        } while (edx < ecx);
        return eax;
    }
}

int main()
{
    return 0;
}