#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ncurses.h>
#include "listaCaracteres.cpp"

using namespace std;

//INSTANCIA DE LAS CLASES A USAR
ListCharacters* listaCaracteres=new ListCharacters();

//DEFINICIO DE LOS METODOS A UTILIZAR DURANTE LA EJECUCION DEL PROGRAMA
void windowEditor();
void windowOpenFile();
void windowRecentFiles();
void windowReports();
void exit();

//VARIABLES GLOBALES A UTILIZAR
WINDOW *ventanaInicio;
char console_text[3000];

//VENTANA QUE MUESTRA EL MENU DE INICIO
void iniciarMenu()
{
    ventanaInicio=initscr();
    clear();
    int x=25;
    mvprintw(2,x,"UNIVERSIDAD DE SAN CARLOS DE GUATEMALA");
    mvprintw(3,x,"FACULTAD DE INGENIERIA");
    mvprintw(4,x,"ESTRUCTURA DE DATOS");
    mvprintw(5,x,"PRACTICA 1");
    mvprintw(6,x,"RONALD GEOVANY ORDONEZ XILOJ");
    mvprintw(7,x,"201314564");
    mvprintw(10,x,"MENU");
    mvprintw(11,x,"1. Crear Archivo");
    mvprintw(12,x,"2. Abrir Archivo");
    mvprintw(13,x,"3. Archivos Recientes");
    mvprintw(14,x,"4. Salir");
    mvprintw(16,x,"Seleccione un numero de opcion(1-4): ");    
    refresh(); //refresh
    int inputkey=getch();
    if(inputkey=='1'){
        windowEditor();
    }
    if(inputkey=='2'){
        windowReports();
    }
    else{
        exit();
    }
}

//VENTANA QUE SERVIRA COMO EDITOR DEL TEXTO
void windowEditor(){    
    int y = 23; //posicion en y para colocar el inicio de los nombres    
    
    clear();
    mvprintw(y,2,"CTRL+W Buscar y Reemplazar");
    mvprintw(y,35,"CTRL+C Reportes");
    mvprintw(y,58,"CTRL+S Guardar");
    mvprintw(1,2,"");
    //getch();
    refresh();
    
    int i=0;
    bool flag=true;
    int key;
    while(flag){
        key=getch();
        if(key>64 && key<123){
            console_text[i]=key;
            listaCaracteres->addNode(key);
            mvprintw(1,2,console_text);
            refresh();
            i++;
        }
        else{
            iniciarMenu();
        }
    }
    exit();
}


//VENTANA PARA ABRIR UN ARCHIVO Y MOSTRARLO EN EL EDITOR DE TEXTO
void windowOpenFIle(){

}

//VENTANA QUE MOSTRARA LOS ARCHIVOS RECIENTES ABIERTOS 
void windowRecentFiles(){

}

//VENTANA PARA MOSTRAR REPORTES()
void windowReports(){
    clear();    
    mvprintw(2,3,"ARCHIVO GENERADO CON EXITO");
    refresh();
    listaCaracteres->graphList();
    getch();
    iniciarMenu();
}

//CERRAR LA VENTANA DE NCURSES
void exit(){    
    endwin();
}

//####################################################################
//#######################MENU PRINCIPAL###############################
//####################################################################
int main()
{
    iniciarMenu();    
    return 0;
}