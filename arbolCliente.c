#include "arbolCliente.h"

/*************************************************************//**
*
* \brief Inicializa el arbol
* \return nodoArbol * NULL
*
*****************************************************************/
nodoArbol * inicArbol()
{
    return NULL;
}

/*************************************************************//**
*
* \brief genera un nodo y retorna su puntero
* \param dato con el/los cuales generar el nodo del arbol
* \return nodoArbol * puntero al nodo
*
*****************************************************************/
nodoArbol * crearNodoArbol(stCliente dato)
{
    nodoArbol * aux = (nodoArbol * ) malloc(sizeof( nodoArbol ) );
    aux->dato=dato;
    aux->der=NULL;
    aux->izq=NULL;

    return aux;
}

/*************************************************************//**
*
* \brief inserta el dato recibido en el arbol
* \param nodoArbol * puntero a la raiz del arbol
* \param stDatos dato dato a insertar en el arbol
* \return nodoArbol* nodo del arbol
*
*****************************************************************/
nodoArbol * insertarXNroCliente(nodoArbol * arbol, stCliente dato)
{
    if( arbol )
    {
        if( dato.nroCliente > arbol->dato.nroCliente )
        {
            arbol->der = insertarXNroCliente(arbol->der, dato);
        }
        else
        {
            arbol->izq = insertarXNroCliente(arbol->izq, dato);
        }
    }
    else
    {
        arbol = crearNodoArbol(dato);
    }

    return arbol;
}

nodoArbol* archivoCliente2arbol(char nombreArchivo[], nodoArbol* arbol){
    stCliente c;

    FILE *pArchCliente = fopen(nombreArchivo,"rb");

    if(pArchCliente)
    {
        while(fread(&c,sizeof(stCliente),1,pArchCliente) > 0)
        {
            arbol = insertarXNroCliente(arbol, c);
        }
        fclose(pArchCliente);
    }

    return arbol;
}

nodoArbol* archivoConsumo2arbol(char nombreArchivo[], nodoArbol* arbol){
    stConsumo c;

    FILE *pArchConsumos = fopen(nombreArchivo,"rb");

    if(pArchConsumos)
    {
        while(fread(&c,sizeof(stCliente),1,pArchConsumos) > 0)
        {
            arbol = insertarConsumoXIdCliente(arbol, c);
        }
        fclose(pArchConsumos);
    }

    return arbol;
}

nodoArbol* cargarArbolArchivos(char nombreArchivoCliente[], char nombreArchivoConsumo[] ,nodoArbol* arbol){
    arbol = archivoCliente2arbol(nombreArchivoCliente, arbol);
    arbol = archivoConsumo2arbol(nombreArchivoConsumo, arbol);
    return arbol;
}

/*************************************************************//**
*
* \brief busca un nodo por Nro de Cliente cuando no fue cargado bajo este parametro
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \param int nroCliente -  Nro de Cliente a buscar
* \return nodoArbol * rta puntero al nodo buscado
*
*****************************************************************/
nodoArbol* insertarConsumoXIdCliente(nodoArbol * arbol, stConsumo consumo)
{
    if (arbol)
    {
        if (arbol->dato.idCliente == consumo.idCliente)
        {
            arbol->consumos = agregarEnOrden(arbol->consumos, crearNodo(consumo)); //inserto consumo
        }
        else
        {
            insertarConsumoXIdCliente(arbol->izq,consumo);
            insertarConsumoXIdCliente(arbol->der,consumo);
        }
    }
}

/*************************************************************//**
*
* \brief Agrega un nodo al arbol
* \param nodoArbol* puntero a la raiz del arbol
* \param nodoArbol* puntero al nodo a agregar
* \return nodoArbol* nodo del arbol
*
*****************************************************************/
nodoArbol* agregarNodoArbol(nodoArbol* arbol, nodoArbol* nuevo){
    if(!arbol){
        arbol = nuevo;
    }else{
        if(nuevo->dato.nroCliente > arbol->dato.nroCliente){
            arbol->der = agregarNodoArbol(arbol->der, nuevo);
        }else{
            arbol->izq = agregarNodoArbol(arbol->izq, nuevo);
        }
    }
    return arbol;
}
/*************************************************************//**
*
* \brief muestra el contenido del arbol de cliente
* \param nodoArbol * puntero a la raiz del arbol
* \return void
*
*****************************************************************/
void mostrarArbolClientes(nodoArbol * arbol)
{
    if (arbol)
    {
        mostrarArbolClientes(arbol->izq);
        //mostrarCliente(arbol->dato);// adaptar nombre de la funcion
        mostrarArbolClientes(arbol->der);
    }
}

/*************************************************************//**
*
* \brief busca un nodo por Nro de Cliente
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \param int nroCliente -  Nro de Cliente a buscar
* \return nodoArbol * rta puntero al nodo buscado
*
*****************************************************************/
nodoArbol * buscarXNroCliente(nodoArbol * arbol,int nroCliente)
{
    nodoArbol * rta = NULL;

    if(arbol)
    {
        if(arbol->dato.nroCliente == nroCliente)
        {
            rta = arbol;
        }
        else
        {
            if(arbol->dato.nroCliente < nroCliente)
            {
                rta = buscarXNroCliente(arbol->der,nroCliente);
            }
            else
            {
                rta = buscarXNroCliente(arbol->izq,nroCliente);
            }
        }
    }

    return rta;
}

/*************************************************************//**
*
* \brief busca un nodo por Nro de Cliente cuando no fue cargado bajo este parametro
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \param int nroCliente -  Nro de Cliente a buscar
* \return nodoArbol * rta puntero al nodo buscado
*
*****************************************************************/
nodoArbol * buscarXNroClienteDiferido(nodoArbol * arbol,int nroCliente)
{
    nodoArbol * retorno = NULL;

    if (arbol)
    {
        if (arbol->dato.nroCliente == nroCliente)
        {
            retorno = arbol;
        }
        else
        {
            retorno = buscarXNroClienteDiferido(arbol->izq,nroCliente);
            if ( !retorno )
            {
                retorno = buscarXNroClienteDiferido(arbol->der,nroCliente);
            }
        }
    }

    return retorno;
}

/*************************************************************//**
*
* \brief cuenta la cantidad de elementos
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \return int contador -  cantidad de elementos del arbol
*
*****************************************************************/
int contarElementos(nodoArbol * arbol)
{
    int contador = 0;

    if (arbol)
    {
        contador += 1 + contarElementos(arbol->izq) + contarElementos(arbol->der);
    }

    return contador;
}

/*************************************************************//**
*
* \brief cuenta las terminales (u hojas del arbol)
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \return int cantidad de hojas
*
*****************************************************************/
int contarTerminales(nodoArbol * arbol)
{
    int retorno = 0;

    if (arbol)
    {
        if ( !(arbol->izq) && !(arbol->der) )
        {
            retorno += 1;
        }
        else
        {
            retorno += contarTerminales(arbol->izq);
            retorno += contarTerminales(arbol->der);
        }
    }

    return retorno;
}

/*************************************************************//**
*
* \brief cuenta los niveles (o altura) del arbol
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \return int cantidad de niveles
*
*****************************************************************/
int contarNiveles(nodoArbol * arbol)
{
    int nivel = 0;

    if (arbol)
    {
        if ( (arbol->izq) || (arbol->der) )
        {
            nivel += 1;
            int nivelIzq = contarNiveles(arbol->izq);
            int nivelDer = contarNiveles(arbol->der);

            if ( nivelIzq < nivelDer)
            {
                nivel += nivelDer;
            }
            else
            {
                nivel += nivelIzq;
            }
        }
    }

    return nivel;
}

/*************************************************************//**
*
* \brief busca un nodo y lo borra ( por numero de cliente)
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \param int nroCliente - numero de cliente a borrar
* \return nodoArbol * nuevo nodo raiz del arbol
*
*****************************************************************/
nodoArbol * borrarXNroCliente(nodoArbol * arbol,int nroCliente)
{
    if ( arbol )
    {
        if ( arbol->dato.nroCliente == nroCliente )
        {
            if ( arbol->izq )
            {
                nodoArbol * masDer = NMD(arbol->izq);
                arbol->dato = masDer->dato;
                arbol->izq = borrarXNroCliente(arbol->izq,masDer->dato.nroCliente);
            }
            else
            {
                if ( arbol->der )
                {
                    nodoArbol * masIzq = NMI(arbol->der);
                    arbol->dato = masIzq->dato;
                    arbol->der = borrarXNroCliente(arbol->der,masIzq->dato.nroCliente);
                }
                else
                {
                    free(arbol);
                    arbol = NULL;
                }
            }
        }
        else
        {
            if ( arbol->dato.nroCliente < nroCliente)
            {
                arbol->der = borrarXNroCliente(arbol->der,nroCliente);
            }
            else
            {
                arbol->izq = borrarXNroCliente(arbol->izq,nroCliente);
            }
        }
    }

    return arbol;
}

/*************************************************************//**
*
* \brief busca y retorna el nodo mas a la derecha del arbol
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \return nodoArbol * nodo mas a la derecha
*
*****************************************************************/
nodoArbol * NMD(nodoArbol * arbol)
{
    if (arbol->der)
    {
        arbol = NMD(arbol->der);
    }

    return arbol;
}

/*************************************************************//**
*
* \brief busca y retorna el nodo mas a la izq del arbol
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \return nodoArbol * nodo mas a la izq
*
*****************************************************************/
nodoArbol * NMI(nodoArbol * arbol)
{


    if (arbol->izq)
    {
        arbol = NMI(arbol->izq);
    }

    return arbol;
}

/*************************************************************//**
*
* \brief copia el contenido del arreglo en el arbol ordenando por nro de cliente
* \param nodoArbol * arbol - puntero a la raiz del arbol
* \param stCliente arr[] - arreglo
* \param int base - subindice en que inicia el arreglo (a la llamada va 0)
* \param int tope - subindice en que termina el arreglo (a la llamada va validos-1)
* \return nodoArbol * puntero al arbol cargado
*
*****************************************************************/
nodoArbol * arr2treeXNroCliente(nodoArbol * arbol,stCliente arr[],int base,int tope)
{
    int medio;

    if ( !(base<tope) )
    {
        medio = (base+tope)/2;
        arbol = insertarXNroCliente(arbol,arr[medio]);

        arbol = arr2treeXNroCliente(arbol,arr,base,medio-1);
        arbol = arr2treeXNroCliente(arbol,arr,medio+1,tope);
    }

    return arbol;
}
