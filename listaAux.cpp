#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//***********************************************************************************
//LISRA CIRCULAR SIMPLE QUE LLEVA EL ORDEN DE LS ARCHIVOS RECIENTEMENTE ABIERTOS
//***********************************************************************************

class NodeWords
{

public:
    string word;    
    NodeWords *next;

public:
    NodeWords()
    {
        word = "";        
        next = NULL;
    }

    NodeWords(string word)
    {
        this->word = word;        
        next = NULL;
    }
};

class ListWords
{
public:
    int modificados;
    NodeWords *first;

public:
    //CONSTRUCTOR
    ListWords()
    {
        first = NULL;
        modificados=0;
    }

    bool isEmpty()
    {
        if (first == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int numModify(){
        return modificados;
    }

    /*********************************************************************
         * METODO PARA AGREGAR 
        **********************************************************************/
    void addNode(string word)
    {
        NodeWords *new_node = new NodeWords(word);
        //si aun no nhay elementos agregados en la lista
        if (first == NULL)
        {
            first = new_node;
        }
        else
        {
            NodeWords *temp = first;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }

    //modifica las palabras en la lista
    void modifyNode(string palabraBuscar, string palabraReemplazar)
    {        
        NodeWords* aux = first;
        while (aux != NULL)
        {
            if (aux->word.compare(palabraBuscar) == 0)
            {
                aux->word = palabraReemplazar;   
                modificados++;             
            }
            aux=aux->next;                     
        }
        
    }

    /************************************************************************
         * MOSTRAR LOS ELEMENTOS DE LA LISTA EN LA PANTALLA
         * **********************************************************************
         * */
    void showList()
    {
        NodeWords *aux = first;
        while (aux->next != NULL)
        {
            cout << aux->word;
            cout << ",";
            aux = aux->next;
        }
        cout << aux->word;        
    }
};

/*
int main()
{
    ListWords *list = new ListWords();
    list->addNode("hola");
    list->addNode("mundo");
    list->addNode("hola");
    list->addNode("como");
    list->addNode("estan");
    list->addNode("hola");    
    cout << "\n";
    list->showList();
    cout << "\n";
    int modificadas = list->modifyNode("hola","JOJO");
    list->showList();
    cout << "\n";
    cout<<"PALABRAS MODIFICADAS: ";
    cout<<modificadas;
    cout<<"\n";        
    return 0;
}*/
