#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//***********************************************************************************
//LISRA CIRCULAR SIMPLE QUE LLEVA EL ORDEN DE LS ARCHIVOS RECIENTEMENTE ABIERTOS 
//***********************************************************************************

class NodeRecentFiles{
    public:
        string file_name;
        string location;
        NodeRecentFiles* next;

    public:
        NodeRecentFiles(){
            file_name="";
            location="";
            next = NULL;
        }

        NodeRecentFiles(string file_name, string location){
            this->file_name = file_name;
            this->location = location;
            next = NULL;
        }
};

class ListRecentFiles{
    public:
        NodeRecentFiles* first;
        NodeRecentFiles* last;

    public:
        //CONSTRUCTOR
        ListRecentFiles(){
            first=NULL;
            last=NULL;
        }        

        /*********************************************************************
         * METODO PARA AGREGAR LOS ARCHIVOS ABIERTOS RECIENTEMENTE A LA LISTA
         * UTILIZANDO UNA INSERCION AL INICIO PARA QUE LOS ABIERTOS RECIEN
         * QUEDEN HASTA AL PRINCIPIO
        **********************************************************************/
        void addNode(string file_name, string location){
            NodeRecentFiles* new_node = new NodeRecentFiles(file_name, location);
            //si aun no nhay elementos agregados en la lista
            if(first==NULL){
                first=new_node;
                last=new_node;
                last->next = first;
            }
            else{
                new_node->next=first;
                first=new_node;
                last->next=first;
            }
        }

        /************************************************************************
         * MOSTRAR LOS ELEMENTOS DE LA LISTA EN LA PANTALLA
         * ***********************************************************************/
        void showList(){
            NodeRecentFiles* aux = first;
            do{
                cout<<aux->file_name<<",";                
                aux=aux->next;               

            }while(aux!=first);
        }
};

/*
int main(){
    ListRecentFiles* list = new ListRecentFiles();
    list->addNode("aa","dis");
    list->addNode("bb","10");
    list->addNode("ca","ride");
    list->addNode("daa","wing");
    cout<<"\n";
    list->showList();
    return 0;
}*/

