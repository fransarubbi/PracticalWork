#include <stdio.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#define MAX 50


typedef struct{    // goleador
    char surname[MAX];
    int goals;
} goalscorer;

typedef struct{
    int statistics_group_gf;   //goles a favor, goles en contra, puntaje
    int statistics_group_ge;
    int statistics_group_p;
    int statistics_eights_gf;
    int statistics_eights_ge;
    int statistics_eights_p;
    int statistics_rooms_gf;
    int statistics_rooms_ge;
    int statistics_rooms_p;
    int statistics_semifinal_gf;
    int statistics_semifinal_ge;
    int statistics_semifinal_p;
    int statistics_final_gf;
    int statistics_final_ge;
    int statistics_final_p;
} statistics_phase;

typedef struct{   //partidos jugados, ganados y empatados
    int played;
    int win;
    int draw;
} games;

typedef struct{  //struct de equipo
    char country[MAX];
    char dt[MAX];
    char captain[MAX];
    char group;
    int points;
    int phase;
    char str_hour[100];
    goalscorer player_goals;
    statistics_phase sp;
    games g;
} team;

//Inicializador
void init_team(team *t){
    (*t).points = 0;
    (*t).phase = 0;
    (*t).player_goals.goals = 0;
    (*t).sp.statistics_group_gf = 0;
    (*t).sp.statistics_group_ge = 0;
    (*t).sp.statistics_group_p= 0;
    (*t).sp.statistics_eights_gf = 0;
    (*t).sp.statistics_eights_ge = 0;
    (*t).sp.statistics_eights_p = 0;
    (*t).sp.statistics_rooms_gf = 0;
    (*t).sp.statistics_rooms_ge = 0;
    (*t).sp.statistics_rooms_p = 0;
    (*t).sp.statistics_semifinal_gf = 0;
    (*t).sp.statistics_semifinal_ge = 0;
    (*t).sp.statistics_semifinal_p = 0;
    (*t).sp.statistics_final_gf = 0;
    (*t).sp.statistics_final_ge = 0;
    (*t).sp.statistics_final_p = 0;
    (*t).g.played = 0;
    (*t).g.win = 0;
    (*t).g.draw = 0;
}


//Funciones de carga
void carga_fecha(team *t){
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strcpy((*t).str_hour, asctime(info));
}

void carga_country(team *t, char c[]){
    strcpy((*t).country, c);
}

void carga_dt(team *t, char tecnico[]){
    strcpy((*t).dt, tecnico);
}

void carga_captain(team *t, char capitan[]){
    strcpy((*t).captain, capitan);
}

void carga_group(team *t, char g){
    (*t).group = g;
}

void carga_points(team *t, int p){
    (*t).points = p;
}

void carga_goalscorer(team *t, int goles, char apellido[]){
    (*t).player_goals.goals = goles;
    strcpy((*t).player_goals.surname, apellido);
}

void carga_phase(team *t, int f){
    (*t).phase = f;
}

void carga_phase_group(team *t, int gf, int ge){
    (*t).sp.statistics_group_gf = gf;
    (*t).sp.statistics_group_ge = ge;
}

void carga_eights(team *t, int gf, int ge){
    (*t).sp.statistics_eights_gf = gf;
    (*t).sp.statistics_eights_ge = ge;
}

void carga_rooms(team *t, int gf, int ge){
    (*t).sp.statistics_rooms_gf = gf;
    (*t).sp.statistics_rooms_ge = ge;
}

void carga_semifinal(team *t, int gf, int ge){
    (*t).sp.statistics_semifinal_gf = gf;
    (*t).sp.statistics_semifinal_ge = ge;
}

void carga_final(team *t, int gf, int ge){
    (*t).sp.statistics_final_gf = gf;
    (*t).sp.statistics_final_ge = ge;
}

void carga_jugados(team *t, int j){
    (*t).g.played = j;
}

void carga_ganados(team *t, int g){
    (*t).g.win = g;
}

void carga_empatados(team *t, int e){
    (*t).g.draw = e;
}



//Funciones modificar
void modifica_points(team *t, int p){
    (*t).points = p;
}

void modifica_goalscorer(team *t, int goles, char apellido[]){
    (*t).player_goals.goals = goles;
    strcpy((*t).player_goals.surname, apellido);
}

void modifica_group(team *t, int gf, int ge, int p){
    (*t).sp.statistics_group_gf = gf;
    (*t).sp.statistics_group_ge = ge;
    (*t).sp.statistics_group_p = p;
}

void modifica_eights(team *t, int gf, int ge, int p){
    (*t).sp.statistics_eights_gf = gf;
    (*t).sp.statistics_eights_ge = ge;
    (*t).sp.statistics_eights_p = p;
}

void modifica_rooms(team *t, int gf, int ge, int p){
    (*t).sp.statistics_rooms_gf = gf;
    (*t).sp.statistics_rooms_ge = ge;
    (*t).sp.statistics_rooms_p = p;
}

void modifica_semifinal(team *t, int gf, int ge, int p){
    (*t).sp.statistics_semifinal_gf = gf;
    (*t).sp.statistics_semifinal_ge = ge;
    (*t).sp.statistics_semifinal_p = p;
}

void modifica_final(team *t, int gf, int ge, int p){
    (*t).sp.statistics_final_gf = gf;
    (*t).sp.statistics_final_ge = ge;
    (*t).sp.statistics_final_p = p;
}

void modifica_etapa(team *t, int ph){
    (*t).phase = ph;
}

void modifica_jugados(team *t, int j){
    (*t).g.played = j;
}

void modifica_ganados(team *t, int g){
    (*t).g.win = g;
}

void modifica_empatados(team *t, int e){
    (*t).g.draw = e;
}




//Funciones de muestra
char* mostrar_fecha(team t){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(t.str_hour));
    strcpy(aux, t.str_hour);
    return aux;
}


char* mostrar_country(team t){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(t.country));
    strcpy(aux, t.country);
    return aux;
}

char* mostrar_dt(team t){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(t.dt));
    strcpy(aux, t.dt);
    return aux;
}

char* mostrar_captain(team t){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(t.captain));
    strcpy(aux, t.captain);
    return aux;
}

char mostrar_group(team t){
   return t.group;
}

int mostrar_points(team t){
    return t.points;
}

int mostrar_goals_goalscorer(team t){
    return t.player_goals.goals;
}

char* mostrar_surname_goalscorer(team t){
    char *aux;
    aux = (char*)malloc(sizeof(char)*strlen(t.player_goals.surname));
    strcpy(aux, t.player_goals.surname);
    return aux;
}


int mostrar_etapa(team t){
    return t.phase;   
}

int mostrar_jugados(team t){
    return t.g.played;
}

int mostrar_ganados(team t){
    return (t).g.win;
}

int mostrar_empatados(team t){
    return t.g.draw;
}

statistics_phase mostrar_statistics_group(team t){
    return t.sp;
}