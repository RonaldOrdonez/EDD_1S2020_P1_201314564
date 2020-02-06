#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class NodeWordReplaced{
    public:
        string word_replaced; //palabra que se puso como reemplazo
        string replaced_to;   //palabra que fue remplazada
        NodeWordReplaced* next;
    
    public:
        NodeWordReplaced(){
            word_replaced = "";
            replaced_to = "";
            next=NULL;            
        }

        NodeWordReplaced(string word_replaced, string replaced_to){
            this->word_replaced = word_replaced;
            this->replaced_to = replaced_to;
            next=NULL;
        }
        
};

class ListWordsReplaced{
    public:
        NodeWordReplaced *first;
    
    public: 
        ListWordsReplaced(){
            first = NULL;
        }

        //*********************************************************************************
        //METODO PARA AGREGAR UN NODO A LA LISTA DE REEMPLAZADOS
        //*********************************************************************************
        void addNode(string word_replaced, string replaced_to){
            NodeWordReplaced* newNode = new NodeWordReplaced(word_replaced,replaced_to);
            if(first==NULL){
                first=newNode;
                first->next = NULL;                
            }
            else{
                //verificar si la palabra a ingresar va antes de la cabeza para hacer susititucion                
                if((word_replaced.compare(first->word_replaced) < 0) || (word_replaced.compare(first->word_replaced) == 0)){ // lo q voy a ingresar va antes de la cabeza
                    newNode->next=first;
                    first=newNode;                    
                }
                //si lo q voy a ingresar es mayor que la cabeza hay q avanzar hasta encontrar la compracion correcta
                else{
                    NodeWordReplaced* temp = first;
                    bool flag = false;
                    while(temp->next != NULL && flag==false){
                        if((word_replaced.compare(temp->next->word_replaced) < 0) || (word_replaced.compare(temp->next->word_replaced) == 0)){
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
            NodeWordReplaced* aux = first;
            while(aux->next!=NULL){
                cout<<"(";
                cout<<aux->word_replaced<<",";
                cout<<aux->replaced_to;
                cout<<"),";
                aux=aux->next;
            }
            cout<<"(";
            cout<<aux->word_replaced<<",";
            cout<<aux->replaced_to;
            cout<<")";
        }
};

/*
int main(){
    ListWordsReplaced* list = new ListWordsReplaced();
    list->addNode("1erecho","primer");
    list->addNode("istemas","sist");
    list->addNode("u","universidad");
    list->addNode("ala","wing");
    cout<<"\n";
    list->showList();
    return 0;
}
*/