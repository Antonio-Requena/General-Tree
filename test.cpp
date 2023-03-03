#include <iostream>
#include "agen.h"
#include "agen_E-S.h"
#include "practica.h"

using namespace std;

typedef char tElto;
const tElto fin = '#';

int main()
{
    Agen <tElto> Arbolito;
    tElto x = 'b';

    ifstream fs("agen.dat");
    rellenarAgen(fs,Arbolito);
    fs.close();
    imprimirAgen(Arbolito);

    cout << "El grado del arbol es: " << grado(Arbolito) << endl;
    poda(Arbolito,x);
    imprimirAgen(Arbolito);
    

}