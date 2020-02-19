#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

//*********************************************************************************
// PILA QUE GUARDA LAS PALABRAS QUE FUERON REVERTIDAS AL PRESIONAR CTRL+Z
//*********************************************************************************

class NodeReversed
{
public:
    string word_serched;
    string word_replaced;
    string state;
    string word;
    int positionCol;
    int positionRow;
    NodeReversed *next;

public:
    NodeReversed()
    {
        word_serched = "";
        word_replaced = "";
        state = "";
        word = "";
        positionCol = 0;
        positionRow = 0;
        next = NULL;
    }

    NodeReversed(string word_serched, string word_replaced, string state, string word, int positionCol, int positionRow)
    {
        this->word_serched = word_serched;
        this->word_replaced = word_replaced;
        this->state = state;
        this->word = word;
        this->positionCol = positionCol;
        this->positionRow = positionRow;
        next = NULL;
    }
};

class StackReversed
{

public:
    NodeReversed *top;

public:
    StackReversed()
    {
        top = NULL;
    }

    //****************************************************************
    // METODO PARA AGREGAR(PUSH) EN LA PILA
    //****************************************************************
    void push(string word_serched, string word_replaced, string state, string word, int positionCol, int positionRow)
    {
        if (word == " ")
        {
        }
        else
        {
            NodeReversed *newNode = new NodeReversed(word_serched, word_replaced, state, word, positionCol, positionRow);
            if (top == NULL)
            {
                top = newNode;
            }
            else
            {
                newNode->next = top;
                top = newNode;
            }
        }
    }

    //****************************************************************
    // METODO PARA ELIMINAR O SACAR(POP) DE LA PILA
    //****************************************************************
    void pop()
    {
        NodeReversed *temp = top;
        top = top->next;
    }

    //****************************************************************
    // METODO PARA IMPRIMIR EN PANTALLA
    //****************************************************************
    void print()
    {
        NodeReversed *aux = top;
        while (aux->next != NULL)
        {
            cout << aux->word_serched;
            cout << ",";
            aux = aux->next;
        }
        cout << aux->word_serched;
    }

    //****************************************************************
    // METODO PARA GRAFICAR LOS ELEMENTOS DE LA PILA
    //****************************************************************
    void graphStack()
    {

        if (top == NULL)
        {
            cout << "Pila Vacia";
        }
        else
        {
            NodeReversed *aux = top;
            int numNode = 0;
            string scriptGraph = "digraph pilaRevertidos{ \n";
            scriptGraph += "node[shape=record]; \n";
            while (aux->next != NULL)
            {
                // 34 es comillas, 47 es barra, 92 es barra invertida,
                if (aux->word == "\"" || aux->word == "/")
                {
                    scriptGraph += "node" + to_string(numNode) + "[label=\" Palabra Buscada: ";
                    scriptGraph += aux->word_serched + "\\" + "n";

                    scriptGraph += "Reemplazada Por: ";
                    scriptGraph += aux->word_replaced + "\\" + "n";

                    scriptGraph += "Estado: ";
                    scriptGraph += aux->state + "\\" + "n";

                    scriptGraph += "Palabra: \\";
                    scriptGraph += aux->word + "\\" + "n";

                    scriptGraph += "Posicion: ";
                    scriptGraph += to_string(aux->positionRow) + "," + to_string(aux->positionCol);
                    scriptGraph += "\" ]; \n";

                    scriptGraph += "node" + to_string(numNode);
                    scriptGraph += "->";
                    scriptGraph += "node" + to_string(numNode + 1);
                    scriptGraph += "; \n";

                    numNode++;
                    aux = aux->next;
                }
                else
                {
                    //Imprime todos los caracteres q no necesitan "/" para ser impresos
                    scriptGraph += "node" + to_string(numNode) + "[label=\" Palabra Buscada: ";
                    scriptGraph += aux->word_serched + "\\" + "n";

                    scriptGraph += "Reemplazada Por: ";
                    scriptGraph += aux->word_replaced + "\\" + "n";

                    scriptGraph += "Estado: ";
                    scriptGraph += aux->state + "\\" + "n";

                    scriptGraph += "Palabra: ";
                    scriptGraph += aux->word + "\\" + "n";

                    scriptGraph += "Posicion: ";
                    scriptGraph += to_string(aux->positionRow) + "," + to_string(aux->positionCol);
                    scriptGraph += "\" ]; \n";

                    scriptGraph += "node" + to_string(numNode);
                    scriptGraph += "->";
                    scriptGraph += "node" + to_string(numNode + 1);
                    scriptGraph += "; \n";
                    numNode++;
                    aux = aux->next;
                }
            }
            scriptGraph += "node" + to_string(numNode) + "[label=\" Palabra Buscada: ";
            scriptGraph += aux->word_serched + "\\" + "n";

            scriptGraph += "Reemplazada Por: ";
            scriptGraph += aux->word_replaced + "\\" + "n";

            scriptGraph += "Estado: ";
            scriptGraph += aux->state + "\\" + "n";

            scriptGraph += "Palabra: ";
            scriptGraph += aux->word + "\\" + "n";

            scriptGraph += "Posicion: ";
            scriptGraph += to_string(aux->positionRow) + "," + to_string(aux->positionCol);
            scriptGraph += "\" ]; \n";
            scriptGraph += "}";

            ofstream myFile;
            myFile.open("pilaRevertidos.dot");
            myFile << scriptGraph;
            myFile.close();
            system("dot -Tpng pilaRevertidos.dot -o pilaRevertidos.png");
            system("shotwell pilaRevertidos.png");
        }
    }
};

/*
int main(){
    StackReversed* list = new StackReversed();
    list->push("null", "null", "Revertido", "H", 1, 2);
    list->push("null", "null", "Revertido", "O", 1, 3);
    list->push("null", "null", "Revertido", "L", 1, 4);
    list->push("null", "null", "Revertido", "A", 1, 5);
    list->graphStack();

    return 0;
}*/
