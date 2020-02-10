#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//*********************************************************************************
//LISTA SIMPLE ENLAZADA ORDENADA QUE GUARDA LAS PALABRAS BUSCADAS
//*********************************************************************************

class NodeWordSerched{
    public:
        string original_word;  // original word that was serched
        string replaced_by;    // word that replaced to the original
        NodeWordSerched* next;  // next node
    
    public:
        NodeWordSerched(){
            original_word = "";
            replaced_by = "";
            next = NULL;
        }
        NodeWordSerched(string original_word, string replaced_by){
            this->original_word = original_word;
            this->replaced_by = replaced_by;
            next = NULL;            
        }
};

class ListWordsSerched{
    public:
        NodeWordSerched *first;
    
    public: 
        ListWordsSerched(){
            first = NULL;
        }

        //*********************************************************************************
        //METODO PARA AGREGAR UN NODO A LA LISTA DE BUSCADOS
        //*********************************************************************************
        void addNode(string original_word, string replaced_by){
            NodeWordSerched* newNode = new NodeWordSerched(original_word,replaced_by);
            if(first==NULL){
                first=newNode;
                first->next = NULL;                
            }
            else{
                //verificar si la palabra a ingresar va antes de la cabeza para hacer susititucion                
                if((original_word.compare(first->original_word) < 0) || (original_word.compare(first->original_word) == 0)){ // lo q voy a ingresar va antes de la cabeza
                    newNode->next=first;
                    first=newNode;                    
                }
                //si lo q voy a ingresar es mayor que la cabeza hay q avanzar hasta encontrar la compracion correcta
                else{
                    NodeWordSerched* temp = first;
                    bool flag = false;
                    while(temp->next != NULL && flag==false){
                        if((original_word.compare(temp->next->original_word) < 0) || (original_word.compare(temp->next->original_word) == 0)){
                            newNode->next = temp->next;
                            temp->next = newNode;
                            flag = true;
                        }
                        else{
                            temp=temp->next;
                        }
                    }
                    if(flag==false){
                        temp->next = newNode;
                        newNode->next = NULL;                    
                    }
                    
                }
                
            }

        }
        //*************************************************************************
        //METODO PARA IMPRIMIR LOS VALORES EN PANTALLA
        //*************************************************************************
        void showList(){
            NodeWordSerched* aux = first;
            while(aux->next!=NULL){
                cout<<"(";
                cout<<aux->original_word<<",";
                cout<<aux->replaced_by;
                cout<<"),";
                aux=aux->next;
            }
            cout<<"(";
            cout<<aux->original_word<<",";
            cout<<aux->replaced_by;
            cout<<")";
        }
};

/*
int main(){
    ListWordsSerched* list = new ListWordsSerched();
    list->addNode("distrito","dis");
    list->addNode("decimo","10");
    list->addNode("alambre","ride");
    list->addNode("ala","wing");
    cout<<"\n";
    list->showList();
    return 0;
}
*/