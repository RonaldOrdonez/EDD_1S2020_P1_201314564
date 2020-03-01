#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using std::string;
using namespace std;

//*********************************************************************************
//LISTA SIMPLE ENLAZADA ORDENADA QUE GUARDA LAS PALABRAS BUSCADAS
//*********************************************************************************

class NodeWordSerched
{
public:
    string original_word;  // original word that was serched
    string replaced_by;    // word that replaced to the original
    NodeWordSerched *next; // next node

public:
    NodeWordSerched()
    {
        original_word = "";
        replaced_by = "";
        next = NULL;
    }
    NodeWordSerched(string original_word, string replaced_by)
    {
        this->original_word = original_word;
        this->replaced_by = replaced_by;
        next = NULL;
    }
};

class ListWordsSerched
{
public:
    NodeWordSerched *first;

public:
    ListWordsSerched()
    {
        first = NULL;
    }

    void clearOut(){
        first=NULL;
    }

     /****************************************************************
    *DEVUELVE SI LA LISTA ESTA VACIA O NO
    * ***************************************************************
    */

    bool isEmpty(){
        if(first==NULL)
        return true;
        else
        {
            return false;
        }       
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
    //METODO PARA AGREGAR UN NODO A LA LISTA DE BUSCADOS
    //*********************************************************************************
    void addNode(string original_word, string replaced_by)
    {

        //hago una copia de la palabra original y la convierto a minuscula
        string original_word_copy = aMinuscula(original_word);

        NodeWordSerched *newNode = new NodeWordSerched(original_word, replaced_by);
        if (first == NULL)
        {
            first = newNode;
            first->next = NULL;
        }
        else
        {
            //verificar si la palabra a ingresar va antes de la cabeza para hacer susititucion
            if ((original_word_copy.compare(aMinuscula(first->original_word)) < 0) || (original_word_copy.compare(aMinuscula(first->original_word)) == 0))
            { // lo q voy a ingresar va antes de la cabeza
                newNode->next = first;
                first = newNode;
            }
            //si lo q voy a ingresar es mayor que la cabeza hay q avanzar hasta encontrar la compracion correcta
            else
            {
                NodeWordSerched *temp = first;
                bool flag = false;
                while (temp->next != NULL && flag == false)
                {
                    if ((original_word_copy.compare(aMinuscula(temp->next->original_word)) < 0) || (original_word_copy.compare(aMinuscula(temp->next->original_word)) == 0))
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
        NodeWordSerched *aux = first;
        while (aux->next != NULL)
        {
            cout << "(";
            cout << aux->original_word << ",";
            cout << aux->replaced_by;
            cout << "),";
            aux = aux->next;
        }
        cout << "(";
        cout << aux->original_word << ",";
        cout << aux->replaced_by;
        cout << ")\n";
    }

    //*************************************************************************
    //METODO PARA GRAFICAR LOS NODOS DE LA LISTA DE PALABRAS BUSCADAS
    //*************************************************************************
    void graphList()
    {
        if (first == NULL)
        {
            cout << "LISTA VACIA";
        }
        else
        {
            NodeWordSerched *aux = first;
            int numNode = 0;
            string scriptGraph = "digraph listaPalabrasBuscadas{ \n";
            scriptGraph += "rankdir=LR; \n";
            scriptGraph += "node[shape=record]; \n";

            while (aux->next != NULL)
            {
                scriptGraph += "node" + to_string(numNode) + "[label=\"";
                scriptGraph += aux->original_word + "\\" + "n";
                scriptGraph += "Reemplazada por: ";
                scriptGraph += aux->replaced_by;
                scriptGraph += "\"]; \n";

                scriptGraph += "node" + to_string(numNode);
                scriptGraph += "->";
                scriptGraph += "node" + to_string(numNode + 1);
                scriptGraph += "; \n";
                numNode++;
                aux = aux->next;
            }
            scriptGraph += "node" + to_string(numNode) + "[label=\"";
            scriptGraph += aux->original_word + "\\" + "n";
            scriptGraph += "Reemplazada por: ";
            scriptGraph += aux->replaced_by;
            scriptGraph += "\"]; \n";
            scriptGraph += "}";

            ofstream myFile;
            myFile.open("listaPalabrasBuscadas.dot");
            myFile << scriptGraph;
            myFile.close();
            system("dot -Tpng listaPalabrasBuscadas.dot -o listaPalabrasBuscadas.png");
            system("shotwell listaPalabrasBuscadas.png");
        }
    }
};

/*
int main()
{
    ListWordsSerched *list = new ListWordsSerched();
    list->addNode("distrito", "dis");
    list->addNode("UVA", "10");
    list->addNode("Hola", "ride");
    list->addNode("ala", "wing");
    list->addNode("Adan", "wing");
    list->addNode("1er", "primero");
    cout << "\n";
    list->graphList();
    return 0;
}*/
