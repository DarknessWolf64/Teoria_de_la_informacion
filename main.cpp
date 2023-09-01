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

using namespace std;

<<<<<<< HEAD
// estructura para enviar los archivos
struct datos
{
    int cabeza;
    pair<int, bitset<8>> par;
    struct datos *sig;
=======
//estructura para enviar los archivos
struct datos {
    int cabeza;
    pair<int, bitset<8>> par;
    struct datos* sig;
>>>>>>> a31fa2ea4acfde985ca1a3f7810843ca32a1191d
};

struct datos *raiz = NULL;
struct datos *fondo = NULL;

<<<<<<< HEAD
// prototipos para el diagrama
void fuente(string cadena);
void trasnmisor(string cadena);
void canal(const pair<int, bitset<8>> &par, int rnum);
void receptor(int tam);
void destino(string cadena);

// prototipos para el almacenamiento de los datos
int vacia();
void insertar(const pair<int, bitset<8>> &par, int cabeza);
void extraer(pair<int, bitset<8>> &par, int &cabeza);
=======

//prototipos para el diagrama
void fuente(string cadena);
void trasnmisor(string cadena);
void canal(const pair<int, bitset<8>>& par, int rnum);
void receptor(string cadena);
void destino(string cadena);

//prototipos para el almacenamiento de los datos
int vacia();
void insertar(const pair<int, bitset<8>>& par, int cabeza);
void extraer(pair<int, bitset<8>>& par, int& cabeza);
>>>>>>> a31fa2ea4acfde985ca1a3f7810843ca32a1191d

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

<<<<<<< HEAD
void trasnmisor(string cadena)
{
    char cifrador[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','?','=','$'};

    int tam = cadena.size();
    char letras[50];
    pair<int, bitset<8>> pares[tam];

    for (int i=0;i<tam;i++)
    {
        for (int j=0;j<sizeof(cifrador)/sizeof(cifrador[0]);j++)
        {
            if (cifrador[j] == cadena[i]) {letras[i] = cifrador[j + 3];}
        }
    }
=======
void trasnmisor(string cadena){
    char mayusculas[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char minusculas[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    int tam = cadena.size();
    string palabra;
    char letras[50];
    pair<int, bitset<8>> pares[tam];
    bool envio = false;

    for(int i=0;i<tam;i++){
        for(int j=0;j<26;j++){
            if(minusculas[j] == cadena[i]){
                letras[i] = minusculas[j + 3];
            }
            else if(mayusculas[j] == cadena[i]){
                letras[i] = mayusculas[j + 3];
            }
        }
    }
    
    for(int k=0;k<tam;k++){
        palabra.push_back(letras[k]);
    }
>>>>>>> a31fa2ea4acfde985ca1a3f7810843ca32a1191d

    //genera un numero al azar para el tipo de canal entre los 6 que hay
    srand(time(NULL));
    int num = rand() % 6 + 1;
    
    for (int x=0;x<tam;x++) {
        bitset<8> binario(letras[x]);
        pares[x] = make_pair(x, binario);
        canal(pares[x], num);
    }

    //implementar una lista que solo saque las bits y enviarlos al receptor y hacer el cambio de bits a letras y juntarlos en una cadena para su desciframiento.
    
    cout << "\nExtrayendo elementos:" << endl;
    while (!vacia()) {
        pair<int, bitset<8>> extraccion_par;
        int extraccion_cabeza;
        extraer(extraccion_par, extraccion_cabeza);

        cout << "Cabeza: " << extraccion_cabeza << ", Par contenido: {" << extraccion_par.second.to_string() << "}" << endl;
    }

    string cifrado = palabra;
    cout << "\n" << cifrado << endl;
}

void canal(const pair<int, bitset<8>>& par, int num){
    // regresar solo el mensaje y implementar que el ruido sea enviado en lugar de generarlo aqui
    int letras[50];

    srand(time(NULL));
    int rnum = rand() % 3 + 1;
    int velocidad = 0;

<<<<<<< HEAD
    //envio de informacion por el canal previamente elegido de manera aleatoria
    for (int x=0;x<tam;x++)
    {
        bitset<8> binario(letras[x]); //se convierte a binario la letra
        pares[x] = make_pair(x, binario); //se hace paquete de 2
        canal(pares[x], num);
        cout << "-----------------------------------------------------------------------------" << endl;
    }

    receptor(tam);
=======
    switch(num){

        case 1:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        break;

        case 2:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        break;

        case 3:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        break;

        case 4:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        break;

        case 5:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        break;

        case 6:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par,par.first);
        }break;
    }

>>>>>>> a31fa2ea4acfde985ca1a3f7810843ca32a1191d
}

void canal(const pair<int, bitset<8>> &par, int num)
{
    srand(time(NULL));
    int rnum = rand() % 3 + 1;
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
            insertar(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
        }
        else if (rnum == 3)
        {
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for (int i=0;i<30;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
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
            insertar(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
        }
        else if (rnum == 3)
        {
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for (int i=0;i<30;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
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
            insertar(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
        }
        else if (rnum == 3)
        {
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for (int i=0;i<30;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
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
            insertar(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
        }
        else if (rnum == 3)
        {
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for (int i=0;i<30;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
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
            insertar(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
        }
        else if (rnum == 3)
        {
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for (int i=0;i<30;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
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
            insertar(par, par.first);
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
        }
        else if (rnum == 3)
        {
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for (int i=0;i<30;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first);
        }
        break;
    }
}

void receptor(int tam)
{
    char cifrador[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','?','=','$'};

    char letras_convertidas[50];
    char letras[50];
<<<<<<< HEAD
    string palabra;
    pair<int, bitset<8>> paresExtraidos[tam];

    int x = 0;
    while (!vacia())
    {
        pair<int, bitset<8>> extraccion_par;
        int extraccion_cabeza;
        extraer(extraccion_par, extraccion_cabeza);
        letras_convertidas[x] = static_cast<char>(extraccion_par.second.to_ulong());
        x++;
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
=======
    int tam = cadena.size();
    string palabra;
    
    for(int i=0;i<tam;i++){
        for(int j=0;j<26;j++){
            if(minusculas[j] == cadena[i]){
                letras[i] = minusculas[j - 3];
            }
            else if(mayusculas[j] == cadena[i]){
                letras[i] = mayusculas[j - 3];
            }
        }
    }
    
    for(int k=0;k<tam;k++){
>>>>>>> a31fa2ea4acfde985ca1a3f7810843ca32a1191d
        palabra.push_back(letras[k]);
    }

    string descifrado = palabra;
    destino(descifrado);
}

<<<<<<< HEAD
void destino(string cadena){
    cout << "El mensaje recibido fue el siguiente: " << cadena << endl;
}

// para la estructura
int vacia()
{
    if (raiz == NULL)
        return 1;
    else
        return 0;
}

void insertar(const pair<int, bitset<8>> &par, int cabeza)
{
    struct datos *nuevo = new datos;
    nuevo->par = par;
    nuevo->cabeza = cabeza;
    nuevo->sig = NULL;
    if (vacia())
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

void extraer(pair<int, bitset<8>> &par, int &cabeza)
{
    if (!vacia())
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
=======
// para la estructura
int vacia() {
    if (raiz == NULL)
        return 1;
    else
        return 0;
}

void insertar(const pair<int, bitset<8>>& par, int cabeza) {
    struct datos *nuevo = new datos;
    nuevo->par = par;
    nuevo->cabeza = cabeza;
    nuevo->sig = NULL;
    if (vacia()) {
        raiz = nuevo;
        fondo = nuevo;
    } else {
        fondo->sig = nuevo;
        fondo = nuevo;
    }
}

void extraer(pair<int, bitset<8>>& par, int& cabeza) {
    if (!vacia()) {
        par = raiz->par;
        cabeza = raiz->cabeza;
        struct datos *bor = raiz;
        if (raiz == fondo) {
            raiz = NULL;
            fondo = NULL;
        } else {
            raiz = raiz->sig;
        }
        delete bor;
    } else {
>>>>>>> a31fa2ea4acfde985ca1a3f7810843ca32a1191d
        par = make_pair(-1, bitset<8>());
        cabeza = -1;
    }
}