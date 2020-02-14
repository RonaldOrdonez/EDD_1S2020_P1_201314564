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
void iniciarMenu();
void windowEditor();
void windowOpenFile();
void windowRecentFiles();
void windowReports();
void exit();

//VARIABLES GLOBALES A UTILIZAR
WINDOW *ventanaInicio;
//char console_text[];

//###################################################################################
//################# VENTANA QUE MUESTRA EL MENU DE INICIO ###########################
//###################################################################################
void iniciarMenu()
{
    clear();
    int x=22; //COORDENADA EN X PARA CENTRAR EL MENU
    //ENCABEZADO Y OPCIONES DEL MENU
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
    refresh();
    int inputkey=getch(); //OBTIENE LA TECLA INGRESADA POR EL USUARIO
    //OPCION 1, MUESTRA EL MENU CON EL ENCABEZADO Y LAS OPCIONES PRINCIPALES
    if(inputkey=='1'){
        windowEditor();
    }
    //OPCION 2, MUESTRA LA VENTA PARA ABRIR UN ARCHIVO
    else if(inputkey=='2'){
        //windowOpenFile(); el qeu va aqui
        windowReports(); //solo para las pruebas

    }
    //OPCION 3, ABRE LA LISTA DE LOS ARCHIVOS RECIENTES
    else if(inputkey=='3'){
        windowRecentFiles();
    }
    //OPCION 4, SE SALE DEL MENU
    else if(inputkey=='4'){
        exit();
    }/*
    else if(inputkey==KEY_F(2)){
         mvprintw(18,x,"PRESIONO F2");  
         refresh();
         iniciarMenu();
    }*/
    else{
        iniciarMenu();
    }
}

//###################################################################################
//######################## VENTANA EDITOR DEL TEXTO #################################
//###################################################################################
void windowEditor(){    
    int y = 22; //posicion en y para colocar el inicio de los nombres        
    clear(); //limpia la pantalla
    mvprintw(21,2,"Presione una de las combinaciones para activar laas funciones mostradas.");
    mvprintw(y,2,"FN+F2 Buscar y Reemplazar");
    mvprintw(y,35,"FN+F3 Reportes");
    mvprintw(y,58,"FN+F4 Guardar");
    mvprintw(23,2,"FN+F5 Deshacer la ultima palabra");
    mvprintw(23,35,"FN+F6 Rehacer la ultima palabra");
    mvprintw(0,0,"");
    //getch();
    refresh(); //utiliza un refresh para actualizar la pantalla y que se muestren las letras    
    //int i=0;
    bool flag=true;
    int key;
    int fila=0; //inicia la fila en 2
    int columna=0; //inicia columna en 2    
    while(flag){        
        key=getch(); //obteniendo el caracter
        //FUNCION PARA BUSCAR Y REEMPLAZAR "F2"
        if(key==KEY_F(2)){
            mvprintw(6,2,"PRESIONO F2");
            refresh();
        }
        //FUNCION PARA REPORTES "F3"
        else if(key==KEY_F(3)){
            mvprintw(6,2,"PRESIONO F3");
            refresh();
        }
        //FUNCION PARA GUARDAR "F4"
        else if(key==KEY_F(4)){
            mvprintw(6,2,"PRESIONO F4");
            refresh();
        }
        //FUNCION PARA DESHACER ULTIMA LETRA "F5"
        else if(key==KEY_F(5)){
            mvprintw(6,2,"PRESIONO F5");
            refresh();
        }
        //FUNCION PARA REHACER ULTIMA LETRA "F6"
        else if(key==KEY_F(6)){
            mvprintw(6,2,"PRESIONO F6");
            refresh();
        }
        //compara que los caracteres esten en un rango valido
        else if((key>=33 && key<=126) || key==164 || key==165 || key==32 || key==9 || key==8 || key==127){            
            //compara la barra espaciadora
            if(key==32){
                mvaddch(fila,columna,key);
                refresh();
                columna++;                
            }
            //compara un tab horizontal
            if(key==9){
                columna=columna+5;                
                mvaddch(fila,columna,32);
                refresh();
                columna++;
            }
            //FUNCION QUE REALIZA CUANDO SE ELIMINA UNA LETRA
            if(key==8 || key==127){
                listaCaracteres->deleteNode();
                columna--;                
                mvaddch(fila,columna+1,32);
                mvaddch(fila,columna+2,32);
                mvaddch(fila,columna,32);
                mvprintw(fila,columna,"");
                refresh();
            }              
            //agrega el caracter a la lista
            else{
            //console_text[i]=key;
            //mvprintw(1,2,console_text);
            listaCaracteres->addNode(key);             
            mvaddch(fila,columna,key);
            refresh();
            columna++;
            //i++; 
            }          
        }
        //compara el salto de linea y un tab vertical
        else if(key==10 || key==11){
            fila++;
            columna=0;
            mvprintw(fila,0,"");
            refresh();
        }     
        //ESC PARA SALIR DE ESTE MODO         
        else if(key==27){
            iniciarMenu();
        }
        else{

        }
    }
    exit();
}

//###################################################################################
//######## VENTANA ABRIR UN ARCHIVO Y MOSTRARLO EN EL EDITOR DE TEXTO ###############
//###################################################################################
void windowOpenFile(){
    exit();

}

//###################################################################################
//########### VENTANA QUE MOSTRARA LOS ARCHIVOS RECIENTES ABIERTOS  #################
//###################################################################################
void windowRecentFiles(){
    exit();
}

//###################################################################################
//##################### VENTANA PARA MOSTRAR REPORTES ###############################
//###################################################################################
void windowReports(){
    clear();    
    mvprintw(2,3,"ARCHIVO GENERADO CON EXITO");
    refresh();
    listaCaracteres->graphList();
    getch();
    iniciarMenu();
}

//###################################################################################
//##################### CERRAR LA VENTANA DE NCURSES ################################
//###################################################################################

void exit(){    
    endwin();
    exit(-1);
}

//####################################################################################
//####################### FUNCION PRINCIPAL "MAIN" ###################################
//####################################################################################
int main()
{
	initscr();			
	raw();				
	keypad(stdscr, TRUE);
	noecho();    
    clear();
    iniciarMenu();    
    return 0;
}