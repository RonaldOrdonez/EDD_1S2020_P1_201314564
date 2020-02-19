#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using std::string;
using namespace std;

//*********************************************************************************
//LISTA SIMPLE ENLAZADA ORDENADA QUE GUARDA LAS PALABRAS REEMPLAZDAS
//*********************************************************************************

class NodeWordReplaced
{
public:
    string word_replaced; //palabra que se puso como reemplazo
    string replaced_to;   //palabra que fue remplazada
    NodeWordReplaced *next;

public:
    NodeWordReplaced()
    {
        word_replaced = "";
        replaced_to = "";
        next = NULL;
    }

    NodeWordReplaced(string word_replaced, string replaced_to)
    {
        this->word_replaced = word_replaced;
        this->replaced_to = replaced_to;
        next = NULL;
    }
};

class ListWordsReplaced
{
public:
    NodeWordReplaced *first;

public:
    ListWordsReplaced()
    {
        first = NULL;
    }

    //*********************************************************************************
    //CONVIERTE A MINUSCULAS UNA CADENA
    //*********************************************************************************

    string aMinuscula(string cadena)
    {
        for (int i = 0; i < cadena.length(); i++)
            cadena[i] = tolower(cadena[i]);
        return cadena;
    }

    //*********************************************************************************
    //METODO PARA AGREGAR UN NODO A LA LISTA DE REEMPLAZADOS
    //*********************************************************************************
    void addNode(string word_replaced, string replaced_to)
    {
        string word_replaced_copy = aMinuscula(word_replaced);
        NodeWordReplaced *newNode = new NodeWordReplaced(word_replaced, replaced_to);
        if (first == NULL)
        {
            first = newNode;
            first->next = NULL;
        }
        else
        {
            //verificar si la palabra a ingresar va antes de la cabeza para hacer susititucion
            if ((word_replaced_copy.compare(aMinuscula(first->word_replaced)) < 0) || (word_replaced_copy.compare(aMinuscula(first->word_replaced)) == 0))
            { // lo q voy a ingresar va antes de la cabeza
                newNode->next = first;
                first = newNode;
            }
            //si lo q voy a ingresar es mayor que la cabeza hay q avanzar hasta encontrar la compracion correcta
            else
            {
                NodeWordReplaced *temp = first;
                bool flag = false;
                while (temp->next != NULL && flag == false)
                {
                    if ((word_replaced_copy.compare(aMinuscula(temp->next->word_replaced)) < 0) || (word_replaced_copy.compare(aMinuscula(temp->next->word_replaced)) == 0))
                    {
                        newNode->next = temp->next;
                        temp->next = newNode;
                        flag = true;
                    }
                    else
                    {
                        temp = temp->next;
                    }
                }
                if (flag == false)
                {
                    temp->next = newNode;
                    newNode->next = NULL;
                }
            }
        }
    }
    //*************************************************************************
    //METODO PARA IMPRIMIR LOS VALORES EN PANTALLA
    //*************************************************************************
    void showList()
    {
        NodeWordReplaced *aux = first;
        while (aux->next != NULL)
        {
            cout << "(";
            cout << aux->word_replaced << ",";
            cout << aux->replaced_to;
            cout << "),";
            aux = aux->next;
        }
        cout << "(";
        cout << aux->word_replaced << ",";
        cout << aux->replaced_to;
        cout << ")\n";
    }

    //*************************************************************************
    //METODO PARA GRAFICAR LA LISTA DE PALABRAs REEMPLAZADAS
    //*************************************************************************
    void graphList()
    {
        if (first == NULL)
        {
            cout << "LISTA VACIA";
        }
        else
        {
            NodeWordReplaced *aux = first;
            int numNode = 0;
            string scriptGraph = "digraph listaPalabrasReemplazadas{ \n";
            scriptGraph += "rankdir=LR; \n";
            scriptGraph += "node[shape=record]; \n";

            while (aux->next != NULL)
            {
                scriptGraph += "node" + to_string(numNode) + "[label=\"";
                scriptGraph += aux->word_replaced + "\\" + "n";
                scriptGraph += "Reemplazo a: ";
                scriptGraph += aux->replaced_to;
                scriptGraph += "\"]; \n";

                scriptGraph += "node" + to_string(numNode);
                scriptGraph += "->";
                scriptGraph += "node" + to_string(numNode + 1);
                scriptGraph += "; \n";
                numNode++;
                aux = aux->next;
            }
            scriptGraph += "node" + to_string(numNode) + "[label=\"";
            scriptGraph += aux->word_replaced + "\\" + "n";
            scriptGraph += "Reemplazo a: ";
            scriptGraph += aux->replaced_to;
            scriptGraph += "\"]; \n";
            scriptGraph += "}";

            ofstream myFile;
            myFile.open("listaPalabrasReemplazadas.dot");
            myFile << scriptGraph;
            myFile.close();
            system("dot -Tpng listaPalabrasReemplazadas.dot -o listaPalabrasReemplazadas.png");
            system("shotwell listaPalabrasReemplazadas.png");
        }
    }
};

int main()
{
    ListWordsReplaced *list = new ListWordsReplaced();
    list->addNode("1er", "Primer");
    list->addNode("Sistemas", "Sist");
    list->addNode("U", "Universidad");
    list->addNode("ala", "wing");
    cout << "\n";
    list->showList();
    list->graphList();
    return 0;
}
