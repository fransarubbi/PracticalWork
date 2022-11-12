#include <ctype.h>
#include <stdlib.h>
#include "lista_team.h"


typedef struct{         //struct auxiliar para guardar jugadores de una seleccion  
   char name[MAX];
   int position;  //1=Arq 2=PC 3=LI 4=LD 5=MC 6=SC 7=MI 8=MD 9=DC 10=MP 11=SD
   int number_shirt;
} players;


typedef struct{      // structura para almacenar planteles
   char country[MAX];
   players p[11];
} players_of_team;


typedef struct{
   char name[MAX];  //nombre del pais en cuestion
   int exists;     //1 si existe el pais, 0 si no existe
} load_country;



//Funciones del menu
void load_list(listateam *, team *, int *, load_country [], int []); //carga n equipos en lista
void show_all_list(listateam ); //muestra toda la lista
void preload(listateam *, load_country [], int []); //precargar pais,dt,capitan,grupo,inicializar puntaje en 0
void show_for_country(listateam ); //busca un equipo por pais (usa search_for_country)
void show_all_insame_phase(listateam );  //mostrar todos los de misma fase
void show_team_inorder_points_recursion(listateam , int );  //funcion recursiva que muestra los equipos ordenados por puntaje
void delete_team_for_country(listateam *, char [], load_country []);  //borra de la lista segun el pais y almacena sus datos en un archivo
void load_players(players_of_team [], int *);      // carga plantel
void show_dt_players(listateam , players_of_team [], char [], int );    // muestra dt y plantel
void load_games(listateam *, team *);    // carga partidos jugados, ganados y empatados
void show_games(listateam );     // mostrar partidos jugados, ganados y empatados
void load_goalscorer(listateam *, team *);     // cargar goleadores
void show_best_goalscorer_order(listateam );    // mostrar mejores goleadores en orden
void show_best_goalscorer(listateam );      // mostrar todos los goleadores (sin orden)
void recursive(listateam , team [], int , int , int );  // funcion recursiva que muestra ordenados por puntos
void change_points(listateam *, team *);    // funcion usada en recursive() para ordenar
void load_file_for_continet(listateam );    // carga paises segun continente indicado
void change_phase(listateam *, team *);     // cambiar etapa actual del equipo
void load_phase(listateam *, team *);      // carga goles a favor y en contra de la fase actual
void preload_players(listateam *, players_of_team [], int *);


//Funciones internas
void show_team(team );  // muestra un equipo, usada en show_all_list
void load_team(team *, load_country [], int *); //carga los equipos para luego meterlos en load_list
int control_country(char []);     // controla que ingrese un equipo que disputa la competencia
int control_group(char );       // controla que ingrese un grupo adecuado
void search_for_country(listateam , char []);     // busca por pais
void load_aux_country(load_country [], char [], int []);     // carga en una estructura auxiliar cuando se ingrese un pais
int function_control_country(load_country [], char [], int []);  // controla que el pais ya este cargado
void ordenate_recursive(listateam , team [], int , int , int );   // ordena los puntos, usada en recursive()
int function_auxiliar_control_america(char []);   // controla que sea un pais americano
int function_auxiliar_control_europa(char []);    // controla que sea un pais europeo
int function_auxiliar_control_africa(char []);    // controla que sea un pais africano
int function_auxiliar_control_asia(char []);      // controla que sea un pais asiatico
int function_auxiliar_control_oceania(char []);   // controla que sea un pais oceanico
int function_control_continent(char []);          // controla que se ingrese un continente correcto



int main(){

 listateam list;
 team t, auxiliar[32];
 players_of_team pt[32];
 load_country lc[32];
 char c[MAX];
 int opcion, cant = 0, aux = 0, j, cantidad = 0, total[1], enter;
 int i=0, cont = 0, datos_input = 0, otro_cant = 0, cant_games = 0;
 total[0] = 0;

 init_lista_team(&list);
 init_team(&t);

 do{
   printf ("\n| ----------------------------------------------------------------------------------------------- |");
   printf ("\n|                                                                                                 |");
   printf ("\n|                       |||||||||||    ||||   |||||||||||   |||||||||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n|                       |||||||||||    ||||   |||||||||||   |||||||||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n|                       |||            ||||   |||           |||   |||                             |");
   printf ("\n|                                                                                                 |");
   printf ("\n| ----------------------------------------------------------------------------------------------- |");
   printf ("\n|                                                                                                 |");
   printf ("\n|     ||| ||| |||  ||||||||  ||||||||    |||      ||||||         |||||||  |||  |||  ||||||||      |");
   printf ("\n|     ||| ||| |||  |||  |||  |||  |||    |||      |||  ||        |||      |||  |||  |||  |||      |");
   printf ("\n|     ||| ||| |||  |||  |||  ||||||||    |||      |||   ||       |||      |||  |||  ||||||||      |");
   printf ("\n|     ||| ||| |||  |||  |||  |||   |||   |||      |||  ||        |||      |||  |||  |||           |");
   printf ("\n|     |||||||||||  ||||||||  |||    |||  |||||||  ||||||         |||||||  ||||||||  |||           |");
   printf ("\n|                                                                                                 |");
   printf ("\n| --------------------------------------------------- | ----------------------------------------- |");
   printf ("\n|        1. Cargar equipos                            |  2. Mostrar todos                         |");
   printf ("\n|        3. Mostrar por pais                          |  4. Mostrar los de misma fase             |");
   printf ("\n|        5. Mostrar goleadores en orden               |  6. Mostrar equipos ordenados por puntaje |");
   printf ("\n|        7. Modificar partidos                        |  8. Borrar segun pais                     |");
   printf ("\n|        9. Mostrar goleadores                        |  10. Modificar la fase                    |");
   printf ("\n|        11. Realizar una precarga                    |  12. Mostrar partidos perdidos            |");
   printf ("\n|        13. Cargar en archivo segun continente       |  14. Cargar plantel                       |");
   printf ("\n|        15. Cargar partidos jugados                  |  16. Cargar goleadores                    |");
   printf ("\n|        17. Mostrar dt y plantel                     |  18. Cargar goles a favor y en contra     |");
   printf ("\n|        19. Realizar precarga de planteles           |  20. Salir del programa                   |");
   printf ("\n| ----------------------------------------------------------------------------------------------- |\n\n");
   scanf("%d", &opcion);

   while(opcion > 20 || opcion < 1){

      printf ("\n| ------------------------------------------------------------------------------------------------|");
      printf ("\n|             Por favor, ingrese un valor correcto segun la opcion que desea utilizar             |");
      printf ("\n| ----------------------------------------------------------------------------------------------- |");
      printf ("\n|        1. Cargar equipos                            |  2. Mostrar todos                         |");
      printf ("\n|        3. Mostrar por pais                          |  4. Mostrar los de misma fase             |");
      printf ("\n|        5. Mostrar goleadores en orden               |  6. Mostrar equipos ordenados por puntaje |");
      printf ("\n|        7. Modificar partidos                        |  8. Borrar segun pais                     |");
      printf ("\n|        9. Mostrar goleadores                        |  10. Modificar la fase                    |");
      printf ("\n|        11. Realizar una precarga                    |  12. Mostrar partidos perdidos            |");
      printf ("\n|        13. Cargar en archivo segun continente       |  14. Cargar plantel                       |");
      printf ("\n|        15. Cargar partidos jugados                  |  16. Cargar goleadores                    |");
      printf ("\n|        17. Mostrar dt y plantel                     |  18. Cargar goles a favor y en contra     |");
      printf ("\n|        19. Realizar precarga de planteles           |  20. Salir del programa                   |");
      printf ("\n| ----------------------------------------------------------------------------------------------- |\n\n");
      scanf("%d", &opcion);
   }
   
   switch(opcion){

      case 1: load_list(&list, &t, &cant, lc, total);
              break;

      case 2: if(cant == 0){
                  do{
                     printf("No hay datos cargados, utilice la opcion Cargar equipos o Realizar una precarga y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }
               else{
                  show_all_list(list);
               }
               break;

      case 3: if(cant == 0){
                  do{
                     printf("No hay datos cargados, utilice la opcion Cargar equipos o Realizar una precarga y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }
               else{
                  show_for_country(list);
               }
              break;

      case 4: if(cant == 0){
                  do{
                     printf("No hay datos cargados, utilice la opcion Cargar equipos o Realizar una precarga y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }
               else{
                  show_all_insame_phase(list);
               }
               break;

      case 5:  if(otro_cant == 0){
                  do{
                     printf("No hay goleadores cargados aun, ingrese la informacion necesaria en la opcion Cargar goleadores\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }else{
                  show_best_goalscorer_order(list);
               }  
               break;
      
      case 6:  if(cant == 0){
                  do{
                     printf("No hay datos cargados, utilice la opcion Cargar equipos o Realizar una precarga y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }else{
                  reset_lista(&list);
                  recursive(list, auxiliar, i, cont, datos_input);
               }
               break;

      case 7:  if(cant == 0){
                  do{
                     printf("No hay datos cargados, utilice la opcion Cargar equipos o Realizar una precarga y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }
               else{
                  change_points(&list, &t);
               }
               break;

      case 8: if(cant == 0){
                  do{
                     printf("No hay datos cargados, por lo tanto no hay nada para borrar\n");
                     printf("Utilice la opcion Cargar equipos o Realizar una precarga, y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
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
                  delete_team_for_country(&list, c, lc);
               }
               break;

      case 9:  if(otro_cant == 0){
                  do{
                     printf("No hay goleadores cargados aun, ingrese la informacion necesaria en la opcion Cargar goleadores\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }else{
                  show_best_goalscorer(list);
               }
               break;

      case 10: if(cant == 0){
                  do{
                     printf("No hay datos cargados, utilice la opcion Cargar equipos o Realizar una precarga y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }
               else{
                  change_phase(&list, &t);
               }
               break;

      case 11: preload(&list, lc, total);
               cant += 1;
               break;

      case 12: if(cant_games == 0){
                  do{
                     printf("No se han cargado datos de los partidos. Utilice Cargar partidos jugados y reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }else{
                  show_games(list);
               }
               break;

      case 13: if(cant == 0){
                  do{
                     printf("No hay datos cargados, utilice la opcion Cargar equipos o Realizar una precarga y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }  
               load_file_for_continet(list);
               break;

      case 14: if(cant == 0){
                  do{
                     printf("No puede cargar el plantel aun, utilice la opcion Cargar equipos o Realizar una precarga y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }else{
                  load_players(pt, &cantidad);
               }
               break;

      case 15: if(cant == 0){
                  do{
                     printf("No puede cargar datos de los partidos aun, porque no hay selecciones cargadas.\n");
                     printf("Utilice la opcion Cargar equipos o Realizar una precarga, y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }
               load_games(&list, &t);  //recordar que no funciona con precarga porq no se carga etapa
               cant_games += 1;
               break;

      case 16: if(cant == 0){
                  do{
                     printf("No puede cargar goleadores aun, porque no hay selecciones cargadas.\n");
                     printf("Utilice la opcion Cargar equipos o Realizar una precarga, y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }
               else{
                  load_goalscorer(&list, &t);
                  otro_cant += 1;
               }
               break;

      case 17: if(cant == 0){
                  do{
                     printf("No se puede mostrar planteles aun, porque no hay selecciones cargadas.\n");
                     printf("Utilice la opcion Cargar equipos o Realizar una precarga, y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
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
                  show_dt_players(list, pt, c, cantidad);
               }
               break;

      case 18: if(cant == 0){
                  do{
                     printf("No puede cargar goles a favor y en contra, porque no hay selecciones cargadas.\n");
                     printf("Utilice la opcion Cargar equipos o Realizar una precarga, y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }
               else{
                  load_phase(&list, &t);
               }
               break;

      case 19: if(cant == 0){
                  do{
                     printf("No puede cargar el plantel aun, utilice la opcion Cargar equipos o Realizar una precarga y luego reintente\n");
                     printf("Ingrese 1 para continuar...\n");
                     scanf("%d", &enter);
                  }while(enter != 1);
               }
               else{
                  preload_players(&list, pt, &cantidad);
               }
               break;
   }
 } while(opcion != 20);

 printf("\n| ----------------------------------------------------------- |");
 printf("\n|   Fin del sistema FIFA World Cup 2022 gracias por utilizar  |");
 printf("\n| ----------------------------------------------------------- |");

 return 0;
}


// FUNCIONES AUXILIARES
void load_aux_country(load_country lc[], char c[], int total[]){
   
   int i, j;
   int aux = total[0];
   for(j = 0; j < total[0]; j++){   // como el nombre queda guardado, recorro el arreglo y si lo encuentra le doy valor 1
      if(strcmp(c, lc[i].name) == 0){   // esto lo hago porque en la funcion delete, se pone 0 cuando se encuentra el nombre
         lc[i].exists = 1;
      }
   }
   for(i = aux; i < aux + 1; i++){   // si no fue cargado antes el equipo, cargarlo en una nueva posicion
      strcpy(lc[i].name, c);
      total[0] = total[0] + 1;
      lc[i].exists = 1;
   }
}


int function_control_country(load_country lc[], char c[], int total[]){
   int i, aux = 0;
   for(i = 0; i < total[0]; i++){
      if(strcmp(lc[i].name, c) == 0 && lc[i].exists == 1){
         aux = 1;
      }
   }
   return aux;
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

 if (strcmp(c, "ESPANA") == 0){
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


void load_team(team *t, load_country lc[], int total[]){

   int j, aux, repeat, f;
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
      repeat = function_control_country(lc, c, total);
      if(repeat == 1){
         printf("\nEl pais %s ya esta cargado, no se puede repetir\n");
      }
   }while(aux != 0 || repeat == 1);
   load_aux_country(lc, c, total);
   carga_country(t, c);
    

   printf("Ingrese el director técnico de la selección\n");
   scanf(" %[^\n]", c);
   for (j = 0; c[j]!= '\0'; j++){
      c[j] = toupper(c[j]);
   }
   carga_dt(t, c);


   printf("Ingrese el apellido del capitán del equipo\n");
   scanf(" %[^\n]", c);
   for (j = 0; c[j]!= '\0'; j++){
      c[j] = toupper(c[j]);
   }
   carga_captain(t, c);


   do{
      printf("Ingrese el grupo en el que se encuentra la selección\n");
      printf("A\tB\tC\tD\tE\tF\tG\tH\n");
      fflush(stdin);
      scanf(" %c", &g);
      g = toupper(g);
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
               }while(aux > 9 || aux < 0 || aux == 8);
               carga_points(t, aux);
               break;
      
      case 2: do{
                  printf("Ingrese el puntaje actual de la selección\n");
                  scanf("%d", &aux);
               }while(aux > 12 || aux < 7 || aux == 11);
               carga_points(t, aux);
               break;

      case 3: do{
                  printf("Ingrese el puntaje actual de la selección\n");
                  scanf("%d", &aux);
               }while(aux > 15 || aux < 10 || aux == 14);
               carga_points(t, aux);
               break;

      case 4: do{
                  printf("Ingrese el puntaje actual de la selección\n");
                  scanf("%d", &aux);
               }while(aux > 18 || aux < 13 || aux == 17);
               carga_points(t, aux);
               break;

      case 5: do{
                  printf("Ingrese el puntaje actual de la selección\n");
                  scanf("%d", &aux);
               }while(aux > 21 || aux < 10 || aux == 20);
               carga_points(t, aux);
               break;

      default: printf("\n");
   }

   carga_fecha(t);
}


void show_team(team t){

   statistics_phase sp_aux;
   sp_aux = mostrar_statistics_group(t);

   printf("El pais es %s\n", mostrar_country(t));
   printf("El DT es %s\n", mostrar_dt(t));
   printf("El capitan es %s\n", mostrar_captain(t));
   printf("El grupo es %c\n", mostrar_group(t));
   
   switch(mostrar_etapa(t)){
      case 1:  printf("La etapa actual es Fase de Grupos\n");
               printf("Goles a favor: %d\n", sp_aux.statistics_group_gf);
               printf("Goles en contra: %d\n", sp_aux.statistics_group_ge);
               break;

      case 2:  printf("La etapa actual es Octavos de Final\n");
               printf("Goles a favor: %d\n", sp_aux.statistics_eights_gf);
               printf("Goles en contra: %d\n", sp_aux.statistics_eights_ge);
               break;

      case 3:  printf("La etapa actual es Cuartos de Final\n");
               printf("Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
               printf("Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
               break;
      
      case 4:  printf("La etapa actual es Semifinal\n");
               printf("Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
               printf("Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
               break;

      case 5:  printf("La etapa actual es Final\n");
               printf("Goles a favor: %d\n", sp_aux.statistics_final_gf);
               printf("Goles en contra: %d\n", sp_aux.statistics_final_ge);
               break;
   }
   printf("Los puntos son %d\n", mostrar_points(t));
   printf("La fecha es %s\n", mostrar_fecha(t));
}


void search_for_country(listateam list, char c[]){

   int contador = 0, enter;
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
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void ordenate_recursive(listateam list, team auxiliar[], int i, int cont, int datos_input){

   int j, change,points, change_phase, enter;
   char change_country[MAX], change_dt[MAX], change_captain[MAX];

   if(cont == 0){
      strcpy(auxiliar[i].country, mostrar_country(copy_lista(list)));
      strcpy(auxiliar[i].dt, mostrar_dt(copy_lista(list)));
      strcpy(auxiliar[i].captain, mostrar_captain(copy_lista(list)));
      auxiliar[i].group = mostrar_group(copy_lista(list));
      auxiliar[i].points = mostrar_points(copy_lista(list));
      auxiliar[i].phase = mostrar_etapa(copy_lista(list));
   
      for(j = 0; j < datos_input; j++){
         if(auxiliar[j].points < auxiliar[j+1].points){
            strcpy(change_country, auxiliar[j].country);
            strcpy(auxiliar[j].country, auxiliar[j+1].country);
            strcpy(auxiliar[j+1].country, change_country);

            strcpy(change_dt, auxiliar[j].dt);
            strcpy(auxiliar[j].dt, auxiliar[j+1].dt);
            strcpy(auxiliar[j+1].dt, change_dt);

            strcpy(change_captain, auxiliar[j].captain);
            strcpy(auxiliar[j].captain, auxiliar[j+1].captain);
            strcpy(auxiliar[j+1].captain, change_captain);

            change = auxiliar[j].points;
            auxiliar[j].points = auxiliar[j+1].points;
            auxiliar[j+1].points = change;

            change_phase = auxiliar[j].phase;
            auxiliar[j].phase = auxiliar[j+1].phase;
            auxiliar[j+1].phase = change_phase;
         }
      }
   }
   else{
      printf("----------- Imprimiendo paises ordenados por puntos ------------\n\n");
      for(j = 0; j < datos_input; j++){
         printf("\nPais: %s\n", auxiliar[j].country);
         printf("Dt: %s\n", auxiliar[j].dt);
         printf("Capitan: %s\n", auxiliar[j].captain);
         printf("Grupo: %c\n", auxiliar[j].group);
         printf("Puntos: %d\n", auxiliar[j].points);
         switch(auxiliar[i].phase){
            case 1: printf("Fase de grupos\n");
                    break;
            case 2: printf("Octavos de final\n");
                    break;
            case 3: printf("Cuartos de final\n");
                    break;
            case 4: printf("Semifinal\n");
                    break;
            case 5: printf("Final\n");
                    break;
         }
      }
      printf("------------------------------------------\n");
      do{
         printf("Ingrese 1 para continuar...\n");
         scanf("%d", &enter);
      }while(enter != 1);
   } 
}


int function_auxiliar_control_america(char c[]){

   int aux;

   if(strcmp(c, "ARGENTINA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "BRASIL") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "ECUADOR") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "URUGUAY") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "MEXICO") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "ESTADOS UNIDOS") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "CANADA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "COSTA RICA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }
}


int function_auxiliar_control_europa(char c[]){

   int aux;

   if(strcmp(c, "ALEMANIA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "ESPAÑA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "CROACIA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "BELGICA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "SERBIA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "SUIZA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "FRANCIA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "DINAMARCA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "PAISES BAJOS") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "INGLATERRA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "GALES") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "POLONIA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "PORTUGAL") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }
}


int function_auxiliar_control_africa(char c[]){

   int aux;

   if(strcmp(c, "CAMERUN") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "GHANA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "MARRUECOS") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "SENEGAL") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "TUNEZ") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }
}


int function_auxiliar_control_asia(char c[]){

   int aux;

   if(strcmp(c, "ARABIA SAUDITA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "IRAN") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "COREA DEL SUR") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "JAPON") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

}


int function_auxiliar_control_oceania(char c[]){

   int aux;

   if(strcmp(c, "AUSTRALIA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }
}


int function_control_continent(char c[]){

   int aux;

   if(strcmp(c, "AMERICA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "EUROPA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "AFRICA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "ASIA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }

   if(strcmp(c, "OCEANIA") == 0){
      aux = 0;
      return aux;
   }
   else{
      aux = 1;
   }
}





// FUNCIONES DEL MENU
void load_list(listateam *list, team *t, int *cant, load_country lc[], int total[]){
   
   int i = 0, n, enter;
  
   do{
      printf("¿Cuántas selecciones quiere cargar? Máximo 32\n");
      scanf("%d", &n);
   }while(n > 32 || n < 1);

   while(i < n){

      if(isFull_lista(list) == 0){

         printf("------------- Cargando Equipo -------------\n");
         load_team(t, lc, total);
         insert_lista_team(list, *t);
      }
      else{
         printf("Error! No hay mas espacio para cargar equipos\n");
      }
      i++;
      *cant += 1;
   }
   do{
      printf("Carga completa. Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void show_all_list(listateam list){

   int enter;
   int cant = 0;

   reset_lista(&list);
   while(!isOos_lista(list)){

      printf("\n");
      printf("Datos de la seleccion\n");
      show_team(copy_lista(list));
      printf("----------------------\n");
      cant++;
      
      if(cant == 3){
         cant = 0;
         do{
            printf("Ingrese 1 para continuar...\n");
            scanf("%d", &enter);
         }while(enter != 1);
      }
      forward_lista(&list);
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

   int fase, contador = 0, enter;
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
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void show_best_goalscorer_order(listateam list){

   char surname[MAX], country[MAX];
   int goals, i = 0, j, cant = 0, enter;

   team aux[32];

   for(j = 0; j < 32; j++){
      aux[j].player_goals.goals = 0;
   }

   reset_lista(&list);
   while(!isOos_lista(list)){
      if(mostrar_goals_goalscorer(copy_lista(list)) > 0){
         strcpy(aux[i].country, mostrar_country(copy_lista(list)));
         strcpy(aux[i].player_goals.surname, mostrar_surname_goalscorer(copy_lista(list)));
         aux[i].player_goals.goals = mostrar_goals_goalscorer(copy_lista(list));
         i++;
         cant++;
      }
      forward_lista(&list);
   }

   for(i = 1; i < cant + 1; i++){
      for(j = 0; j < cant - i; j++){
         if(strcmp(aux[j].country, aux[j+1].country) < 0){
            strcpy(country, aux[j].country);
            strcpy(aux[j].country, aux[j+1].country);
            strcpy(aux[j+1].country, country);
         }
      }
   }

   for(i = 0; i < cant; i++){
      printf("El pais del goleador es: %s\n", aux[i].country);
      printf("El goleador es: %s\n", aux[i].player_goals.surname);
      printf("Hizo %d goles\n", aux[i].player_goals.goals);
   }

   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void recursive(listateam list, team auxiliar[], int i, int cont, int datos_input){

   if(isOos_lista(list)){
      cont = 1;
      ordenate_recursive(list, auxiliar, i, cont, datos_input);
   }
   else{
      auxiliar[i].points = mostrar_points(copy_lista(list));
      ordenate_recursive(list, auxiliar, i, cont, datos_input);
      datos_input++;
      i++;
      forward_lista(&list);
      recursive(list, auxiliar, i, cont, datos_input);
   }
}


void change_points(listateam *list, team *t){

   char c[MAX];
   int aux, j, contador = 0, points, pj, pg, pe, etapa, enter;

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

   reset_lista(list);
   while(!isOos_lista(*list)){
      if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
         etapa = mostrar_etapa(copy_lista(*list));
         contador += 1;
      }
      forward_lista(list);
   }

   if(contador == 0){
      printf("\n|||||||||||||||||||||||||| ALERTA |||||||||||||||||||||||||||||||\n");
      printf("Aún no hay datos para el pais %s, registrelo y luego reintente\n", c);
      printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n");
   }
   else{
      switch(etapa){
         case 1: do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Fase de Grupos\n");
                     scanf("%d", &pj);
                  }while(pj > 3 || pj < 0);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  points = 3*pg + pe;
                  break;

         case 2:  do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Octavos de Final\n");
                     scanf("%d", &pj);
                  }while(pj > 4 || pj < 3);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  points = 3*pg + pe;
                  break;

         case 3:  do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Cuartos de Final\n");
                     scanf("%d", &pj);
                  }while(pj > 5 || pj < 4);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  points = 3*pg + pe;
                  break;

         case 4: do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Semifinal\n");
                     scanf("%d", &pj);
                  }while(pj > 6 || pj < 5);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  points = 3*pg + pe;
                  break;

         case 5:  do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Octavos\n");
                     scanf("%d", &pj);
                  }while(pj > 7 || pj < 6);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  points = 3*pg + pe;
                  break;
      }
      reset_lista(list);
      while(!isOos_lista(*list)){
         if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
            *t = copy_lista(*list);
            suppress_lista_team(list);
            modifica_jugados(t, pj);
            modifica_empatados(t, pe);
            modifica_ganados(t, pg);
            modifica_points(t, points);
            insert_lista_team(list, *t);
         }
         forward_lista(list);
      }
   }
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void delete_team_for_country(listateam *list, char c[], load_country lc[]){

   team t;
   int contador = 0, enter, i;
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
               fprintf(loadDeleted, "\n\n");
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
            printf("Se ha borrado correctamente el pais\n");
         }
         else{
            forward_lista(list);
         }
      }

      for( i = 0; i < 32; i++){
         if(strcmp(c, lc[i].name) == 0){
            lc[i].exists = 0;
         }
      }
   }
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void show_best_goalscorer(listateam list){

   char surname[MAX], country[MAX];
   int goals, enter;

   reset_lista(&list);
   while(!isOos_lista(list)){
      if(mostrar_goals_goalscorer(copy_lista(list)) > 0){
         strcpy(country, mostrar_country(copy_lista(list)));
         strcpy(surname, mostrar_surname_goalscorer(copy_lista(list)));
         goals = mostrar_goals_goalscorer(copy_lista(list));
         printf("El pais del goleador es: %s\n", country);
         printf("El goleador es: %s\n", surname);
         printf("Hizo %d goles\n", goals);
      }
      forward_lista(&list);
   }

   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void change_phase(listateam *list, team *t){

   char c[MAX];
   int aux, j, contador = 0, etapa, new_etapa, gf, ge, points, enter;
   statistics_phase sp_aux;

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


   reset_lista(list);
   while(!isOos_lista(*list)){
      if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
         etapa = mostrar_etapa(copy_lista(*list));
         points = mostrar_points(copy_lista(*list));
         sp_aux = mostrar_statistics_group(copy_lista(*list));
         contador += 1;
      }
      forward_lista(list);
   }

   if(contador == 0){
      printf("Aún no hay datos para el pais %s, registrelo y luego reintente\n", c);
   }
   else{
      switch(etapa){
         case 1:  do{
                     printf("El equipo esta en Fase de Grupos. Ahora el equipo pasará a Octavos de Final. Ingrese 2\n");
                     scanf("%d", &new_etapa);
                  }while(new_etapa != 2);
                  gf = sp_aux.statistics_group_gf;
                  ge = sp_aux.statistics_group_ge;
                  break;

         case 2:  do{
                     printf("El equipo esta en Octavos de Final. Ahora el equipo pasará a Cuartos de Final. Ingrese 3\n");
                     scanf("%d", &new_etapa);
                  }while(new_etapa != 3);
                  gf = sp_aux.statistics_eights_gf;
                  ge = sp_aux.statistics_eights_ge;
                  break;

         case 3:  do{
                     printf("El equipo esta en Cuartos de Final. Ahora el equipo pasará a Semifinales. Ingrese 4\n");
                     scanf("%d", &new_etapa);
                  }while(new_etapa != 4);
                  gf = sp_aux.statistics_rooms_gf;
                  ge = sp_aux.statistics_rooms_ge;
                  break;

         case 4:  do{
                     printf("El equipo esta en Semifinal. Ahora el equipo pasará a la Final. Ingrese 5\n");
                     scanf("%d", &new_etapa);
                  }while(new_etapa != 5);
                  gf = sp_aux.statistics_final_gf;
                  ge = sp_aux.statistics_final_ge;
                  break;
      }
      reset_lista(list);
      while(!isOos_lista(*list)){
         if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
            if(etapa == 1){
               *t = copy_lista(*list);
               suppress_lista_team(list);
               modifica_etapa(t, new_etapa);
               modifica_eights(t, gf, ge, points);
               insert_lista_team(list, *t);
            }
            if(etapa == 2){
               *t = copy_lista(*list);
               suppress_lista_team(list);
               modifica_etapa(t, new_etapa);
               modifica_rooms(t, gf, ge, points);
               insert_lista_team(list, *t);
            }
            if(etapa == 3){
               *t = copy_lista(*list);
               suppress_lista_team(list);
               modifica_etapa(t, new_etapa);
               modifica_semifinal(t, gf, ge, points);
               insert_lista_team(list, *t);
            }
            if(etapa == 4){
               *t = copy_lista(*list);
               suppress_lista_team(list);
               modifica_etapa(t, new_etapa);
               modifica_final(t, gf, ge, points);
               insert_lista_team(list, *t);
            }
         }
         forward_lista(list);
      }
   }
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void preload(listateam *list, load_country lc[], int total[]){

   char country[MAX], dt[MAX], captain[MAX], group;
   int p, enter;
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
         carga_fecha(&t);
         insert_lista_team(list, t);
         load_aux_country(lc, country, total);
      }
      printf("Se ha realizado correctamente la carga de los datos\n");
   }
   fclose(preLoad);
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void show_games(listateam list){

   char c[MAX];
   int aux, mj, mg, me, j, cont = 0, enter;

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

   reset_lista(&list);
   while(!isOos_lista(list)){
      if(strcmp(c, mostrar_country(copy_lista(list))) == 0){
         cont += 1;
      }
      forward_lista(&list);
   }

   reset_lista(&list);
   if(cont == 0){
      printf("No hay coincidencias encontradas para la seleccion indicada\n");
   }
   else{
      while(!isOos_lista(list)){
         if(strcmp(c, mostrar_country(copy_lista(list))) == 0){
             mj = mostrar_jugados(copy_lista(list)); 
             printf("Partidos jugados %d\n", mj);
             me = mostrar_empatados(copy_lista(list)); 
             printf("Partidos empatados %d\n", me);
             mg = mostrar_ganados(copy_lista(list));
             printf("Partidos ganados %d\n", mg);
             aux = mj - (mg + me);
             printf("El equipo perdio %d partidos\n", aux);
         }
         forward_lista(&list);
      }
   }
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void load_file_for_continet(listateam list){

   int aux, j, contador = 0, enter;
   int puntos_america = 0, puntos_europa = 0, puntos_africa = 0, puntos_asia = 0, puntos_oceania = 0;
   char c[MAX];

   do{
      printf("Ingrese el continente que desea filtrar\n");
      scanf("%s", c);
      for (j = 0; c[j]!= '\0'; j++){
         c[j] = toupper(c[j]);
      }
      aux = function_control_continent(c);
   }while(aux != 0);

   reset_lista(&list);
   while(!isOos_lista(list)){

      if(strcmp(c, "AMERICA") == 0){
         aux = function_auxiliar_control_america(c);
         if(aux != 0){
            contador += 1;
         }
      }
      
      if(strcmp(c, "EUROPA") == 0){
         aux = function_auxiliar_control_europa(c);
         if(aux != 0){
            contador += 1;
         }
      }

      if(strcmp(c, "AFRICA") == 0){
         aux = function_auxiliar_control_africa(c);
         if(aux != 0){
            contador += 1;
         }
      }

      if(strcmp(c, "ASIA") == 0){
         aux = function_auxiliar_control_asia(c);
         if(aux != 0){
            contador += 1;
         }
      }

      if(strcmp(c, "OCEANIA") == 0){
         aux = function_auxiliar_control_oceania(c);
         if(aux != 0){
            contador += 1;
         }
      }
      forward_lista(&list);
   }
   if(contador == 0){
      printf("No hay selecciones cargadas pertenecientes al continente %s\n", c);
   }
   else{
      statistics_phase sp_aux;
      FILE *fp;
      fp = fopen("Continent.txt", "a+");

      if(fp == NULL){
         printf("Error al acceder al archivo\n");
         exit(1);
      }
      else{
         reset_lista(&list);
         while(!isOos_lista(list)){
            
            if(strcmp(c, "AMERICA") == 0){
               if(strcmp("ARGENTINA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_america = puntos_america + mostrar_points(copy_lista(list));
               }

               if(strcmp("BRASIL", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_america = puntos_america + mostrar_points(copy_lista(list));
               }

               if(strcmp("URUGUAY", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_america = puntos_america + mostrar_points(copy_lista(list));
               }

               if(strcmp("ECUADOR", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_america = puntos_america + mostrar_points(copy_lista(list));
               }

               if(strcmp("MEXICO", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_america = puntos_america + mostrar_points(copy_lista(list));
               }

               if(strcmp("ESTADOS UNIDOS", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_america = puntos_america + mostrar_points(copy_lista(list));
               }

               if(strcmp("CANADA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_america = puntos_america + mostrar_points(copy_lista(list));
               }

               if(strcmp("COSTA RICA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_america = puntos_america + mostrar_points(copy_lista(list));
               }
            }

            if(strcmp(c, "EUROPA") == 0){
               if(strcmp("ALEMANIA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("ESPANA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("CROACIA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("BELGICA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_america = puntos_america + mostrar_points(copy_lista(list));
               }

               if(strcmp("SERBIA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("SUIZA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("FRANCIA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("DINAMARCA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("PAISES BAJOS", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("INGLATERRA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("GALES", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("POLONIA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }

               if(strcmp("PORTUGAL", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_europa = puntos_europa + mostrar_points(copy_lista(list));
               }
               
               fprintf(fp, "Puntaje del continente europeo: %d\n", puntos_europa);
            }

            if(strcmp(c, "AFRICA") == 0){
               if(strcmp("CAMERUN", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_africa = puntos_africa + mostrar_points(copy_lista(list));
               }

               if(strcmp("GHANA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_africa = puntos_africa + mostrar_points(copy_lista(list));
               }

               if(strcmp("MARRUECOS", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_africa = puntos_africa + mostrar_points(copy_lista(list));
               }
            
               if(strcmp("SENEGAL", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_africa = puntos_africa + mostrar_points(copy_lista(list));
               }
            
               if(strcmp("TUNEZ", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_africa = puntos_africa + mostrar_points(copy_lista(list));
               }
            
               fprintf(fp, "Puntaje del continente africano: %d\n", puntos_africa);
            }
         
            if(strcmp(c, "ASIA") == 0){
               if(strcmp("ARABIA SAUDITA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_asia = puntos_asia + mostrar_points(copy_lista(list));
               }

               if(strcmp("IRAN", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_asia = puntos_asia + mostrar_points(copy_lista(list));
               }
            
               if(strcmp("COREA DEL SUR", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_asia = puntos_asia + mostrar_points(copy_lista(list));
               }
            
               if(strcmp("JAPON", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  
                  puntos_asia = puntos_asia + mostrar_points(copy_lista(list));
               }
            
               fprintf(fp, "Puntaje del continente asiatico: %d\n", puntos_asia);
            }

            if(strcmp(c, "OCEANIA") == 0){
               if(strcmp("AUSTRALIA", mostrar_country(copy_lista(list))) == 0){
                  
                  fprintf(fp, "Pais: %s\n", mostrar_country(copy_lista(list)));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Fase de Grupos\n");
                              break;
                     
                     case 2:  fprintf(fp, "Octavos de Final\n");
                              break;

                     case 3:  fprintf(fp, "Cuartos de Final\n");
                              break;

                     case 4:  fprintf(fp, "Semifinal\n");
                              break;

                     case 5:  fprintf(fp, "Final\n");
                              break; 
                  }

                  sp_aux = mostrar_statistics_group(copy_lista(list));
                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_group_gf);
                              break;
                     
                     case 2:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_eights_gf);
                              break;

                     case 3:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_rooms_gf);
                              break;

                     case 4:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_semifinal_gf);
                              break;

                     case 5:  fprintf(fp, "Goles a favor: %d\n", sp_aux.statistics_final_gf);
                              break; 
                  }

                  switch(mostrar_etapa(copy_lista(list))){
                     case 1:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_group_ge);
                              break;
                     
                     case 2:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_eights_ge);
                              break;

                     case 3:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_rooms_ge);
                              break;

                     case 4:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_semifinal_ge);
                              break;

                     case 5:  fprintf(fp, "Goles en contra: %d\n", sp_aux.statistics_final_ge);
                              break; 
                  }
                  puntos_oceania = mostrar_points(copy_lista(list));
                  fprintf(fp, "Puntaje del continente asiatico: %d\n", puntos_oceania);
               }
            }
            
            forward_lista(&list);
         }
         if(strcmp(c, "AMERICA") == 0){
            fprintf(fp, "Puntaje del continente americano: %d\n", puntos_america);
         }
         if(strcmp(c, "EUROPA") == 0){
            fprintf(fp, "Puntaje del continente europeo: %d\n", puntos_europa);
         }
         if(strcmp(c, "AFRICA") == 0){
            fprintf(fp, "Puntaje del continente africano: %d\n", puntos_africa);
         }
         if(strcmp(c, "ASIA") == 0){
            fprintf(fp, "Puntaje del continente asiatico: %d\n", puntos_asia);
         }
         if(strcmp(c, "OCEANIA") == 0){
            fprintf(fp, "Puntaje del continente oceanico: %d\n", puntos_oceania);
         }
         fclose(fp);
      }
   }
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void load_players(players_of_team pt[], int *cantidad){

   char country[MAX], name[MAX];
   int aux, j, i, n, k, l, enter;
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
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void load_games(listateam *list, team *t){

   char c[MAX];
   int j, aux, contador = 0, pj, pg, pe, etapa, enter;

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

   reset_lista(list);
   while(!isOos_lista(*list)){
      if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
         etapa = mostrar_etapa(copy_lista(*list));
         contador += 1;
      }
      forward_lista(list);
   }

   if(contador == 0){
      printf("\n|||||||||||||||||||||||||| ALERTA |||||||||||||||||||||||||||||||\n");
      printf("Aún no hay datos para el pais %s, registrelo y luego reintente\n", c);
      printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n");
   }
   else{
      switch(etapa){
         case 1:  do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Fase de Grupos\n");
                     scanf("%d", &pj);
                  }while(pj > 3 || pj < 0);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  break;

         case 2:  do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Octavos de Final\n");
                     scanf("%d", &pj);
                  }while(pj > 4 || pj < 3);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  break;

         case 3:  do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Cuartos de Final\n");
                     scanf("%d", &pj);
                  }while(pj > 5 || pj < 4);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  break;

         case 4:  do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Semifinal\n");
                     scanf("%d", &pj);
                  }while(pj > 6 || pj < 5);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  break;

         case 5:  do{
                     printf("Ingrese la cantidad de partidos jugados.\n");
                     printf("Recuerde que la seleccion esta en Octavos\n");
                     scanf("%d", &pj);
                  }while(pj > 7 || pj < 6);
                  do{
                     printf("Ingrese la cantidad de partidos ganados\n");
                     scanf("%d", &pg);
                  }while(pg > pj || pg < 0);
                  do{
                     printf("Ingrese la cantidad de partidos empatados\n");
                     scanf("%d", &pe);
                  }while(pj < pg + pe || pe < 0);
                  break;
      }
      reset_lista(list);
      while(!isOos_lista(*list)){
         if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
            *t = copy_lista(*list);
            suppress_lista_team(list);
            carga_jugados(t, pj);
            carga_empatados(t, pe);
            carga_ganados(t, pg);
            insert_lista_team(list, *t);
         }
         forward_lista(list);
      }
   }
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void load_goalscorer(listateam *list, team *t){

   char c[MAX], surname[MAX];
   int aux, j, goals, contador = 0, enter;

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

   reset_lista(list);
   while(!isOos_lista(*list)){
      if (strcmp(c, mostrar_country(copy_lista(*list))) == 0){
         contador += 1;
      }
      forward_lista(list);
   }

   if(contador == 0){
      printf("Aún no hay datos para el pais %s, registrelo y luego reintente\n", c);
      do{
         printf("Ingrese 1 para continuar...\n");
         scanf("%d", &enter);
      }while(enter != 1);
   }
   else{
      printf("Ingrese el apellido del goleador\n");
      scanf(" %[^\n]", surname);
      for (j = 0; surname[j]!= '\0'; j++){
         surname[j] = toupper(surname[j]);
      }
      do{
         printf("Ingrese los goles convertidos\n");
         scanf("%d", &goals);
      }while(goals > 15 || goals < 1);
      
      reset_lista(list);
      while(!isOos_lista(*list)){
         if (strcmp(c, mostrar_country(copy_lista(*list))) == 0){
            *t = copy_lista(*list);
            suppress_lista_team(list);
            carga_goalscorer(t, goals, surname);
            insert_lista_team(list, *t);
         }
         forward_lista(list);
      }
      do{
         printf("Ingrese 1 para continuar...\n");
         scanf("%d", &enter);
      }while(enter != 1);
   }
}


void show_dt_players(listateam list, players_of_team pt[], char c[], int cantidad){

   int i, aux = 0, j, enter, otro_aux = 0;
   for (i = 0; i < cantidad; i++){
      if(strcmp(pt[i].country, c) == 0){
         aux = 1;
      }
   }

   reset_lista(&list);
   while(!isOos_lista(list)){
      if(strcmp(c, mostrar_country(copy_lista(list))) == 0){
         otro_aux = 1;
      }
      
      forward_lista(&list);  
   }

   if(aux == 0 || otro_aux == 0){
      printf("No ha cargado un plantel para la seleccion %s\n", c);
      do{
         printf("Ingrese 1 para continuar...\n");
         scanf("%d", &enter);
      }while(enter != 1);
   }
   else{
      reset_lista(&list);
      while(!isOos_lista(list)){

         for(i = 0; i < cantidad; i++){
            if(strcmp(pt[i].country, c) == 0 && strcmp(pt[i].country, mostrar_country(copy_lista(list))) == 0){

               printf("El DT es %s\n", mostrar_dt(copy_lista(list)));
               printf("El capitan es %s\n", mostrar_captain(copy_lista(list)));

               for(j = 0; j < 11; j++){

                  printf("Apellido: %15s\t", pt[i].p[j].name);
                  switch(pt[i].p[j].position){
                     case 1: printf("Arquero\t\t\t");
                             break;
                     case 2: printf("Primer central\t\t");
                             break;
                     case 3: printf("Lateral izquierdo\t");
                             break;
                     case 4: printf("Lateral derecho\t\t");
                             break;
                     case 5: printf("Mediocentro\t\t");
                             break;
                     case 6: printf("Segundo central\t\t");
                             break;
                     case 7: printf("Carrilero izquierdo\t");
                             break;
                     case 8: printf("Carrilero derecho\t");
                             break;
                     case 9: printf("Delantero centro\t");
                             break;
                     case 10: printf("Enganche\t\t");
                              break;
                     case 11: printf("Segundo delantero\t");
                              break;
                  }
                  printf("Dorsal %2d\n", pt[i].p[j].number_shirt);
               }
            }
         }
         forward_lista(&list);
      }
      do{
         printf("Ingrese 1 para continuar...\n");
         scanf("%d", &enter);
      }while(enter != 1);
   }
   
}


void load_phase(listateam *list, team *t){

   char c[MAX];
   int aux, j, contador = 0, etapa, gf, ge, enter;

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

   reset_lista(list);
   while(!isOos_lista(*list)){
      if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
         etapa = mostrar_etapa(copy_lista(*list));
         contador += 1;
      }
      forward_lista(list);
   }

   if(contador == 0){
      printf("Aún no hay datos para el pais %s, registrelo y luego reintente\n", c);
   }
   else{
      switch(etapa){
         case 1:  do{
                     printf("Ingrese los goles a favor de la Fase de Grupos\n");
                     scanf("%d", &gf);
                  }while(gf < 0 || gf > 30);
                  do{
                     printf("Ingrese los goles en contra de la Fase de Grupos\n");
                     scanf("%d", &ge);
                  }while(ge < 0 || ge > 30);
                  break;

         case 2:  do{
                     printf("Ingrese los goles a favor de los Octavos de Final\n");
                     scanf("%d", &gf);
                  }while(gf < 0 || gf > 30);
                  do{
                     printf("Ingrese los goles en contra de los Octavos de Final\n");
                     scanf("%d", &ge);
                  }while(ge < 0 || ge > 30);
                  break;

         case 3:  do{
                     printf("Ingrese los goles a favor de los Cuartos de Final\n");
                     scanf("%d", &gf);
                  }while(gf < 0 || gf > 30);
                  do{
                     printf("Ingrese los goles en contra de los Cuartos de Final\n");
                     scanf("%d", &ge);
                  }while(ge < 0 || ge > 30);
                  break;

         case 4:  do{
                     printf("Ingrese los goles a favor de la Semifinal\n");
                     scanf("%d", &gf);
                  }while(gf < 0 || gf > 30);
                  do{
                     printf("Ingrese los goles en contra de la Semifinal\n");
                     scanf("%d", &ge);
                  }while(ge < 0 || ge > 30);
                  break;

         case 5:  do{
                     printf("Ingrese los goles a favor de la Final\n");
                     scanf("%d", &gf);
                  }while(gf < 0 || gf > 30);
                  do{
                     printf("Ingrese los goles en contra de la Final\n");
                     scanf("%d", &ge);
                  }while(ge < 0 || ge > 30);
                  break;  
      }
      reset_lista(list);
      while(!isOos_lista(*list)){ 
         if(strcmp(c, mostrar_country(copy_lista(*list))) == 0){
            if(etapa == 1){
               *t = copy_lista(*list);
               suppress_lista_team(list);
               carga_phase_group(t, gf, ge);
               insert_lista_team(list, *t);
            }
            if(etapa == 2){
               *t = copy_lista(*list);
               suppress_lista_team(list);
               carga_eights(t, gf, ge);
               insert_lista_team(list, *t);
            }
            if(etapa == 3){
               *t = copy_lista(*list);
               suppress_lista_team(list);
               carga_rooms(t, gf, ge);
               insert_lista_team(list, *t);
            }
            if(etapa == 4){
               *t = copy_lista(*list);
               suppress_lista_team(list);
               carga_semifinal(t, gf, ge);
               insert_lista_team(list, *t);
            }
            if(etapa == 5){
               *t = copy_lista(*list);
               suppress_lista_team(list);
               carga_final(t, gf, ge);
               insert_lista_team(list, *t);
            }
         }
         forward_lista(list);
      }
   }
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}


void preload_players(listateam *list, players_of_team pt[], int *cantidad){

   char country[MAX], dt[MAX], captain[MAX];
   int enter, i = 0, j = 0;

   FILE *preLoad;
   preLoad = fopen("PreloadPlayers.txt", "r+");

   if(preLoad == NULL){
      printf("No se pudo acceder al archivo\n");
      exit(1);
   }
   else{
      for(i = 0; !feof(preLoad); i++){
         fscanf(preLoad, "%[^\n]\n", pt[i].country);
         for(j = 0; j < 11; j++){
            fscanf(preLoad, "%[^\n]\n", pt[i].p[j].name);
            fscanf(preLoad, "%d\n", &pt[i].p[j].position);
            fscanf(preLoad, "%d\n", &pt[i].p[j].number_shirt);
         }
         *cantidad += 1;
      }
      
      printf("Se ha realizado correctamente la carga de los datos\n");
   }
   fclose(preLoad);
   do{
      printf("Ingrese 1 para continuar...\n");
      scanf("%d", &enter);
   }while(enter != 1);
}