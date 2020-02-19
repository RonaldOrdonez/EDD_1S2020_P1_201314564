#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

//***********************************************************************************
//LISRA CIRCULAR SIMPLE QUE LLEVA EL ORDEN DE LS ARCHIVOS RECIENTEMENTE ABIERTOS
//***********************************************************************************

class NodeRecentFiles
{
public:
    string file_name;
    string location;
    NodeRecentFiles *next;

public:
    NodeRecentFiles()
    {
        file_name = "";
        location = "";
        next = NULL;
    }

    NodeRecentFiles(string file_name, string location)
    {
        this->file_name = file_name;
        this->location = location;
        next = NULL;
    }
};

class ListRecentFiles
{
public:
    NodeRecentFiles *first;
    NodeRecentFiles *last;

public:
    //CONSTRUCTOR
    ListRecentFiles()
    {
        first = NULL;
        last = NULL;
    }

    /*********************************************************************
         * METODO PARA AGREGAR LOS ARCHIVOS ABIERTOS RECIENTEMENTE A LA LISTA
         * UTILIZANDO UNA INSERCION AL INICIO PARA QUE LOS ABIERTOS RECIEN
         * QUEDEN HASTA AL PRINCIPIO
        **********************************************************************/
    void addNode(string file_name, string location)
    {
        NodeRecentFiles *new_node = new NodeRecentFiles(file_name, location);
        //si aun no nhay elementos agregados en la lista
        if (first == NULL)
        {
            first = new_node;
            last = new_node;
            last->next = first;
        }
        else
        {
            new_node->next = first;
            first = new_node;
            last->next = first;
        }
    }

    /************************************************************************
         * MOSTRAR LOS ELEMENTOS DE LA LISTA EN LA PANTALLA
         * ***********************************************************************/
    void showList()
    {
        NodeRecentFiles *aux = first;
        do
        {
            cout << aux->file_name << ",";
            aux = aux->next;

        } while (aux != first);
    }

    /************************************************************************
         * GRAFICA LOS ELEMENTOS DE LA LISTA
         * ***********************************************************************/
    void graphList()
    {
        if (first == NULL)
        {
            cout << "LISTA VACIA";
        }
        else
        {
            NodeRecentFiles *aux = first;
            int numNode = 0;
            string scriptGraph = "digraph archivosRecientes{ \n";
            scriptGraph += "rankdir=LR; \n";
            scriptGraph += "node[shape=record]; \n";
            
            while (aux->next != first)
            {
                scriptGraph += "node" + to_string(numNode) + "[label=\"";
                scriptGraph += aux->file_name + "\\" + "n";                
                scriptGraph += aux->location;
                scriptGraph += "\"]; \n";             

                scriptGraph += "node" + to_string(numNode);
                scriptGraph += "->";
                scriptGraph += "node" + to_string(numNode + 1);
                scriptGraph += "; \n";
                numNode++;
                aux = aux->next;
            }
            scriptGraph += "node" + to_string(numNode) + "[label=\"";
            scriptGraph += aux->file_name + "\\" + "n";                
            scriptGraph += aux->location;
            scriptGraph += "\"]; \n";            
            scriptGraph += "node" + to_string(numNode);
            scriptGraph += "->";
            scriptGraph += "node0";
            scriptGraph += "; \n";          
            scriptGraph += "}";

            ofstream myFile;
            myFile.open("listaArchivosRecientes.dot");
            myFile << scriptGraph;
            myFile.close();
            system("dot -Tpng listaArchivosRecientes.dot -o listaArchivosRecientes.png");
            system("shotwell listaArchivosRecientes.png");
        }
    }
};

/*
int main(){
    ListRecentFiles* list = new ListRecentFiles();
    list->addNode("Archivo1","home/user/desktop/Archivo1");
    list->addNode("Archivo2","home/user/desktop/Archivo2");
    list->addNode("Archivo3","home/user/desktop/Archivo3");
    list->addNode("Archivo4","home/user/desktop/Archivo4");
    cout<<"\n";
    list->graphList();
    return 0;
}
*/