#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//*********************************************************************************
// PILA QUE GUARDA LAS PALABRAS QUE FUERON REVERTIDAS AL PRESIONAR CTRL+Z
//*********************************************************************************

class NodeReversed{
    public:
        string word_serched;
        string word_replaced;
        bool state;
        string word;
        int position;
        NodeReversed* next;
    
    public:
        NodeReversed(){
            word_serched = "";
            word_replaced = "";
            state = false;
            word = "";
            position = 0;
            next = NULL;            
        }

        NodeReversed(string word_serched, string word_replaced, bool state, string word, int position){
            this->word_serched = word_serched;
            this->word_replaced = word_replaced;
            this->state = state;
            this->word = word;
            this->position = position;
            next = NULL;
        }
};

class StackReversed{

    public:
        NodeReversed* top;
    
    public:
        StackReversed(){
            top = NULL;
        }
    
        //****************************************************************
        // METODO PARA AGREGAR(PUSH) EN LA PILA
        //****************************************************************
        void push(string word_serched, string word_replaced, bool state, string word, int position){
            
            NodeReversed* newNode = new NodeReversed(word_serched, word_replaced, state, word, position);
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
        NodeReversed* pop(){
            NodeReversed* temp = top;
            top = top->next;
            return temp;                      
        }

        void print(){
            NodeReversed* aux=top;
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