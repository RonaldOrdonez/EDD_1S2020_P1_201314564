#include <iostream>
using std::string;

// Prototipo de funciones
string aMinuscula(string cadena);
int main()
{
	string cadena = "HOLA";		
	string minuscula = aMinuscula(cadena);
	std::cout << "Minúscula: " + minuscula +"\n";
}

string aMinuscula(string cadena)
{
	for (int i = 0; i < cadena.length(); i++)
		cadena[i] = tolower(cadena[i]);
	return cadena;
}