#include <ctype.h>
#include <stdlib.h>
#include "lista_team.h"

typedef struct{         //struct auxiliar para guardar jugadores de una seleccion  
   char name[MAX];
   int position;  //1=Arq 2=PC 3=LI 4=LD 5=MC 6=SC 7=MI 8=MD 9=DC 10=MP 11=SD
   int number_shirt;
} players;

typedef struct{
   char country[MAX];
   players p[11];
} players_of_team;


//Funciones del menu
void load_list(listateam *, team *, int *); //carga n equipos en lista
void show_all_list(listateam ); //muestra toda la lista
void show_team(team );
void preload(listateam *); //precargar pais,dt,capitan,grupo,inicializar puntaje en 0
void show_for_country(listateam ); //busca un equipo por pais (usa search_for_country)
void show_all_insame_phase(listateam );  //mostrar todos los de misma fase
void show_team_inorder_points_recursion(listateam , int );  //funcion recursiva que muestra los equipos ordenados por puntaje
void delete_team_for_country(listateam *, char []);  //borra de la lista segun el pais y almacena sus datos en un archivo
void load_players(players_of_team [], int *);
void show_dt_players(listateam , players_of_team [], char [], int );

//Funciones internas
void load_team(team *); //carga los equipos para luego meterlos en load_list
int control_country(char []);
int control_group(char );
void search_for_country(listateam , char []); //busca por pais



int main(){

 listateam list;
 team t;
 players_of_team pt[32];
 char c[MAX];
 int opcion, cant = 0, aux = 0, j, cantidad = 0;

 init_lista_team(&list);

 do{
   printf ("\n|                       |||||||||||    ||||   |||||||||||   |||||||||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n|                       |||||||||||    ||||   |||||||||||   |||||||||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n| ------------------------------------------------------------------------------------------------|");
   printf ("\n|     ||| ||| |||  ||||||||  ||||||||    |||      ||||||         |||||||  |||  |||  ||||||||      |");
   printf ("\n|     ||| ||| |||  |||  |||  |||  |||    |||      |||  ||        |||      |||  |||  |||  |||      |");
   printf ("\n|     ||| ||| |||  |||  |||  ||||||||    |||      |||   ||       |||      |||  |||  ||||||||      |");
   printf ("\n|     ||| ||| |||  |||  |||  |||   |||   |||      |||  ||        |||      |||  |||  |||           |");
   printf ("\n|     |||||||||||  ||||||||  |||    |||  |||||||  ||||||         |||||||  ||||||||  |||           |");
   printf ("\n|                                                                                                 |");
   printf ("\n| --------------------------------------------------- | ----------------------------------------- |");
   printf ("\n|        1. Cargar equipos                            |  2. Mostrar todos                         |");
   printf ("\n|        3. Mostrar por pais                          |  4. Mostrar los de misma fase             |");
   printf ("\n|        5. Mostrar goleadores en orden               |  6. Mostrar asistidores en orden          |");
   printf ("\n|        7. Mostrar equipos ordenados por puntaje     |  8. Modificar partidos                    |");
   printf ("\n|        9. Borrar segun pais                         |  10. Modificar la fase                    |");
   printf ("\n|        11. Mostrar goleadores                       |  12. Modificar asistidores                |");
   printf ("\n|        13. Mostrar actualizaciones paginadas        |  14. Cargar en archivo segun continente   |");
   printf ("\n|        15. Realizar una precarga                    |  16. Mostrar partidos perdidos de un pais |");
   printf ("\n|        17. Cargar plantel                           |  18. Mostrar dt y plantel                 |");
   printf ("\n|        19. Cargar goleadores                        |  20. Salir del programa                   |");
   printf ("\n| ------------------------------------------------------------------------------------------------|\n\n");
   scanf("%d", &opcion);

   while(opcion > 20 || opcion < 1){
      printf("Por favor, ingrese un valor correcto segun la opcion que desea utilizar\n");
      scanf("%d", &opcion);
   }
   
   switch(opcion){

      case 1: load_list(&list, &t, &cant);
              break;

      case 2: if(cant == 0){
                  printf("La lista esta vacia, no hay nada para mostrar\n");
               }
               else{
                  show_all_list(list);
               }
               break;

      case 3: if(cant == 0){
                  printf("La lista esta vacia, no hay nada para mostrar\n");
               }
               else{
                  show_for_country(list);
               }
              break;

      case 4: if(cant == 0){
                  printf("La lista esta vacia, no hay nada para mostrar\n");
               }
               else{
                  show_all_insame_phase(list);
               }
               break;

      case 9: if(cant == 0){
                  printf("La lista esta vacia, no hay nada para mostrar\n");
               }
               else{
                  do{
                     printf("|-------------------------------------------------------|\n");
                     printf("| Por favor ingrese un pais que dispute el Mundial 2022 |\n");
                     printf("|-------------------------------------------------------|\n");
                     printf("|      Qatar, Ecuador, Senegal, Paises bajos            |\n");
                     printf("|      Inglaterra, Iran, Estados Unidos, Gales          |\n");
                     printf("|      Argentina, Arabia Saudita, Mexico, Polonia       |\n");
                     printf("|      Francia, Australia, Dinamarca, Tunez             |\n");
                     printf("|      España, Costa Rica, Alemania, Japon              |\n");
                     printf("|      Belgica, Canada, Marruecos, Croacia              |\n");
                     printf("|      Brasil, Serbia, Suiza, Camerun                   |\n");
                     printf("|      Portugal, Ghana, Uruguay, Corea del Sur          |\n");
                     printf("|-------------------------------------------------------|\n");
                     scanf(" %[^\n]", c);
                     for (j = 0; c[j]!= '\0'; j++){
                      c[j] = toupper(c[j]);
                     }
                     aux = control_country(c);
                  }while(aux != 0);
                  delete_team_for_country(&list, c);
               }
               break;

      case 15: preload(&list);
               cant += 1;
               break;

      case 17: load_players(pt, &cantidad);
               break;

      case 18: do{
                  printf("|-------------------------------------------------------|\n");
                  printf("| Por favor ingrese un pais que dispute el Mundial 2022 |\n");
                  printf("|-------------------------------------------------------|\n");
                  printf("|      Qatar, Ecuador, Senegal, Paises bajos            |\n");
                  printf("|      Inglaterra, Iran, Estados Unidos, Gales          |\n");
                  printf("|      Argentina, Arabia Saudita, Mexico, Polonia       |\n");
                  printf("|      Francia, Australia, Dinamarca, Tunez             |\n");
                  printf("|      España, Costa Rica, Alemania, Japon              |\n");
                  printf("|      Belgica, Canada, Marruecos, Croacia              |\n");
                  printf("|      Brasil, Serbia, Suiza, Camerun                   |\n");
                  printf("|      Portugal, Ghana, Uruguay, Corea del Sur          |\n");
                  printf("|-------------------------------------------------------|\n");
                  scanf(" %[^\n]", c);
                  for (j = 0; c[j]!= '\0'; j++){
                     c[j] = toupper(c[j]);
                  }
                  aux = control_country(c);
               }while(aux != 0);
               show_dt_players(list, pt, c, cantidad);
               break;

      default: printf("Fin del sistema, que tenga buen dia!\n");
   }
 } while(opcion != 20);

 return 0;
}




void load_list(listateam *list, team *t, int *cant){
   
   int i = 0, n;
  
   do{
      printf("¿Cuántas selecciones quiere cargar? Máximo 32\n");
      scanf("%d", &n);
   }while(n > 32 || n < 1);

   while(i < n){

      if(isFull_lista(list) == 0){

         printf("------------- Cargando Equipo -------------\n");
         load_team(t);
         insert_lista_team(list, *t);
      }
      else{
         printf("Error! No hay mas espacio para cargar equipos\n");
      }
      i++;
      *cant += 1;
   }
   
}


void show_all_list(listateam list){

   reset_lista(&list);
   while(!isOos_lista(list)){
      printf("\n");
      printf("Datos de la seleccion\n");
      show_team(copy_lista(list));
      printf("----------------------\n");
      forward_lista(&list);
   }
}


int control_country(char c[]){
 int aux;

 if (strcmp(c, "QATAR") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "ECUADOR") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "SENEGAL") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "PAISES BAJOS") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "INGLATERRA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "IRAN") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "ESTADOS UNIDOS") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "GALES") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "ARGENTINA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "ARABIA SAUDITA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "MEXICO") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "POLONIA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "FRANCIA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "AUSTRALIA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "DINAMARCA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "TUNEZ") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "ESPAÑA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "COSTA RICA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "ALEMANIA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "JAPON") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "BELGICA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }
 
 if (strcmp(c, "CANADA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "MARRUECOS") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "CROACIA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "BRASIL") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "SERBIA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "SUIZA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "CAMERUN") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "PORTUGAL") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "GHANA") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "URUGUAY") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }

 if (strcmp(c, "COREA DEL SUR") == 0){
    aux = 0;
    return aux;
 }
 else{
    aux = 1;
 }
 return aux;  
}


int control_group(char g){

   int aux;

   if (g == 'A'){
      aux = 0;
      return aux;
   }
   else{
      aux = -1;
   }

   if (g == 'B'){
      aux = 0;
      return aux;
   }
   else{
      aux = -1;
   }

   if (g == 'C'){
      aux = 0;
      return aux;
   }
   else{
      aux = -1;
   }

   if (g == 'D'){
      aux = 0;
      return aux;
   }
   else{
      aux = -1;
   }

   if (g == 'E'){
      aux = 0;
      return aux;
   }
   else{
      aux = -1;
   }

   if (g == 'F'){
      aux = 0;
      return aux;
   }
   else{
      aux = -1;
   }

   if (g == 'G'){
      aux = 0;
      return aux;
   }
   else{
      aux = -1;
   }

   if (g == 'H'){
      aux = 0;
      return aux;
   }
   else{
      aux = -1;
   }
}


void load_team(team *t){

   int j, aux, f;
   char c[MAX], g;

   do{
      printf("|-------------------------------------------------------|\n");
      printf("| Por favor ingrese un pais que dispute el Mundial 2022 |\n");
      printf("|-------------------------------------------------------|\n");
      printf("|      Qatar, Ecuador, Senegal, Paises bajos            |\n");
      printf("|      Inglaterra, Iran, Estados Unidos, Gales          |\n");
      printf("|      Argentina, Arabia Saudita, Mexico, Polonia       |\n");
      printf("|      Francia, Australia, Dinamarca, Tunez             |\n");
      printf("|      España, Costa Rica, Alemania, Japon              |\n");
      printf("|      Belgica, Canada, Marruecos, Croacia              |\n");
      printf("|      Brasil, Serbia, Suiza, Camerun                   |\n");
      printf("|      Portugal, Ghana, Uruguay, Corea del Sur          |\n");
      printf("|-------------------------------------------------------|\n");
      scanf(" %[^\n]", c);
      for (j = 0; c[j]!= '\0'; j++){
         c[j] = toupper(c[j]);
      }
      aux = control_country(c);
   }while(aux != 0);
   carga_country(t, c);
    

   printf("Ingrese el director técnico de la selección\n");
   scanf(" %[^\n]", c);
   carga_dt(t, c);


   printf("Ingrese el apellido del capitán del equipo\n");
   scanf(" %[^\n]", c);
   carga_captain(t, c);


   do{
      printf("Ingrese el grupo en el que se encuentra la selección\n");
      printf("A\tB\tC\tD\tE\tF\tG\tH\n");
      fflush(stdin);
      scanf(" %c", &g);
      aux = control_group(g);
   }while(aux != 0);
   carga_group(t, g);
    

   do{
      printf("Ingrese la fase donde se encuentra actualmente la selección\n");
      printf("1.Fase de Grupos\n2.Octavos de Final\n3.Cuartos de Final\n4.Semifinal\n5.Final\n");
      scanf("%d", &f);
   }while(f > 5 || f < 1);
   carga_phase(t, f);


   switch(f){
      case 1: do{
                  printf("Ingrese el puntaje actual de la selección\n");
                  scanf("%d", &aux);
               }while(aux > 9 || aux < 1);
               carga_points(t, aux);
               break;
      
      case 2: do{
                  printf("Ingrese el puntaje actual de la selección\n");
                  scanf("%d", &aux);
               }while(aux > 12 || aux < 7);
               carga_points(t, aux);
               break;

      case 3: do{
                  printf("Ingrese el puntaje actual de la selección\n");
                  scanf("%d", &aux);
               }while(aux > 15 || aux < 10);
               carga_points(t, aux);
               break;

      case 4: do{
                  printf("Ingrese el puntaje actual de la selección\n");
                  scanf("%d", &aux);
               }while(aux > 18 || aux < 13);
               carga_points(t, aux);
               break;

      case 5: do{
                  printf("Ingrese el puntaje actual de la selección\n");
                  scanf("%d", &aux);
               }while(aux > 21 || aux < 10);
               carga_points(t, aux);
               break;

      default: printf("\n");
   }
}


void show_team(team t){

   printf("El pais es %s\n", mostrar_country(t));
   printf("El DT es %s\n", mostrar_dt(t));
   printf("El capitan es %s\n", mostrar_captain(t));
   printf("El grupo es %c\n", mostrar_group(t));
   
   switch(mostrar_etapa(t)){
      case 1: printf("La etapa actual es Fase de Grupos\n");
              break;

      case 2: printf("La etapa actual es Octavos de Final\n");
              break;

      case 3: printf("La etapa actual es Cuartos de Final\n");
              break;
      
      case 4: printf("La etapa actual es Semifinal\n");
              break;

      case 5: printf("La etapa actual es Final\n");
              break;
      
      default: printf("\n");
   }

   printf("Los puntos son %d\n", mostrar_points(t));
}


void preload(listateam *list){

   char country[MAX], dt[MAX], captain[MAX], group;
   int p;
   team t;
   init_team(&t);

   FILE *preLoad;
   preLoad = fopen("PrecargaTeam.txt", "r+");

   if(preLoad == NULL){
      printf("No se pudo acceder al archivo\n");
      exit(1);
   }
   else{
      while(!feof(preLoad)){

         fscanf(preLoad, "%[^\n]\n", country);
         carga_country(&t, country);
         fscanf(preLoad, "%[^\n]\n", dt);
         carga_dt(&t, dt);
         fscanf(preLoad, "%[^\n]\n", captain);
         carga_captain(&t, captain);
         fscanf(preLoad, "%c\n", &group);
         carga_group(&t, group);
         fscanf(preLoad, "%d\n", &p);
         carga_points(&t, p);
         insert_lista_team(list, t);
      }
      printf("Se ha realizado correctamente la carga de los datos\n");
   }
   fclose(preLoad);
}


void search_for_country(listateam list, char c[]){

   int contador = 0;
   reset_lista(&list);
   while(!isOos_lista(list)){

      if(strcmp(mostrar_country(copy_lista(list)), c) == 0){
         contador++;
      }
      forward_lista(&list);
   }
   if(contador != 0){
      reset_lista(&list);
      printf("---- Se encontraron %d coincidencias\n", contador);
      while(!isOos_lista(list)){
         if(strcmp(mostrar_country(copy_lista(list)), c) == 0){
            show_team(copy_lista(list));
         }
         forward_lista(&list);
      }
   }
   else{
      printf("No se han encontado coincidencias\n");
   }
}


void show_for_country(listateam list){

   char c[MAX];
   int aux, j;

   do{
      printf("|-------------------------------------------------------|\n");
      printf("| Por favor ingrese un pais que dispute el Mundial 2022 |\n");
      printf("|-------------------------------------------------------|\n");
      printf("|      Qatar, Ecuador, Senegal, Paises bajos            |\n");
      printf("|      Inglaterra, Iran, Estados Unidos, Gales          |\n");
      printf("|      Argentina, Arabia Saudita, Mexico, Polonia       |\n");
      printf("|      Francia, Australia, Dinamarca, Tunez             |\n");
      printf("|      España, Costa Rica, Alemania, Japon              |\n");
      printf("|      Belgica, Canada, Marruecos, Croacia              |\n");
      printf("|      Brasil, Serbia, Suiza, Camerun                   |\n");
      printf("|      Portugal, Ghana, Uruguay, Corea del Sur          |\n");
      printf("|-------------------------------------------------------|\n");
      scanf(" %[^\n]", c);
      for (j = 0; c[j]!= '\0'; j++){
         c[j] = toupper(c[j]);
      }
      aux = control_country(c);
   }while(aux != 0);
   search_for_country(list, c);
}


void show_all_insame_phase(listateam list){

   int fase, contador = 0;
   reset_lista(&list);

   do{
      printf("Ingrese la fase que desea buscar\n");
      printf("1.Fase de Grupos\n2.Octavos de Final\n3.Cuartos de Final\n4.Semifinal\n5.Final\n");
      scanf("%d", &fase);
   }while(fase > 5 || fase < 1);

   while(!isOos_lista(list)){
      if(mostrar_etapa(copy_lista(list)) == fase){
         contador++;
      }
      forward_lista(&list);
   }
   if(contador != 0){
      reset_lista(&list);
      while(!isOos_lista(list)){

         if(mostrar_etapa(copy_lista(list)) == fase){
            show_team(copy_lista(list));
         }
         forward_lista(&list);
      }
   }
   else{
      printf("No hay equipos en la fase indicada\n");
   }
}


void delete_team_for_country(listateam *list, char c[]){

   team t;
   int contador = 0;
   reset_lista(list);
   while(!isOos_lista(*list)){
      if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
         contador += 1;
      }
      forward_lista(list);
   }
   
   if(contador != 0){
      reset_lista(list);
      FILE *loadDeleted;
      loadDeleted = fopen("Deleted.txt", "a+");
      if(loadDeleted == NULL){
         printf("No se ha podido abrir el archivo\n");
         exit(1);
      }
      else{
         while(!isOos_lista(*list)){
            if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
               fprintf(loadDeleted, "Pais: %s\n", mostrar_country(copy_lista(*list)));
               fprintf(loadDeleted, "El DT es: %s\n", mostrar_dt(copy_lista(*list)));
               fprintf(loadDeleted, "El capitan es: %s\n", mostrar_captain(copy_lista(*list)));
               fprintf(loadDeleted, "El grupo es: %c\n", mostrar_group(copy_lista(*list)));
               fprintf(loadDeleted, "El puntaje es: %d\n", mostrar_points(copy_lista(*list)));
               switch(mostrar_etapa(copy_lista(*list))){
                  case 1: fprintf(loadDeleted, "La etapa es Fase de grupos\n");
                          break;
                  case 2: fprintf(loadDeleted, "La etapa es Octavos de final\n");
                          break;
                  case 3: fprintf(loadDeleted, "La etapa es Cuartos de final\n");
                          break;
                  case 4: fprintf(loadDeleted, "La etapa es Semifinal\n");
                          break;
                  case 5: fprintf(loadDeleted, "La etapa es Fase de grupos\n");
                          break;
               }
               printf("Copia al archivo completa!\n");
            }
            forward_lista(list);
         }
      }
      fclose(loadDeleted);

      reset_lista(list);
      while(!isOos_lista(*list)){
         if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
            suppress_lista_team(list);
            printf("Se ha borrado correctamente el archivo\n");
         }
         else{
            forward_lista(list);
         }
      }
   }
}


void load_players(players_of_team pt[], int *cantidad){

   char country[MAX], name[MAX];
   int aux, j, i, n, k, l;
   int auxcant = *cantidad;

   do{
      printf("Cuantos planteles desea cargar?\n");
      scanf("%d", &n);
   }while(n > 32 - *cantidad || n < 1);

   for(i = auxcant; i < n + auxcant; i++){
      do{
         printf("|-------------------------------------------------------|\n");
         printf("| Por favor ingrese un pais que dispute el Mundial 2022 |\n");
         printf("|-------------------------------------------------------|\n");
         printf("|      Qatar, Ecuador, Senegal, Paises bajos            |\n");
         printf("|      Inglaterra, Iran, Estados Unidos, Gales          |\n");
         printf("|      Argentina, Arabia Saudita, Mexico, Polonia       |\n");
         printf("|      Francia, Australia, Dinamarca, Tunez             |\n");
         printf("|      España, Costa Rica, Alemania, Japon              |\n");
         printf("|      Belgica, Canada, Marruecos, Croacia              |\n");
         printf("|      Brasil, Serbia, Suiza, Camerun                   |\n");
         printf("|      Portugal, Ghana, Uruguay, Corea del Sur          |\n");
         printf("|-------------------------------------------------------|\n");
         scanf(" %[^\n]", country);
         for (j = 0; country[j]!= '\0'; j++){
            country[j] = toupper(country[j]);
         }
         aux = control_country(country);
      }while(aux != 0);
      strcpy(pt[i].country, country);

      for (k = 0; k < 11; k++){

         printf("Ingrese el apellido del jugador\n");
         scanf(" %[^\n]", name);
         for (l = 0; name[l]!= '\0'; l++){
            name[l] = toupper(name[l]);
         }
         strcpy(pt[i].p[k].name, name);

         do{
            printf("Ingrese el numero de su camiseta\n");
            scanf("%d", &pt[i].p[k].number_shirt);
         }while(pt[i].p[k].number_shirt < 1 || pt[i].p[k].number_shirt > 50);
         do{
            printf("Ingrese la posicion en la que juega\n");
            printf("1: Arquero\n2: Primer central\n3: Lateral Izquierdo\n4: Lateral Derecho\n5: Mediocentro\n");
            printf("6: Segundo central\n7: Carrilero izquierdo\n8: Carrilero derecho\n9: Delantero centro\n");
            printf("10: Enganche\n11: Segundo delantero\n");
            scanf("%d", &pt[i].p[k].position);
         }while(pt[i].p[k].position < 1 || pt[i].p[k].position > 11);
      }
      *cantidad += 1;
   }
}


void show_dt_players(listateam list, players_of_team pt[], char c[], int cantidad){

   int i, aux = 0, j;
   for (i = 0; i < cantidad; i++){
      if(strcmp(pt[i].country, c) == 0){
         aux += 1;
      }
   }
   if(aux == 0){
      printf("No ha cargado un plantel para la seleccion %s\n", c);
   }
   else{
      reset_lista(&list);
      while(!isOos_lista(list)){

         for(i = 0; i < cantidad; i++){
            if(strcmp(pt[i].country, mostrar_country(copy_lista(list))) == 0){

               printf("El DT es %s\n", mostrar_dt(copy_lista(list)));
               printf("El capitan es %s\n", mostrar_captain(copy_lista(list)));

               for(j = 0; j < 11; j++){

                  printf("Apellido: %s\t", pt[i].p[j].name);
                  switch(pt[i].p[j].position){
                     case 1: printf("Arquero\t");
                             break;
                     case 2: printf("Primer central\t");
                             break;
                     case 3: printf("Lateral izquierdo\t");
                             break;
                     case 4: printf("Lateral derecho\t");
                             break;
                     case 5: printf("Mediocentro\t");
                             break;
                     case 6: printf("Segundo central\t");
                             break;
                     case 7: printf("Carrilero izquierdo\t");
                             break;
                     case 8: printf("Carrilero derecho\t");
                             break;
                     case 9: printf("Delantero centro\t");
                             break;
                     case 10: printf("Enganche\t");
                              break;
                     case 11: printf("Segundo delantero\t");
                              break;
                  }
                  printf("Dorsal %d\n", pt[i].p[j].number_shirt);
               }
            }
         }
         forward_lista(&list);
      }
   }
}

