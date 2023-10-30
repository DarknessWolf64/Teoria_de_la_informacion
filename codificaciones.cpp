// librerias
#include <string.h>
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>
#include <bitset>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

using namespace std;
int entriopia[200];

// estructura para enviar los archivos de codificacion cesar y a doble linea
struct datos
{
    int cabeza;
    pair<int, bitset<8>> par;
    struct datos *sig;
};

struct datos *raiz = NULL;
struct datos *fondo = NULL;

//estrucutra para enviar los archivos de huffman y shannon-fano
struct datos_A
{
    int cabeza;
    pair<int, string> par;
    struct datos_A *sigA;
};

struct datos_A *raizA = NULL;
struct datos_A *fondoA = NULL;

// Definicion de un nodo en el arbol de Huffman
struct huffman {
    int numero;
    int frecuencia;
    huffman* izquierda;
    huffman* derecha;

    huffman(int num, int freq) : numero(num), frecuencia(freq), izquierda(nullptr), derecha(nullptr) {}
};

// Funcion de comparacion para la cola de prioridad
struct CompararHojas {
    bool operator()(huffman* const& a, huffman* const& b) {
        return a->frecuencia > b->frecuencia;
    }
};

//estructura para el cifrado shannon-fano
struct shannon_fano {
    int valor;
    int frec;
    string codigo;
};

// prototipos para el diagrama
void fuente(string cadena);
void trasnmisor(string cadena);
void canalB(const pair<int, bitset<8>> &par, int num, int rnum);
void canalA(const pair<int, string> &par, int num, int rnum);
void receptor(int tam);
void destino(string cadena);

// prototipos para el almacenamiento de los datos
int vaciaB();
void insertarB(const pair<int, bitset<8>> &par, int cabeza);
void extraerB(pair<int, bitset<8>> &par, int &cabeza);
int vaciaA();
void insertarA(const pair<int, string> &par, int cabeza);
void extraerA(pair<int, string> &par, int &cabeza);

//prototipos para la codificacion huffman
void generarCodigosHuffman(huffman* raiz, string codigo, map<int, string>& codigosHuffman);
huffman* construirArbolHuffman(int numeros[], map<int, int>& frecuencias, int n);
string codificacion_huffman(int numeros[], int n, map<int, string>& codigosHuffman);

//prototipos para la codificacion shannon-fano
void ShannonFano(vector<shannon_fano>& puntero, int inicio, int final, const string& hoja);
string codificacion_shannon_fano(const vector<shannon_fano>& hojas, const int asciiB[], int tam);
void decodificacion_shannon_fano(const string& codificacion, const vector<shannon_fano>& hojas, int tam, int ascii[]);
void receptor_shannon_fano(const vector<shannon_fano>& hojas, int tam);

//prototipos para el codificador cesar
bitset<8>* codificacionCesar(const bitset<8> cesarbinarios[],int tam_cesar, int tam_binarios, const bitset<8> binarios[]);
bitset<8>* decodificacionCesar(const bitset<8> cesarbinarios[],int tam_cesar, int tam_binarios, const bitset<8> binarios[]);
void receptor_cesar(const bitset<8> cesarbinarios[],int tam_cesar, int tam);

//prototipos para el codificador a doble linea
bitset<8>* codificacionaDobleLinea(const bitset<8> mitadinicio[],const bitset<8> mitadfinal[],int medio, int tam, const bitset<8> binarios[]);
bitset<8>* decodificacionaDobleLinea(const bitset<8> mitadinicio[],const bitset<8> mitadfinal[],int medio, int tam, const bitset<8> binarios[]);
void receptor_doble_linea(const bitset<8> mitadinicio[],const bitset<8> mitadfinal[],int medio, int tam);

int main()
{
    // fuente que se va enviar en este caso un mensaje
    string cadena;

    cout << "Ingresa la cadena a enviar: ";
    getline(cin, cadena);
    cout << " " << endl;
    // el trasnmisor utilizado es una encriptacion en cesar
    fuente(cadena);

    return 0;
}

void fuente(string cadena)
{
    cout << "El mansaje fue enviado" << endl;

    trasnmisor(cadena);
}

void trasnmisor(string cadena)
{
    char cifrador[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','?','=','$'};

    int tam = cadena.size();
    char letras[tam];
    bitset<8> binarios[tam];
    pair<int, bitset<8>> pares[tam];
    int numeroPaquetes = 4;
    pair<int, string> paresA[numeroPaquetes];

    //codificacion huffman
    map<int, int> frecuencias;
    map<int, string> codigosHuffman;
    huffman* raiz;

    //codificacion shannon-fano
    int asciiB[tam];
    vector<shannon_fano> hojas;
    set<char> processedLetters;
    string codificado;
    int tamanoCadena;
    int tamanoPaquete;
    int residuo;
    string paquetes[numeroPaquetes];
    int inicio = 0;
    int fin = 0;
    
    //codificacion cesar
    int tam_cifrado = sizeof(cifrador)/sizeof(cifrador[0]);
    bitset<8> cifrador_binario[tam_cifrado];
    bitset<8>* datosCifrados_cesar;
    

    //cifrado a doble linea
    bitset<8>* datosCifrados_dobleLinea;
    int medio = tam_cifrado/2;
    bitset<8> mitadinicio[medio];
    bitset<8> mitadfinal[medio];
        
    for (int i=0;i<tam;i++)
    {
        for (int j=0;j<sizeof(cifrador)/sizeof(cifrador[0]);j++)
        {
            if (cifrador[j] == cadena[i]) {letras[i] = cifrador[j + 3];}
        }
    }

    for(int i=0;i<tam_cifrado;i++){
        cifrador_binario[i] = bitset<8>(cifrador[i]);
    }

    //genera un numero al azar para el tipo de canal entre los 6 que hay
    srand(time(NULL));
    int num = rand() % 6 + 1;
    
    for (int x=0;x<tam;x++) {
        bitset<8> binario(letras[x]);
        binarios[x] = binario;
    }

    //eleccion de codificacion
    //int ele = rand() % 4 + 1;
    int ele = 1;

    switch(ele){
        case 1:
        cout << "HUFFMAN" << endl;

        //conversion de binarios a ascii
        for (int i = 0; i < tam; i++) {
            asciiB[i] = static_cast<int>(binarios[i].to_ulong());
        }

        // Calcular las frecuencias
        for (int i = 0; i < tam; ++i) {
            frecuencias[asciiB[i]]++;
        }

        raiz = construirArbolHuffman(asciiB, frecuencias, tam);
        generarCodigosHuffman(raiz, "", codigosHuffman);

        codificado = codificacion_huffman(asciiB,tam,codigosHuffman);
        cout << "Codificacion del arreglo original: " << codificado << "\n";
        break;
        
        case 2:
        cout << "SHANNON-FANO" << endl;
        //conversion de binarios a ascii
        for (int i = 0; i < tam; i++) {
            asciiB[i] = static_cast<int>(binarios[i].to_ulong());
        }

        //para buscar valor y frecuencia repetida
        for (int i = 0; i < tam; i++) {
            if (processedLetters.count(letras[i]) == 0) {
                // Si la letra no se ha procesado antes, agrega su información a hojas
                hojas.push_back({asciiB[i], count(asciiB, asciiB + tam, asciiB[i]), ""});
                processedLetters.insert(letras[i]);
            }
        }

        // Ordenar por frecuencia
        sort(hojas.begin(), hojas.end(), [](const shannon_fano& a, const shannon_fano& b) {
            return a.frec > b.frec;
        });

        ShannonFano(hojas, 0, hojas.size() - 1, "");

        codificado = codificacion_shannon_fano(hojas, asciiB, tam);

        for (int x=0;x<1;x++) {
        int rnum = rand() % 2 + 1;
        entriopia[x] = rnum;
        paresA[x] = make_pair(x,codificado);
        canalA(paresA[x], num, rnum);
        }

        break;

        case 3:
        cout << "CODIFICACION CESAR - INVENTADA" << endl;
        datosCifrados_cesar = codificacionCesar(cifrador_binario,tam_cifrado,tam,binarios);
        
        for (int x=0;x<tam;x++) {
        int rnum = rand() % 2 + 1;
        entriopia[x] = rnum;
        pares[x] = make_pair(x,datosCifrados_cesar[x]);
        canalB(pares[x], num, rnum);
        }
        break;

        case 4:
        cout << "CODIFICACION A DOBLE LINEA - INVENTADA" << endl;
        for (int i = 0; i < tam_cifrado; i++) {
            if (i < medio) {
                mitadinicio[i] = cifrador_binario[i];
            } else {
                mitadfinal[i - medio] = cifrador_binario[i];
            }
        }
        datosCifrados_dobleLinea = codificacionaDobleLinea(mitadinicio,mitadfinal,medio,tam,binarios);

        for (int x=0;x<tam;x++) {
        int rnum = rand() % 2 + 1;
        entriopia[x] = rnum;
        pares[x] = make_pair(x,datosCifrados_dobleLinea[x]);
        canalB(pares[x], num, rnum);
        }

        break;

        default: cout << "CODIFICACION NO ENCONTRADA" << endl;
    }

    int umbral[] = {2};
    int tam_entriopia = sizeof(entriopia)/sizeof(entriopia[0]);
    int tam_umbral = sizeof(umbral)/sizeof(umbral[0]);
    double valor_entriopia = 0.0;
    double probabilidad = 1.0/tam_entriopia;

    for(int i=0;i<tam_entriopia;i++){
        for(int j=0;j<tam_umbral;j++){
            if(entriopia[i]==umbral[j]){
                valor_entriopia -= probabilidad * log2(probabilidad);
            }
            else{
                valor_entriopia -= 0 * log2(probabilidad);
            }
        }
    }
    cout << "\nLa entriopia de los ruidos es: " << valor_entriopia << endl;
    //receptor(tam);
    if(ele == 1){}
    if(ele == 2){receptor_shannon_fano(hojas,tam);}
    if(ele == 3){receptor_cesar(cifrador_binario,tam_cifrado,tam);}
    if(ele == 4){receptor_doble_linea(mitadinicio,mitadfinal,medio,tam);}
}

//canal para codificacion huffman y shannon fano
void canalA(const pair<int, string> &par, int num, int rnum)
{
    srand(time(NULL));
    int velocidad = 0;

    switch (num)
    {

    case 1:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        break;

    case 2:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i< 10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        break;

    case 3:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        break;

    case 4:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        break;

    case 5:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        break;

    case 6:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarA(par, par.first);
        }
        break;
    }
}

//canal para codifcador cesar y codificador a doble linea
void canalB(const pair<int, bitset<8>> &par, int num, int rnum)
{
    srand(time(NULL));
    int velocidad = 0;

    switch (num)
    {

    case 1:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        break;

    case 2:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i< 10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        break;

    case 3:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        break;

    case 4:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        break;

    case 5:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        break;

    case 6:
        if (rnum == 1)
        {
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for (int i=0;i<10;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertarB(par, par.first);
        }
        break;
    }
}

void destino(string cadena){
    cout << "El mensaje recibido fue el siguiente: " << cadena << endl;
}

// para la estrucutura A
int vaciaA()
{
    if (raizA == NULL)
        return 1;
    else
        return 0;
}

void insertarA(const pair<int, string> &par, int cabeza)
{
    struct datos_A *nuevoA = new datos_A;
    nuevoA->par = par;
    nuevoA->cabeza = cabeza;
    nuevoA->sigA = NULL;
    if (vaciaA())
    {
        raizA = nuevoA;
        fondoA = nuevoA;
    }
    else
    {
        fondoA->sigA = nuevoA;
        fondoA = nuevoA;
    }
}

void extraerA(pair<int, string> &par, int &cabeza)
{
    if (!vaciaA())
    {
        par = raizA->par;
        cabeza = raizA->cabeza;
        struct datos_A *bor = raizA;
        if (raizA == fondoA)
        {
            raizA = NULL;
            fondoA = NULL;
        }
        else
        {
            raizA = raizA->sigA;
        }
        delete bor;
    }
    else
    {
        par = make_pair(-1, string());
        cabeza = -1;
    }
}

// para la estructura B
int vaciaB()
{
    if (raiz == NULL)
        return 1;
    else
        return 0;
}

void insertarB(const pair<int, bitset<8>> &par, int cabeza)
{
    struct datos *nuevo = new datos;
    nuevo->par = par;
    nuevo->cabeza = cabeza;
    nuevo->sig = NULL;
    if (vaciaB())
    {
        raiz = nuevo;
        fondo = nuevo;
    }
    else
    {
        fondo->sig = nuevo;
        fondo = nuevo;
    }
}

void extraerB(pair<int, bitset<8>> &par, int &cabeza)
{
    if (!vaciaB())
    {
        par = raiz->par;
        cabeza = raiz->cabeza;
        struct datos *bor = raiz;
        if (raiz == fondo)
        {
            raiz = NULL;
            fondo = NULL;
        }
        else
        {
            raiz = raiz->sig;
        }
        delete bor;
    }
    else
    {
        par = make_pair(-1, bitset<8>());
        cabeza = -1;
    }
}

//codificacion Huffman
// Generar codigos de Huffman y almacenarlos en un mapa
void generarCodigosHuffman(huffman* raiz, string codigo, map<int, string>& codigosHuffman) {
    if (!raiz)
        return;

    if (raiz->numero != -1)
        codigosHuffman[raiz->numero] = codigo;

    generarCodigosHuffman(raiz->izquierda, codigo + "0", codigosHuffman);
    generarCodigosHuffman(raiz->derecha, codigo + "1", codigosHuffman);
}

// Construir el arbol de Huffman
huffman* construirArbolHuffman(int numeros[], map<int, int>& frecuencias, int n) {
    priority_queue<huffman*, vector<huffman*>, CompararHojas> minHeap;

    for (int i = 0; i < n; ++i) {
        minHeap.push(new huffman(numeros[i], frecuencias[numeros[i]]));
    }

    while (minHeap.size() > 1) {
        huffman* izquierda = minHeap.top();
        minHeap.pop();

        huffman* derecha = minHeap.top();
        minHeap.pop();

        huffman* nuevoNodo = new huffman(-1, izquierda->frecuencia + derecha->frecuencia);
        nuevoNodo->izquierda = izquierda;
        nuevoNodo->derecha = derecha;
        minHeap.push(nuevoNodo);
    }

    return minHeap.top();
}

// Codificacion huffman
string codificacion_huffman(int numeros[], int n, map<int, string>& codigosHuffman) {
    string textoCodificado = "";
    for (int i = 0; i < n; ++i) {
        textoCodificado += codigosHuffman[numeros[i]];
    }
    return textoCodificado;
}

//codificacion shannon_fano
void ShannonFano(vector<shannon_fano>& puntero, int inicio, int final, const string& hoja = ""){
    if (inicio == final) {
        puntero[inicio].codigo = hoja;
        return;
    }

    int sum = 0;
    for (int i = inicio; i <= final; i++) {
        sum += puntero[i].frec ;
    }

    sum /= 2;
    int i, sum2 = puntero[inicio].frec;

    for (i = inicio + 1; i <= final && abs(sum - (sum2 + puntero[i].frec)) < abs(sum - sum2); i++) {
        sum2 += puntero[i].frec;
    }

    ShannonFano(puntero, inicio, i - 1, hoja + "0");
    ShannonFano(puntero, i, final, hoja + "1");
}


string codificacion_shannon_fano(const vector<shannon_fano>& hojas, const int asciiB[], int tam) {
    string codificado;

    for (int i = 0; i < tam; i++) {
        for (size_t j = 0; j < hojas.size(); j++) {
            if (asciiB[i] == hojas[j].valor) {
                codificado += hojas[j].codigo;
                break;
            }
        }
    }

    return codificado;
}

void decodificacion_shannon_fano(const string& codificacion, const vector<shannon_fano>& hojas, int tam, int ascii[]){
    int ind = 0;
    int asciiInd = 0;
    while (ind < codificacion.size()) {
        for (const shannon_fano& caracter : hojas) {
            if (codificacion.find(caracter.codigo, ind) == ind) {
                ascii[asciiInd] = caracter.valor;
                asciiInd++;
                ind += caracter.codigo.size();
                break;
            }
        }
    }
}

void receptor_shannon_fano(const vector<shannon_fano>& hojas, int tam)
{
    char cifrador[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','?','=','$'};

    char letras_convertidas[50];
    char letras[50];
    string palabra;
    string paquete;
    pair<int, string> paresExtraidos[tam];

    int x = 0;
    while (!vaciaA())
    {
        pair<int, string> extraccion_par;
        int extraccion_cabeza;
        extraerA(extraccion_par, extraccion_cabeza);
        paquete = extraccion_par.second;
        x++;
    }
    int asciidecodificado[tam];
    decodificacion_shannon_fano(paquete,hojas,tam,asciidecodificado);

    for(int i=0;i<tam;i++){
        letras_convertidas[i] = static_cast<char>(asciidecodificado[i]);
    }

    string cadena(letras_convertidas);


    for (int i=0;i<tam;i++)
    {
        for (int j=0;j<sizeof(cifrador)/sizeof(cifrador[0]);j++)
        {
            if (cifrador[j] == cadena[i]) {letras[i] = cifrador[j - 3];}
        }
    }

    for (int k = 0; k < tam; k++)
    {
        palabra.push_back(letras[k]);
    }

    string descifrado = palabra;
    destino(descifrado);

}


//codificacion cesar
bitset<8>* codificacionCesar(const bitset<8> cesarbinarios[],int tam_cesar, int tam_binarios, const bitset<8> binarios[]){
    bitset<8>* datosCifrados = new bitset<8>[tam_binarios];

    for (int i=0;i<tam_binarios;i++)
    {
        for (int j=0;j<tam_cesar;j++)
        {
            if (cesarbinarios[j] == binarios[i]) {datosCifrados[i] = cesarbinarios[j + 3];}
        }
    }

    return datosCifrados;
}

bitset<8>* decodificacionCesar(const bitset<8> cesarbinarios[],int tam_cesar, int tam_binarios, const bitset<8> binarios[]){
    bitset<8>* datosDescifrados = new bitset<8>[tam_binarios];

    for (int i=0;i<tam_binarios;i++)
    {
        for (int j=0;j<tam_cesar;j++)
        {
            if (cesarbinarios[j] == binarios[i]) {datosDescifrados[i] = cesarbinarios[j - 3];}
        }
    }

    return datosDescifrados;
}

void receptor_cesar(const bitset<8> cesarbinarios[],int tam_cesar, int tam)
{
    char cifrador[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','?','=','$'};

    char letras_convertidas[50];
    char letras[50];
    string palabra;
    bitset<8> binarios[tam];
    pair<int, bitset<8>> paresExtraidos[tam];

    int x = 0;
    while (!vaciaB())
    {
        pair<int, bitset<8>> extraccion_par;
        int extraccion_cabeza;
        extraerB(extraccion_par, extraccion_cabeza);
        binarios[x] = extraccion_par.second;
        x++;
    }

    bitset<8>* datosDescifrados = decodificacionCesar(cesarbinarios,tam_cesar,tam,binarios);

    for(int k=0;k<tam;k++){
        letras_convertidas[k] = static_cast<char>(datosDescifrados[k].to_ulong());
    }

    string cadena(letras_convertidas);


    for (int i=0;i<tam;i++)
    {
        for (int j=0;j<sizeof(cifrador)/sizeof(cifrador[0]);j++)
        {
            if (cifrador[j] == cadena[i]) {letras[i] = cifrador[j - 3];}
        }
    }

    for (int k = 0; k < tam; k++)
    {
        palabra.push_back(letras[k]);
    }

    string descifrado = palabra;
    destino(descifrado);
}

//codificacion a doble linea
bitset<8>* codificacionaDobleLinea(const bitset<8> mitadinicio[],const bitset<8> mitadfinal[],int medio, int tam, const bitset<8> binarios[]){
    bitset<8>* datosCifrados = new bitset<8>[tam];
    
    for (int i=0;i<tam;i++)
    {
        for (int j=0;j<medio;j++)
        {
            if(mitadinicio[j] == binarios[i]){
                datosCifrados[i] = mitadfinal[j]; 
            }
            if(mitadfinal[j] == binarios[i]){
                datosCifrados[i] = mitadinicio[j];
            }
        }
    }

    return datosCifrados;
}

bitset<8>* decodificacionaDobleLinea(const bitset<8> mitadinicio[],const bitset<8> mitadfinal[],int medio, int tam, const bitset<8> binarios[]){
    bitset<8>* datosDescifrados = new bitset<8>[tam];
    
    for (int i=0;i<tam;i++)
    {
        for (int j=0;j<medio;j++)
        {
            if(mitadinicio[j] == binarios[i]){
                datosDescifrados[i] = mitadfinal[j]; 
            }
            if(mitadfinal[j] == binarios[i]){
                datosDescifrados[i] = mitadinicio[j];
            }
        }
    }
    return datosDescifrados;
}

void receptor_doble_linea(const bitset<8> mitadinicio[],const bitset<8> mitadfinal[],int medio, int tam){
    char cifrador[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','?','=','$'};

    char letras_convertidas[50];
    char letras[50];
    string palabra;
    bitset<8> binarios[tam];
    pair<int, bitset<8>> paresExtraidos[tam];

    int x = 0;
    while (!vaciaB())
    {
        pair<int, bitset<8>> extraccion_par;
        int extraccion_cabeza;
        extraerB(extraccion_par, extraccion_cabeza);
        binarios[x] = extraccion_par.second;
        x++;
    }

    bitset<8>* datosDescifrados = decodificacionaDobleLinea(mitadinicio,mitadfinal,medio,tam,binarios);

    for(int k=0;k<tam;k++){
        letras_convertidas[k] = static_cast<char>(datosDescifrados[k].to_ulong());
    }

    string cadena(letras_convertidas);


    for (int i=0;i<tam;i++)
    {
        for (int j=0;j<sizeof(cifrador)/sizeof(cifrador[0]);j++)
        {
            if (cifrador[j] == cadena[i]) {letras[i] = cifrador[j - 3];}
        }
    }

    for (int k = 0; k < tam; k++)
    {
        palabra.push_back(letras[k]);
    }

    string descifrado = palabra;
    destino(descifrado);
}