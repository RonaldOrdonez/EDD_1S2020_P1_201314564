#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//*********************************************************************************
// PILA QUE MANEJA LOS CAMBIOS REALIZADOS EN LA CONSOLA DE EDICION
//*********************************************************************************

class NodeChangesMade{
    public:
        string word_serched;
        string word_replaced;
        bool state;
        string word;
        int position;
        NodeChangesMade* next;
    
    public:
        NodeChangesMade(){
            word_serched = "";
            word_replaced = "";
            state = false;
            word = "";
            position = 0;
            next = NULL;            
        }

        NodeChangesMade(string word_serched, string word_replaced, bool state, string word, int position){
            this->word_serched = word_serched;
            this->word_replaced = word_replaced;
            this->state = state;
            this->word = word;
            this->position = position;
            next = NULL;
        }
};

class StackChangedMade{

    public:
        NodeChangesMade* top;
    
    public:
        //CONSTRUCTOR
        StackChangedMade(){
            top = NULL;
        }
    
        //****************************************************************
        // METODO PARA AGREGAR(PUSH) EN LA PILA
        //****************************************************************
        void push(string word_serched, string word_replaced, bool state, string word, int position){
            
            NodeChangesMade* newNode = new NodeChangesMade(word_serched, word_replaced, state, word, position);
            if(top == NULL){
                top = newNode;
            }
            else{
                newNode->next = top;
                top = newNode;
            }                   
        }

        //****************************************************************
        // METODO PARA ELIMINAR O SACAR(POP) DE LA PILA
        //****************************************************************
        NodeChangesMade* pop(){
            NodeChangesMade* temp = top;
            top = top->next;
            return temp;                      
        }

        void print(){
            NodeChangesMade* aux=top;
            while(aux->next!=NULL){
                cout<<aux->word_serched;
                cout<<",";
                aux=aux->next;
            }
            cout<<aux->word_serched;
        }
};

/*
int main(){
    StackReversed* list = new StackReversed();
    list->push("hola","mucho",false,"gusto",0);
    list->push("mucho","mucho",false,"gusto",0);
    list->push("gusto","mucho",false,"gusto",0);
    list->push("pedro","mucho",false,"gusto",0);
    cout<<"\n";
    list->print();
    NodeReversed* sacado = list->pop();
    cout<<"\n";
    cout<<"HA SALIDO DE PILA: ";
    cout<<sacado->word_serched;
    cout<<"\n";
    list->print();
    return 0;
}
*/