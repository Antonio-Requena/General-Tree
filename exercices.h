#ifndef PRACTICA_H
#define PRACTICA_H

#include <algorithm>
#include "agen.h"

//EJERCICIO 1 GRADO DEL ARBOL
template <typename T>
int grado(const Agen<T>& A)
{
    if(A.arbolVacio())
        return -1;
    else
        return gradoRec(A.raiz(),A);
}

template<typename T>
int gradoRec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        int grado_Max = grado_nodo(n,A);
        int grado_aux;
        typename Agen<T>::nodo aux = A.hijoIzqdo(n);
        while (aux != Agen<T>::NODO_NULO)
        {
            grado_aux = gradoRec(aux,A);
            aux = A.hermDrcho(aux);
            grado_Max = std::max(grado_Max,grado_aux);
            
        }
        return grado_Max;
    }
}

template <typename T>
int grado_nodo(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int grado = 0;
    n = A.hijoIzqdo(n);
    while(n != Agen<T>::NODO_NULO)
    {
        grado++;
        n = A.hermDrcho(n);
    }
    return grado;
}

//EJERCICIO 2 PROFUNDIDAD NODO

template <typename T>
int profundidad_nodo(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int profundidad = 0;

    while(A.padre(n) != Agen<T>::NODO_NULO)
    { 
        profundidad++;
        n = A.padre(n);
    }
    return profundidad;
}

//ELERCICIO 3 DESEQUILIBRIO ARBOL GENERAL
template <typename T>
int desequilibrio_agen(const Agen<T>& A)
{
    int max = altura_agen(A);
    int min = altura_min(A);
    return max-min;
}

template <typename T>
int altura_agen(const Agen<T>& A)
{
    if(A.arbolVacio())
        return -1;
    else
        return alturaRec(A.raiz(),A) -1;
}

template <typename T>
int alturaRec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        int altura_Max = 0;
        int altura_aux;
        typename Agen<T>::nodo aux = A.hijoIzqdo(n);

        while(aux != Agen<T>::NODO_NULO)
        {
            altura_aux = alturaRec(aux,A);
            aux = A.hermDrcho(aux);
            altura_Max = std::max(altura_Max,altura_aux);
        } 
        return 1 + altura_Max;
    }
}

template <typename T>
int altura_min(const Agen<T>& A)
{
    if(A.arbolVacio())
        return -1;
    else
        return altura_minRec(A.raiz(),A);
}


template <typename T>
int altura_minRec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return profundidad_nodo(n,A) -1;
    else
    {
        int profundidad_min = 1;
        int profundidad_aux;
        typename Agen<T>::nodo aux = A.hijoIzqdo(n);

        while(aux != Agen<T>::NODO_NULO)
        {
            profundidad_aux = altura_minRec(aux,A);
            aux = A.hermDrcho(aux);
            profundidad_min = std::min(profundidad_min,profundidad_aux);
        } 
        return 1+ profundidad_min;
    }
}


//EJERCICIO 4
template <typename T>
typename Agen<T>::nodo buscar_elto(const Agen<T>& A, typename Agen<T>::nodo n, T& x)
{
    typename Agen<T>::nodo aux = Agen<T>::NODO_NULO;
    if (A.elemento(n) == x)
        aux = n;
    else
    {
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO)
        {
            aux = buscar_elto(A,n,x);
            n = A.hermDrcho(n);
        }
    }
    return aux;
}

template <typename T>
void eliminar_desc(Agen<T>& A, typename Agen<T>::nodo n)
{
    while(A.hijoIzqdo(n) != Agen<T>::NODO_NULO)
    {
        eliminar_desc(A,A.hijoIzqdo(n));
        A.eliminarHijoIzqdo(n);
    }
}

template <typename T>
void poda(Agen<T>& A, T x)
{
    if(!A.arbolVacio())
    {
        typename Agen<T>::nodo n;
        n = buscar_elto(A,A.raiz(),x);

        if (n != Agen<T>::NODO_NULO)
        {
            eliminar_desc(A,n);
            //Procedemos a eliminar el elemento
            if(A.padre(n)==Agen<T>::NODO_NULO)
                A.eliminarRaiz();
            else if (A.hijoIzqdo(A.padre(n)) == n)
                A.eliminarHijoIzqdo(A.padre(n));
            else
            {
                typename Agen<T>::nodo aux = A.hijoIzqdo(A.padre(n));
                while( aux != Agen<T>::NODO_NULO && n != Agen<T>::NODO_NULO )
                {
                    if(A.hermDrcho(aux) == n)
                    {
                        A.eliminarHermDrcho(aux);
                        n = Agen<T>::NODO_NULO;
                    }
                    else
                        aux = A.hermDrcho(aux);
                }

            }
        }
    }
}
#endif
