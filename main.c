#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "hash/hash.h"
#include "avltree/avltree.h"
#include "avltree/lists/queue.h"
#include "avltree/lists/stack.h"
#define LARGO 256
#define CAPACIDAD 1000
#define OPERACION 1
#define EXTENSION 2
#define COMPRENSION 3
#define EXCESO 4
#define ERROR 5
#define IMPRIMIR 6
#define SALIR 7


int intervalo_verificar(char *inicio, char *final, Intervalo * intervalo) {
  char *errorI;
  double inicioD = strtod(inicio, &errorI);
  char *errorF;
  double finalD = strtod(final, &errorF);

  if (strcmp(errorI, "") != 0 || strcmp(errorF, "") != 0)
    return 0;
  if (finalD < inicioD)
    return 0;
  intervalo->inicio = inicioD;
  intervalo->final = finalD;
  return 1;
}


char funcion_verificar(char *inicio, char *igual, char *final, int leidos) {
  if(strcmp(inicio, "salir") == 0){
    if (leidos == 1)
      return SALIR;
  } else if(strcmp(inicio, "imprimir") == 0){
    printf("Pase el imprimir\n");
    if(leidos == 2)
      return IMPRIMIR;
  } else if(strcmp(igual, "=") == 0){
    printf("Pase el igual");
    if(leidos == 3){
      if(final[0] == '{')
        if(strncmp(final, "{x :", 4) == 0)
          return COMPRENSION;
        else
          return EXTENSION;
      else
        return OPERACION;
    }
  }
  return ERROR;
}


/*
void insertar_extension(Hash* hash, char* alias, char* conjunto){

}

void insertar_comprension(Hash* hash, char* alias, char* conjunto);

void ejecutar_operacion(Hash* hash, char* alias, char* operacion);






*/




// Procesamiento de entrada.

void copiar_seccion(char *comando, char *parte, int i, int *cont,
                    int *indexToken, char eow) {
  if (comando[i] == eow) {
    (*indexToken)++;
    (*cont) = -1;
  } else
    parte[(*cont)] = comando[i];
}

char entrada_validar(char *comando, char* inicio, char* igual, char* operacion) {
  int i = 0, cont = 0;
  int indexToken = 0;
  char eows[] = "  ";

  for (; comando[i] != '\n' && comando[i] != '\r'; i++, cont++) {
    // Copiamos la opreracion
    if (indexToken == 2)
      copiar_seccion(comando, operacion, i, &cont, &indexToken, '\n');
    // Copiamos la igualdad
    if (indexToken == 1)
      copiar_seccion(comando, igual, i, &cont, &indexToken, eows[1]);
    // Copiamos el inicio.
    if (indexToken == 0)
      copiar_seccion(comando, inicio, i, &cont, &indexToken, eows[0]);
  }
  printf("Index: %d\n", indexToken+1);
  printf("Cadena inicio: %s-FINAL-\n", inicio);
  printf("Cadena igual: %s-FINAL-\n", igual);
  printf("Cadena operacion: %s-FINAL-\n", operacion);
  return funcion_verificar(inicio, igual, operacion, ++indexToken);
}

int main() {

  int salida = 1;
  Hash* hash = hash_crear(CAPACIDAD);

  printf("Interfaz 1.0\n");
  while (salida) {
    char *comando = malloc(sizeof(char) * LARGO);
    char *inicio = calloc(LARGO, sizeof(char));
    char *igual = calloc(LARGO, sizeof(char));
    char *operacion = calloc(LARGO, sizeof(char));
    int identificador;
    // leemos con \n incluido
    fgets(comando, LARGO, stdin);
    // Si se excede la capacidad maxima queda caracteres en el buffer,
    // en ese caso limpiamos el buffer y notificamos el error.
    if (strlen(comando) == LARGO - 1){
      scanf("%*[^\n]");
      scanf("%*c");
      identificador = EXCESO;
    } else {
      //comando[LARGO-1] = '\0';
      identificador = entrada_validar(comando, inicio, igual, operacion);
    }
    
    // Dependiendo del identificador la accion sera distinta.
    switch (identificador) {
    case OPERACION:
      printf("Llegaste a la operacion\n");
      //obtener_realizar_operacion(hash, inicio, operacion);
      break;
    
    case EXTENSION:
      printf("Llegaste a extension\n");
      //insertar_extension(hash, inicio, operacion);
      break;
    
    case COMPRENSION:
      printf("Llegaste a comprension\n");
      //insertar_comprension(hash, inicio, operacion);
      break;

    case EXCESO:
      printf("Largo excedido\n");
      break;

    case ERROR:
      printf("ERROR - Elemento invalido dentro del comando\n");
      break;
    
    case IMPRIMIR:
      printf("Llegaste a imprimir\n");
      //itree_imprimir(hash_conjunto(hash, igual), intervalo_imprimir);
      break;

    case SALIR:
      salida = 0;
      break;

    default:
      printf("ERROR - Caso desconocido, no debiste llegar aqui...");
      break;
    }
    // Libero la memoria de los comandos
    free(comando);
    free(inicio);
    free(igual);
    free(operacion);
  }
  // Se destruye la tabla hash de conjuntos.
  hash_destruir(hash);
  return 0;
}

  /*
  AVLTree A = itree_crear();
  Intervalo *intervalo1 = malloc(sizeof(Intervalo));
  Intervalo *intervalo2 = malloc(sizeof(Intervalo));
  Intervalo *intervalo3 = malloc(sizeof(Intervalo));
  intervalo1->inicio = 1;
  intervalo1->final = 2;
  intervalo2->inicio = 7;
  intervalo2->final = 8;
  intervalo3->inicio = 14;
  intervalo3->final = 15;
  A = itree_insertar(A, intervalo1);
  A = itree_insertar(A, intervalo2);
  A = itree_insertar(A, intervalo3);

  AVLTree B = itree_crear();
  Intervalo* intervalo4 = malloc(sizeof(Intervalo));
  intervalo4->inicio = 3;
  intervalo4->final = 4;
  B = itree_insertar(B, intervalo4);

  AVLTree D = itree_crear();
  Intervalo* intervalo5 = malloc(sizeof(Intervalo));
  intervalo5->inicio = 1;
  intervalo5->final = 7;
  D = itree_insertar(D, intervalo5);

  AVLTree I = itree_crear();
  Intervalo* intervalo6 = malloc(sizeof(Intervalo));
  intervalo6->inicio = -INT_MAX;
  intervalo6->final = INT_MAX;
  I = itree_insertar(I, intervalo6);

  AVLTree C = conjuntoavl_union(A, B);
  printf("Conjunto union A u B:\n");
  itree_imprimir(C, intervalo_imprimir);
  printf("\n");

  AVLTree E = conjuntoavl_union(A, D);
  printf("Conjunto union A u D:\n");
  itree_imprimir(E, intervalo_imprimir);
  printf("\n");

  AVLTree H = conjuntoavl_union(A, I);
  printf("Conjunto union A u I:\n");
  itree_imprimir(H, intervalo_imprimir);
  printf("\n");
  // ----------
  AVLTree F = conjuntoavl_interseccion(A, B);
  printf("Conjunto interseccion A i B:\n");
  itree_imprimir(F, intervalo_imprimir);
  printf("\n");

  AVLTree G = conjuntoavl_interseccion(A, D);
  printf("Conjunto interseccion A i D:\n");
  itree_imprimir(G, intervalo_imprimir);
  printf("\n");

  AVLTree J = conjuntoavl_interseccion(A, I);
  printf("Conjunto interseccion A i I:\n");
  itree_imprimir(J, intervalo_imprimir);
  printf("\n");
  // ----------
  AVLTree K = conjuntoavl_resta(A, B);
  printf("Conjunto resta A r B:\n");
  itree_imprimir(K, intervalo_imprimir);
  printf("\n");

  AVLTree L = conjuntoavl_resta(A, D);
  printf("Conjunto resta A r D:\n");
  itree_imprimir(L, intervalo_imprimir);
  printf("\n");

  AVLTree M = conjuntoavl_resta(A, I);
  printf("Conjunto resta A r I:\n");
  itree_imprimir(M, intervalo_imprimir);
  printf("\n");

  AVLTree N = conjuntoavl_resta(I, A);
  printf("Conjunto resta I r A:\n");
  itree_imprimir(N, intervalo_imprimir);
  printf("\n");
  // ----------
  AVLTree O = conjuntoavl_complemento(A);
  printf("Conjunto complemento A:\n");
  itree_imprimir(O, intervalo_imprimir);
  printf("\n");

  AVLTree V = itree_crear();
  Intervalo* intervalo7 = malloc(sizeof(Intervalo));
  intervalo7->inicio = INVALINI;
  intervalo7->final = INVALFIN;
  V = itree_insertar(V, intervalo7);

  AVLTree P = conjuntoavl_complemento(V);
  printf("Conjunto complemento vacio:\n");
  itree_imprimir(P, intervalo_imprimir);
  printf("\n");

  AVLTree Q = conjuntoavl_complemento(I);
  printf("Conjunto complemento infinito:\n");
  itree_imprimir(Q, intervalo_imprimir);
  printf("\n");

  AVLTree Ir = itree_crear();
  Intervalo* intervalo8 = malloc(sizeof(Intervalo));
  intervalo8->inicio = -INT_MAX;
  intervalo8->final = 0;
  Intervalo* intervalo9 = malloc(sizeof(Intervalo));
  intervalo9->inicio = 1;
  intervalo9->final = INT_MAX;
  Ir = itree_insertar(Ir, intervalo8);
  Ir = itree_insertar(Ir, intervalo9);

  AVLTree R = conjuntoavl_complemento(Ir);
  printf("Conjunto complemento infinito compuesto:\n");
  itree_imprimir(R, intervalo_imprimir);
  printf("\n");

  itree_destruir(A);
  itree_destruir(B);
  itree_destruir(C);
  itree_destruir(D);
  itree_destruir(E);
  itree_destruir(F);
  itree_destruir(G);
  itree_destruir(H);
  itree_destruir(I);
  itree_destruir(J);
  itree_destruir(K);
  itree_destruir(L);
  itree_destruir(M);
  itree_destruir(N);
  itree_destruir(O);
  itree_destruir(P);
  itree_destruir(Q);
  itree_destruir(R);
  itree_destruir(V);
  itree_destruir(Ir);
  */
  // TODO pasar las funciones de hash.c a hash.h