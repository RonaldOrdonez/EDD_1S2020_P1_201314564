#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ncurses.h>
#include <unistd.h>
#include <limits.h>
#include "listaArchivosRecientes.cpp"
#include "listaCaracteres.cpp"
#include "listaPalabrasBuscadas.cpp"
#include "listaPalabrasReemplazadas.cpp"
#include "pilaCambiosRealizados.cpp"
#include "pilaRevertidos.cpp"
#include "listaAux.cpp"

using namespace std;

//INSTANCIA DE LAS CLASES A USAR
ListCharacters *listaCaracteres = new ListCharacters();
StackChangedMade *pilaCambiosRealizados = new StackChangedMade();
NodeChangesMade *NodoCambios = new NodeChangesMade();
NodeReversed *NodoRevertidos = new NodeReversed();
StackReversed *pilaRevertidos = new StackReversed();
ListRecentFiles *listaArchivosRecientes = new ListRecentFiles();
ListWordsSerched *listaPalabrasBuscas = new ListWordsSerched();
ListWordsReplaced *listaPalabrasReemplazadas = new ListWordsReplaced();
//PARA BUSCAR Y REEMPLAZAR
ListWords *listaDePlabras = new ListWords();
string palabraConcatenada = "";
string palabraABuscar = "";
string palabraAReemplazar = "";

//string cadenaAGuarda

//DEFINICIO DE LOS METODOS A UTILIZAR DURANTE LA EJECUCION DEL PROGRAMA
void iniciarMenu();
void windowEditor();
void windowOpenFile();
void windowRecentFiles();
void windowReports();
void windowSaveFile();
void buscarYReemplazar();
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
    int x = 22; //COORDENADA EN X PARA CENTRAR EL MENU
    //ENCABEZADO Y OPCIONES DEL MENU
    mvprintw(2, x, "UNIVERSIDAD DE SAN CARLOS DE GUATEMALA");
    mvprintw(3, x, "FACULTAD DE INGENIERIA");
    mvprintw(4, x, "ESTRUCTURA DE DATOS");
    mvprintw(5, x, "PRACTICA 1");
    mvprintw(6, x, "RONALD GEOVANY ORDONEZ XILOJ");
    mvprintw(7, x, "201314564");
    mvprintw(10, x, "MENU");
    mvprintw(11, x, "1. Crear Archivo");
    mvprintw(12, x, "2. Abrir Archivo");
    mvprintw(13, x, "3. Archivos Recientes");
    mvprintw(14, x, "4. Salir");
    mvprintw(16, x, "Seleccione un numero de opcion(1-4): ");
    refresh();
    int inputkey = getch(); //OBTIENE LA TECLA INGRESADA POR EL USUARIO
    //OPCION 1, MUESTRA EL MENU CON EL ENCABEZADO Y LAS OPCIONES PRINCIPALES
    if (inputkey == '1')
    {
        windowEditor();
    }
    //OPCION 2, MUESTRA LA VENTA PARA ABRIR UN ARCHIVO
    else if (inputkey == '2')
    {
        //windowOpenFile(); el qeu va aqui
        windowReports(); //solo para las pruebas
    }
    //OPCION 3, ABRE LA LISTA DE LOS ARCHIVOS RECIENTES
    else if (inputkey == '3')
    {
        windowRecentFiles();
    }
    //OPCION 4, SE SALE DEL MENU
    else if (inputkey == '4')
    {
        exit();
    }
    else
    {
        iniciarMenu();
    }
}

//###################################################################################
//######################## VENTANA EDITOR DEL TEXTO #################################
//###################################################################################
void windowEditor()
{
    int y = 22; //posicion en y para colocar el inicio de los nombres
    clear();    //limpia la pantalla
    mvprintw(21, 1, "==============================================================================");
    mvprintw(y, 1, "FN+F2 Buscar y Reemplazar");
    mvprintw(y, 35, "FN+F3 Reportes");
    mvprintw(y, 60, "FN+F4 Guardar");
    mvprintw(23, 1, "FN+F5 Deshacer accion");
    mvprintw(23, 35, "FN+F6 Rehacer accion");
    mvprintw(0, 0, "");
    //getch();
    refresh(); //utiliza un refresh para actualizar la pantalla y que se muestren las letras
    //int i=0;
    bool flag = true;
    int key;
    int fila = 0;    //inicia la fila en 0
    int columna = 0; //inicia columna en 0
    while (flag)
    {
        key = getch(); //obteniendo el caracter

        /*##################################################################################
        *##### FUNCIONES "F" QUE REALIZAN LAS OPERACIONES CON COMBINACION DE TECLAS
        *###################################################################################
        */
        //FUNCION PARA BUSCAR Y REEMPLAZAR "F2"
        if (key == KEY_F(2))
        {
            buscarYReemplazar();
        }
        //FUNCION PARA REPORTES "F3"
        else if (key == KEY_F(3))
        {
            windowReports();
        }
        //FUNCION PARA GUARDAR "F4"
        else if (key == KEY_F(4))
        {
            windowSaveFile();
        }

        //FUNCION PARA DESHACER ULTIMA LETRA "F5", ES UN CTRL+Z
        else if (key == KEY_F(5))
        {
            //limpia la fila 18 x si se quedo escrito
            for (int i = 0; i < 25; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }

            if (listaCaracteres->isEmpty() || pilaCambiosRealizados->isEmpty())
            {
            }
            else
            {
                //elimino de la lista de caracteres
                listaCaracteres->deleteNode();
                //saco el nodo de la pila de cambios realizados
                NodoCambios = pilaCambiosRealizados->pop();
                string word_serched = NodoCambios->word_serched;
                string word_replaced = NodoCambios->word_replaced;
                char word = NodoCambios->word;
                int positionCol = NodoCambios->positionCol;
                int positionRow = NodoCambios->positionRow;

                //INSERTO EL MISMO NODO EN LA OTRA PILA
                pilaRevertidos->push(word_serched, word_replaced, "Revertido", word, positionCol, positionRow);
                mvaddch(fila, columna - 1, 32);
                mvprintw(fila, columna - 1, "");
                refresh();
                columna--;
            }
        }

        //FUNCION PARA REHACER ULTIMA LETRA "F6", ES UN CTRL+Y
        else if (key == KEY_F(6))
        {
            //limpia la fila 18 x si se quedo escrito
            for (int i = 0; i < 25; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            if (pilaRevertidos->isEmpty())
            {
            }
            else
            {
                //hacer un pop de la pila de revertidos y asignarlo a un nodo de tipo revetidos
                NodoRevertidos = pilaRevertidos->pop();
                //tomar los datos del nodo en variables
                string word_serched = NodoRevertidos->word_serched;
                string word_replaced = NodoRevertidos->word_replaced;
                char word = NodoRevertidos->word;
                int positionCol = NodoRevertidos->positionCol;
                int positionRow = NodoRevertidos->positionRow;
                //insertar los datos de la pila de revertidos en la pila de cambios realizados
                pilaCambiosRealizados->push(word_serched, word_replaced, "No Revertido", word, positionCol, positionRow);
                //insertar en la lista de caracteres
                listaCaracteres->addNode(word);
                //dibujar el caracter nuevamente en la pantalla
                mvaddch(positionRow, positionCol, word);
                refresh();
                columna++;

                refresh();
            }
        }

        /*###########################################################################################
         *############## ACEPTACION DE LAS TECLAS NORMALES QUE SE INGRESAN EN EL TECLADO
         *###########################################################################################
         */

        //compara que los caracteres esten en un rango valido
        else if ((key >= 33 && key <= 126) || key == 164 || key == 165 || key == 32 || key == 9 || key == 8 || key == 127 || key == KEY_BACKSPACE)
        {
            //compara la barra espaciadora
            if (key == 32)
            {
                listaCaracteres->addNode(key);
                listaDePlabras->addNode(palabraConcatenada);
                palabraConcatenada = "";
                mvaddch(fila, columna, key);
                refresh();
                columna++;
            }
            //compara un tab horizontal
            if (key == 9)
            {
                listaCaracteres->addNode(key);
                listaDePlabras->addNode(palabraConcatenada);
                palabraConcatenada = "";
                columna = columna + 5;
                mvaddch(fila, columna, 32);
                refresh();
                columna++;
            }
            /*########################################
            *ELIMINA UN CARACTER DE LA LISTA
            *########################################
            */

            if (key == 8 || key == 127 || key == KEY_BACKSPACE)
            {

                listaCaracteres->deleteNode();
                //pilaCambiosRealizados->push("null", "null", "No Revertido", to_string(key), columna, fila);
                columna--;
                mvaddch(fila, columna + 1, 32);
                mvaddch(fila, columna + 2, 32);
                mvaddch(fila, columna, 32);
                mvprintw(fila, columna, "");
                refresh();
            }
            /*########################################
            *AGREGA UN CARACTER VALIDO A LA LISTA
            *########################################
            */
            else
            {
                palabraConcatenada += (char)key;
                listaCaracteres->addNode(key);
                pilaCambiosRealizados->push("null", "null", "No Revertido", key, columna, fila);
                mvaddch(fila, columna, key);
                refresh();
                columna++;
                //i++;
            }
        }
        //compara el salto de linea y un tab vertical
        else if (key == 10 || key == 11)
        {
            listaDePlabras->addNode(palabraConcatenada);
            listaDePlabras->addNode("saltline");
            listaCaracteres->addNode(key);
            palabraConcatenada = "";
            fila++;
            columna = 0;
            mvprintw(fila, 0, "");
            refresh();
        }
        //ESC PARA SALIR DE ESTE MODO
        else if (key == 27)
        {
            iniciarMenu();
        }
        else
        {
        }
    }
    exit();
}

//###################################################################################
//######## VENTANA ABRIR UN ARCHIVO Y MOSTRARLO EN EL EDITOR DE TEXTO ###############
//###################################################################################
void buscarYReemplazar()
{
    int col = 20;

    mvprintw(18, 1, "Palabra a Buscar: ");
    mvprintw(18, 19, "");
    refresh();

    bool flag = true;
    int opc;
    while (flag)
    {
        opc = getch();
        if (opc != 10)
        {
            mvaddch(18, col, opc);
            refresh();
            palabraABuscar += (char)opc;
            col++;
        }
        else
        {
            flag = false;
        }
    }

    for (int i = 0; i < 28; i++)
    {
        mvaddch(18, i, 32);
        refresh();
    }

    flag = true;
    col = 22;
    mvprintw(18, 1, "Palabra a Reemplazar: ");
    mvprintw(18, 23, "");
    refresh();
    while (flag)
    {
        opc = getch();
        if (opc != 10)
        {
            mvaddch(18, col, opc);
            refresh();
            palabraAReemplazar += (char)opc;
            col++;
        }
        else
        {
            flag = false;
        }
    }

    //tengo palabra a BUscar y palabraA Reemplazar, las envio y me devuelve los nodos afectados
    listaDePlabras->modifyNode(palabraABuscar, palabraAReemplazar);
    int palabrasAfectadas = listaDePlabras->modificados;
    if (palabrasAfectadas > 0)
    {
        for (int i = 0; i < 70; i++)
        {
            mvaddch(0, i, 32);
            refresh();
        }
        for (int i = 0; i < 70; i++)
        {
            mvaddch(1, i, 32);
            refresh();
        }
        for (int i = 0; i < 70; i++)
        {
            mvaddch(2, i, 32);
            refresh();
        }
        for (int i = 0; i < 70; i++)
        {
            mvaddch(3, i, 32);
            refresh();
        }
        for (int i = 0; i < 70; i++)
        {
            mvaddch(4, i, 32);
            refresh();
        }
        for (int i = 0; i < 70; i++)
        {
            mvaddch(5, i, 32);
            refresh();
        }

        for (int i = 0; i < 70; i++)
        {
            mvaddch(6, i, 32);
            refresh();
        }
        for (int i = 0; i < 70; i++)
        {
            mvaddch(7, i, 32);
            refresh();
        }
        for (int i = 0; i < 70; i++)
        {
            mvaddch(8, i, 32);
            refresh();
        }
        for (int i = 0; i < 70; i++)
        {
            mvaddch(9, i, 32);
            refresh();
        }
        for (int i = 0; i < 70; i++)
        {
            mvaddch(10, i, 32);
            refresh();
        }

        for (int i = 0; i < 35; i++)

        {
            mvaddch(18, i, 32);
            refresh();
        }

        int fila = 0;
        int columna = 0;
        //agregar a la lista de palabras buscadas
        listaPalabrasBuscas->addNode(palabraABuscar, palabraAReemplazar);
        //agregar a la lista de palabras Reemplazadas
        listaPalabrasReemplazadas->addNode(palabraAReemplazar, palabraABuscar);
        //modificar la lista
        NodeWords *temporal = listaDePlabras->first;
        string recorridoPalabra = "";

        while (temporal != NULL)
        {
            recorridoPalabra = temporal->word;

            if (recorridoPalabra.compare("saltline") == 0)
            {
                fila++;
                columna = 0;
            }
            else
            {
                for (int i = 0; i < recorridoPalabra.length(); i++)
                {
                    mvaddch(fila, columna, recorridoPalabra.at(i));
                    refresh();
                    columna++;
                }
                columna++;
                mvaddch(fila, columna, 32);
                //columna++;
            }
            recorridoPalabra = "";
            temporal = temporal->next;
        }
    }

    for (int i = 0; i < 35; i++)
    {
        mvaddch(18, i, 32);
        refresh();
    }

    mvprintw(18, 1, "Palabra Modificadas: ");
    mvaddch(18, 22, palabrasAfectadas + 48);
    refresh();
}

//###################################################################################
//######## VENTANA ABRIR UN ARCHIVO Y MOSTRARLO EN EL EDITOR DE TEXTO ###############
//###################################################################################
void windowOpenFile()
{
    exit();
}

//###################################################################################
//########### VENTANA QUE MOSTRARA LOS ARCHIVOS RECIENTES ABIERTOS  #################
//###################################################################################
void windowRecentFiles()
{
    clear();
    mvprintw(1, 10, "=================================================================");
    mvprintw(2, 10, "|                    ARCHIVOS RECIENTES                         |");
    mvprintw(3, 10, "=================================================================");
    mvprintw(4, 10, "");
    refresh();
    if (listaArchivosRecientes->isEmpty())
    {
        mvprintw(5, 10, "NO HAY ARCHIVOS RECIENTES");
        mvprintw(6, 10, "");
        refresh();
    }
    else
    {
        int fila = 7;
        int columna = 1;
        int pos = 49;
        NodeRecentFiles *temp = listaArchivosRecientes->first;

        while (temp->next != listaArchivosRecientes->first)
        {
            char name[50];
            char location[150];
            string nombre = temp->file_name;
            string locacion = temp->location;

            for (int i = 0; i < nombre.length(); i++)
            {
                name[i] = nombre.at(i);
            }

            for (int i = 0; i < locacion.length(); i++)
            {
                location[i] = locacion.at(i);
            }
            mvaddch(fila, columna, pos);
            mvaddch(fila, columna + 1, 46);
            mvprintw(fila, columna + 3, name);
            mvprintw(fila, columna + 14, location);
            fila++;
            pos++;
            columna = 1;
            temp = temp->next;
        }
        char name[50];
        char location[150];
        string nombre = temp->file_name;
        string locacion = temp->location;

        for (int i = 0; i < nombre.length(); i++)
        {
            name[i] = nombre.at(i);
        }

        for (int i = 0; i < locacion.length(); i++)
        {
            location[i] = locacion.at(i);
        }
        mvaddch(fila, columna, pos);
        mvaddch(fila, columna + 1, 46);
        mvprintw(fila, columna + 3, name);
        mvprintw(fila, columna + 14, location);
        listaArchivosRecientes->graphList();
    }

    getch();
    getch();
    iniciarMenu();
}

//###################################################################################
//########### VENTANA PARA GUARDAR MI ARCHIVO RECIEN CREADO  ########################
//###################################################################################
void windowSaveFile()
{
    clear();
    mvprintw(2, 15, "=====================================================");
    mvprintw(3, 15, "|                 GUARDAR ARCHIVO                   |");
    mvprintw(4, 15, "=====================================================");

    mvprintw(5, 15, "Ingrese un nombre para guardar el documento:");
    mvprintw(6, 15, "");
    refresh();
    string nameFile = "";
    bool flag = true;
    int columna = 15;
    while (flag)
    {
        int opc = getch();
        if (opc != 10)
        {
            mvaddch(6, columna, opc);
            refresh();
            nameFile += (char)opc;
            columna++;
        }
        else
        {
            flag = false;
        }
    }
    ofstream myFile;
    myFile.open(nameFile + ".txt");
    NodeCharacter *temp = listaCaracteres->first;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    while (temp->previous != listaCaracteres->first)
    {
        myFile << temp->character;
        temp = temp->previous;
    }
    myFile << temp->character;
    temp = temp->previous;
    myFile << temp->character;
    myFile.close();
    string directorio = "";

    //***********************************************
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        directorio += cwd;
        directorio += "/";
        directorio += nameFile + ".txt";
        listaArchivosRecientes->addNode(nameFile + ".txt", directorio);
    }
    else
    {
        perror("getcwd() error");
    }
    //***********************************************
    //LIMPIAR LAS ESTRUCTURAS
    listaCaracteres->clearOut();
    pilaCambiosRealizados->clearOut();
    pilaRevertidos->clearOut();
    iniciarMenu();
}

//###################################################################################
//##################### VENTANA PARA MOSTRAR REPORTES ###############################
//###################################################################################
void windowReports()
{
    mvprintw(19, 1, "=============================== REPORTES =====================================");
    mvprintw(20, 1, "1)LISTA CARACTERES   2)PALABRAS BUSCADAS   3)PALABRAS ORDENADAS");
    mvprintw(20, 66, "");
    refresh();
    bool flag = true;
    while (flag)
    {
        int opc = getch();
        if (opc == '1')
        {
            if (listaCaracteres->isEmpty())
            {
            }
            else
            {
                listaCaracteres->graphList();
            }
        }
        if (opc == '2')
        {
            if (pilaCambiosRealizados->isEmpty())
            {
            }
            else
            {
                pilaCambiosRealizados->graphStack();
                if (pilaRevertidos->isEmpty())
                {
                }
                else
                {
                    pilaRevertidos->graphStack();
                }
            }
        }
        if (opc == '3')
        {
            //Aqui va el reporte de palabras ordenadas, se genera al tener ya la funcionalidad
            if (listaPalabrasBuscas->isEmpty())
            {
            }
            else
            {
                listaPalabrasBuscas->graphList();
                listaPalabrasReemplazadas->graphList();
            }
        }
        if (opc == '4')
        {
            flag = false;
        }
    }
    for (int i = 0; i < 86; i++)
    {
        mvaddch(19, i, 32);
        mvaddch(20, i, 32);
        refresh();
    }
}

//###################################################################################
//##################### CERRAR LA VENTANA DE NCURSES ################################
//###################################################################################

void exit()
{
    endwin();
    //listaDePlabras->showList();
    //cout<<"\n";
    //cout<<"\n";
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
    //windowRecentFiles();
    return 0;
}