#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

//*********************************************************************************
// PILA QUE MANEJA LOS CAMBIOS REALIZADOS EN LA CONSOLA DE EDICION
//*********************************************************************************

class NodeChangesMade
{
public:
    string word_serched;
    string word_replaced;
    string state;
    string word;
    int positionCol;
    int positionRow;
    NodeChangesMade *next;

public:
    NodeChangesMade()
    {
        word_serched = "";
        word_replaced = "";
        state = "";
        word = "";
        positionCol = 0;
        positionRow = 0;
        next = NULL;
    }

    NodeChangesMade(string word_serched, string word_replaced, string state, string word, int positionCol, int positionRow)
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

class StackChangedMade
{

public:
    NodeChangesMade *top;

public:
    //CONSTRUCTOR
    StackChangedMade()
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
            NodeChangesMade *newNode = new NodeChangesMade(word_serched, word_replaced, state, word, positionCol, positionRow);
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
    NodeChangesMade *pop()
    {
        NodeChangesMade *temp = top;
        top = top->next;
        return temp;
    }

    //****************************************************************
    // METODO PARA IMPRIMIR LOS ELEMENTOS DE LA PILA
    //****************************************************************
    void print()
    {
        NodeChangesMade *aux = top;
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
            NodeChangesMade *aux = top;
            int numNode = 0;
            string scriptGraph = "digraph pilaCambiosRealizados{ \n";
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
            myFile.open("pilaCambiosRealizados.dot");
            myFile << scriptGraph;
            myFile.close();
            system("dot -Tpng pilaCambiosRealizados.dot -o pilaCambiosRealizados.png");
            system("shotwell pilaCambiosRealizados.png");
        }
    }
};

int main()
{
    StackChangedMade *list = new StackChangedMade();
    list->push("null", "null", "No Revertido", "1", 1, 2);
    list->push("null", "null", "No Revertido", "g", 1, 3);
    list->push("null", "null", "No Revertido", "a", 1, 4);
    list->push("null", "null", "No Revertido", "c", 1, 5);
    list->graphStack();
    return 0;
}
