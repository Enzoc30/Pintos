#include <stdlib.h>
#include <stdio.h>


// Estructura del thread
struct thread
{   
    // Se balancea mediante su priority
    int priority;
    int data ;
};


struct nodeRedBlack
{
    // Nodos
    struct thread* data;
    struct nodeRedBlack* parent ; 
    struct nodeRedBlack* left;
    struct nodeRedBlack* right;
    
    // Informacion del color del nodo
    int color ; 

};


// Estructura del RedBlackTree

struct RedBlackTree{
   struct nodeRedBlack* node  ;

};
/*
 Puedes implementar un Red Black tree, para este caso
 quiero que implementes todas las funciones insert, delete y search
 Ademas de que el insert debe tener todas las funcionalidad para balancear
 Quiero tambien que hagas un test, insertando threads  

*/

