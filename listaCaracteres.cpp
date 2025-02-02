#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

//*************************************************************************************
//           LISTA DOBLEMENTE ENLAZADA SIMPLE QUE GUARDA CADA CARACTER
//              INGRESADO AL MOMENTO DE ESCRIBIR EN LA CONSOLA
//*************************************************************************************
class NodeCharacter
{
public:
    char character;
    NodeCharacter *next;
    NodeCharacter *previous;

public:
    NodeCharacter()
    {
        character = ' ';
        next = NULL;
        previous = NULL;
    }

    NodeCharacter(char character)
    {
        this->character = character;
        next = NULL;
        previous = NULL;
    }
};

class ListCharacters
{
public:
    NodeCharacter *first;

public:
    //CONSTRUCTOR
    ListCharacters()
    {
        first = NULL;
    }

    void clearOut()
    {
        first = NULL;
    }

    /****************************************************************
    *DEVUELVE SI LA LISTA ESTA VACIA O NO
    * ***************************************************************
    */

    bool isEmpty()
    {
        if (first == NULL)
            return true;
        else
        {
            return false;
        }
    }

    /********************************************************************
         * METODO PARA INSERTAR NODOS AL PRINCIPIO DE LA LISTA
        ********************************************************************/

    void addNode(char character)
    {
        NodeCharacter *new_node = new NodeCharacter(character);

        if (first == NULL)
        {
            first = new_node;
        }
        else
        {
            first->previous = new_node;
            new_node->next = first;
            first = new_node;
        }
    }

    void addNodeLast(char character)
    {
        NodeCharacter *new_node = new NodeCharacter(character);

        if (first == NULL)
        {
            first = new_node;
        }
        else
        {
            NodeCharacter *temp = first;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = new_node;
            new_node->previous = temp;
        }
    }

    /********************************************************************
         * METODO PARA ELIMINAR NODOS DEL FINAL DE LA LISTA
    *********************************************************************/
    void deleteNode()
    {
        first = first->next;
    }

    void deleteLast()
    {
        if (first == NULL)
        {
            cout << "LISTA VACIA";
        }
        else
        {
            NodeCharacter *aux_ = first;
            while (aux_->next->next != NULL)
            {
                aux_ = aux_->next;
            }
            aux_->next->previous = NULL;
            aux_->next = NULL;
        }
    }

    /********************************************************************
         * METODO PARA MOSTRAR LOS NODOS EN PANTALLA
        *********************************************************************/
    void showList()
    {
        NodeCharacter *temp = first;
        cout << first->character << endl;
        cout << "anterior="
             << "NULL" << endl;
        cout << "siguiente=" << first->next->character << endl;
        cout << "\n";
        temp = temp->next;
        while (temp->next != NULL)
        {
            cout << temp->character << endl;
            cout << "anterior=" << temp->previous->character << endl;
            cout << "siguiente=" << temp->next->character << endl;
            cout << "\n";
            temp = temp->next;
        }
        cout << temp->character << endl;
        cout << "anterior=" << temp->previous->character << endl;
        cout << "siguiente="
             << "NULL" << endl;
    }

    /********************************************************************
         * METODO PARA GRAFICAR LA LISTA DOBLEMENTE ENLAZADA
        *********************************************************************/
    void graphList()
    {
        if (first == NULL)
        {
            cout << "Lista Vacia";
        }
        else
        {
            NodeCharacter *aux = first;
            int numNode = 0;
            string scriptGraph = "digraph caracteres{ \n";
            scriptGraph += "node[shape=record]; \n";
            while (aux->next != NULL)
            {
                // 34 es comillas, 47 es barra, 92 es barra invertida,
                if (aux->character == 34 || aux->character == 47 || aux->character == 92)
                {
                    scriptGraph += "node" + to_string(numNode) + "[label=\"\\";
                    scriptGraph += aux->character;
                    scriptGraph += "\"];\n";
                    scriptGraph += "node" + to_string(numNode);
                    numNode = numNode + 1;
                    scriptGraph += "->node" + to_string(numNode);
                    scriptGraph += ";\n";
                    scriptGraph += "node" + to_string(numNode);
                    numNode = numNode - 1;
                    scriptGraph += "->node" + to_string(numNode);
                    scriptGraph += ";\n";
                    numNode++;
                    aux = aux->next;
                }
                else if (aux->character == 32)
                {
                    scriptGraph += "node" + to_string(numNode) + "[label=\"";
                    scriptGraph += "\"];\n";
                    scriptGraph += "node" + to_string(numNode);
                    numNode = numNode + 1;
                    scriptGraph += "->node" + to_string(numNode);
                    scriptGraph += ";\n";
                    scriptGraph += "node" + to_string(numNode);
                    numNode = numNode - 1;
                    scriptGraph += "->node" + to_string(numNode);
                    scriptGraph += ";\n";
                    numNode++;
                    aux = aux->next;
                }
                else
                {
                    scriptGraph += "node" + to_string(numNode) + "[label=\"";
                    scriptGraph += aux->character;
                    scriptGraph += "\"];\n";
                    scriptGraph += "node" + to_string(numNode);
                    numNode = numNode + 1;
                    scriptGraph += "->node" + to_string(numNode);
                    scriptGraph += ";\n";
                    scriptGraph += "node" + to_string(numNode);
                    numNode = numNode - 1;
                    scriptGraph += "->node" + to_string(numNode);
                    scriptGraph += ";\n";
                    numNode++;
                    aux = aux->next;
                }
            }
            scriptGraph += "node" + to_string(numNode) + "[label=";
            scriptGraph += aux->character;
            scriptGraph += "];\n";
            scriptGraph += "}";

            ofstream myFile;
            myFile.open("listaCaracteres.dot");
            myFile << scriptGraph;
            myFile.close();
            system("dot -Tpng listaCaracteres.dot -o listaCaracteres.png");
            system("shotwell listaCaracteres.png");

            /*PARA UTILIZAR EN WINDOWS
            const char* cmdCrear="dot -Tpng caracteres.dot -o ListaCaracteres.png";
            const char* cmdExecute="cmd /c start ListaCaracteres.png";
            system(cmdCrear);
            system(cmdExecute);
            */
        }
    }
};

/*
int main()
{
    ListCharacters* list = new ListCharacters();
    list->addNode('a');
    list->addNode('b');
    list->addNode('c');
    list->addNode('d');
    list->addNode('e');
    list->addNode('f');
    list->addNode('g');
    list->addNode('h');
    cout<<"\n";
    list->showList();
    list->graphList();

    list->deleteNode();
    cout<<"DESPUES DE ELIMINAR\n";
    list->showList();
    return 0;
}*/
