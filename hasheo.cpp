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

// estructura para enviar todos los archivos
struct datos
{
    int cabeza;
    pair<int,string> par;
    struct datos *sig;
};

struct datos *raiz = NULL;
struct datos *fondo = NULL;

//estructura para los datos pasados por el canal 1
struct canal1
{
    int cabeza;
    pair<int,string> par;
    struct canal1 *sig1;
};

struct canal1 *raiz1 = NULL;
struct canal1 *fondo1 = NULL;

//estructura para los datos pasados por el canal 2
struct canal2
{
    int cabeza;
    pair<int,string> par;
    struct canal2 *sig2;
};

struct canal2 *raiz2 = NULL;
struct canal2 *fondo2 = NULL;

//estructura para los datos pasados por el canal 3
struct canal3
{
    int cabeza;
    pair<int,string> par;
    struct canal3 *sig3;
};

struct canal3 *raiz3 = NULL;
struct canal3 *fondo3 = NULL;

//estructura para el cifrado shannon-fano
struct shannon_fano {
    mutable string hash;
    int valor;
    int frec;
    string codigo;
};

// prototipos para el diagrama
void fuente(string cadena);
void trasnmisor(string cadena);
void canal(const pair<int, string> &par, int num, int rnum, int canal);
void receptor(const vector<shannon_fano>& hojas,int tam);
void destino(string cadena);
void pasarDatos();
void ordenarDatos();

//prototipos para la codificacion shannon-fano
void ShannonFano(vector<shannon_fano>& puntero, int inicio, int final, const string& hoja = "");
vector<string> codificacion_shannon_fano(const vector<shannon_fano>& hojas, const int asciiB[], int tam);
void mostrarCodigosShannonFano(const vector<shannon_fano>& hojas);
bitset<8> obtenerBinarioDesdeCodigo(const string& codigo, const vector<shannon_fano>& hojas);
vector<bitset<8>> decodificacion_shannon_fano(const vector<string>& codificaciones, const vector<shannon_fano>& hojas);

//para hasheo
void agregarHashAEstructura(const vector<shannon_fano>& hojas);
unsigned int Hash(const string& str);
void mostrarCodigosShannonFanoConHash(const vector<shannon_fano>& hojas);
void intercambiar(const shannon_fano& a, const shannon_fano& b);
vector<string> conversionHash(const vector<string>& codigos);
string busquedaBinaria(const vector<shannon_fano>& hojas, const string& Hash);
vector<string> buscarHashes(const vector<shannon_fano>& hojas, const vector<string>& hashes);

// prototipos para el almacenamiento de los datos
int vacia(int num);
void insertar(const pair<int, string> &par, int cabeza,int num);
void extraer(pair<int, string> &par, int &cabeza, int num);

int main()
{
    // fuente que se va enviar en este caso un mensaje
    string cadena;

    cout << "Ingresa la cadena a enviar: ";
    getline(cin, cadena);
    cout << " " << endl;
    // el trasnmisor utilizado es una encriptacion en cesar
    fuente(cadena);

    getch();
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
    char letras[50];
    pair<int, string> pares[tam];
    bitset<8> binarios[tam];
    bool envios[tam];
    float probPerdida1;
    float probPerdida2;
    float prob1;
    float prob2;
    int num_canal; 
    
    //codificacion shannon-fano
    int asciiB[tam];
    vector<shannon_fano> hojas;
    set<char> processedLetters;
    string codificado;

    for (int i=0;i<tam;i++)
    {
        for (int j=0;j<sizeof(cifrador)/sizeof(cifrador[0]);j++)
        {
            if (cifrador[j] == cadena[i]) {letras[i] = cifrador[j + 3];}
        }
    }

    //genera un numero al azar para el tipo de canal entre los 6 que hay
    srand(time(NULL));
    int num = rand() % 6 + 1;

    for (int x=0;x<tam;x++) {
        bitset<8> binario(letras[x]);
        binarios[x] = binario;
    }
    
    cout << endl << "SHANNON-FANO" << endl;
    //conversion de binarios a ascii
    for (int i = 0; i < tam; i++) {
        asciiB[i] = static_cast<int>(binarios[i].to_ulong());
    }

    // Cambia la parte que busca valores y frecuencias repetidas
    for (int i = 0; i < tam; i++) {
        if (processedLetters.count(letras[i]) == 0) {
            // Si la letra no se ha procesado antes, agrega su información a hojas
            hojas.push_back({ "", asciiB[i], count(asciiB, asciiB + tam, asciiB[i]), "" });
            processedLetters.insert(letras[i]);
        }
    }


    // Ordenar por frecuencia
    sort(hojas.begin(), hojas.end(), [](const shannon_fano& a, const shannon_fano& b) {
        return a.frec > b.frec;
    });

    ShannonFano(hojas, 0, hojas.size() - 1, "");
    
    mostrarCodigosShannonFano(hojas);
    
    vector<string> codificaciones = codificacion_shannon_fano(hojas, asciiB, tam);

    vector<string> hashes = conversionHash(codificaciones);

    cout << endl;
    
    for (int x=0;x<tam;x++) {
        int rnum = rand() % 2 + 1;
        entriopia[x] = rnum;
        pares[x] = make_pair(x, hashes[x]);
        num_canal = 1;
        if(num_canal == 1){
            probPerdida1 = 0.1;
            prob1 = static_cast<float>(rand()) / RAND_MAX;
            if(prob1<probPerdida1){
                cout << "-------------------------------------------------------------------------------------" << endl;
                cout << endl << "paquete fue enviado en el canal 1" << endl;
                canal(pares[x], num, rnum,num_canal);
                envios[x] = true;
            }
            else if(prob1>=probPerdida1){
                probPerdida2 = 0.35;
                prob2 = static_cast<float>(rand()) / RAND_MAX;
                if(prob2<probPerdida2){
                    cout << "-------------------------------------------------------------------------------------" << endl;
                    cout << "paquete rescatado con exito en el canal 2" << endl;
                    canal(pares[x], num, rnum,num_canal+1);
                    envios[x] = true;
                }
                else{
                    envios[x] = false;
                }
            }
        }
        num_canal = 2;
        if(num_canal == 2){
            if(envios[x] == false){
                probPerdida2 = 0.40;
                prob2 = static_cast<float>(rand()) / RAND_MAX;
                if(prob2<probPerdida2){
                    cout << "-------------------------------------------------------------------------------------" << endl;
                    cout << endl << "paquete fue enviado en el canal 2" << endl;
                    canal(pares[x], num, rnum,num_canal);
                    envios[x] = true;
                }
                else if(prob2>=probPerdida2){
                    cout << "-------------------------------------------------------------------------------------" << endl;
                    cout << "paquete rescatado con exito en el canal 3" << endl;
                    canal(pares[x],num,rnum,num_canal+1);
                }
            }
        }
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
    receptor(hojas,tam);
}

void canal(const pair<int, string> &par, int num, int rnum,int canal)
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
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
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
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
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
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
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
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
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
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
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
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
        }
        else if (rnum == 2)
        {
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for (int i=0;i<20;i++)
            {
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
            insertar(par, par.first,canal);
            cout << "-------------------------------------------------------------------------------------" << endl;
        }
        break;
    }
}

void receptor(const vector<shannon_fano>& hojas,int tam)
{
    char cifrador[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','?','=','$'};

    char letras_convertidas[50];
    vector<string> hashes;
    char letras[50];
    string palabra;
    pair<int, string> paresExtraidos[tam];
    int ascii[tam];

    int x = 0;

    pasarDatos();
    cout << endl;

    ordenarDatos();

    while (!vacia(4))
    {
        pair<int, string> extraccion_par;
        int extraccion_cabeza;
        string extraccion_hash; // Nuevo campo para almacenar el hash
        extraer(extraccion_par, extraccion_cabeza,4);
        hashes.push_back(extraccion_par.second); // Almacena el hash en el vector
        x++;
    }

    agregarHashAEstructura(hojas);

    cout << endl;
    
    mostrarCodigosShannonFanoConHash(hojas);

    cout << endl;

    // Algoritmo de ordenación de burbuja
    for (int i = 0; i < hojas.size(); i++) {
        for (int j = 0; j < hojas.size() - 1; j++) {
            // Comparar y intercambiar si es necesario
            if (hojas[j].hash > hojas[j + 1].hash) {
                intercambiar(hojas[j], hojas[j + 1]);
            }
        }
    }

    mostrarCodigosShannonFanoConHash(hojas);

    // Mostrar códigos encontrados
    cout << endl << "Hashes recibidos: ";
    for (const string& hash : hashes) {
        cout << hash << " ";
    }
    cout << endl;

    // Buscar códigos correspondientes a los hashes
    vector<string> codigosEncontrados = buscarHashes(hojas, hashes);

    // Mostrar códigos encontrados
    cout << endl << "Codigos encontrados: ";
    for (const string& codigo : codigosEncontrados) {
        cout << codigo << " ";
    }
    cout << endl;

    // Decodificación
    vector<bitset<8>> binariosDecodificados = decodificacion_shannon_fano(codigosEncontrados, hojas);

    // Mostrar binarios decodificados
    cout << endl << "Binarios decodificados: ";
    for (const bitset<8>& binario : binariosDecodificados) {
        cout << binario << " ";
    }
    cout << endl;

    int index = 0;

    for (const string& codigo : codigosEncontrados) {
        bitset<8> binario = obtenerBinarioDesdeCodigo(codigo, hojas);
        char caracter = static_cast<char>(binario.to_ulong());
        letras_convertidas[index++] = caracter;
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

void destino(string cadena){
    cout << endl << "El mensaje recibido fue el siguiente: " << cadena << endl;
}

// para la estructura
int vacia(int num)
{
    if(num == 1){
        if (raiz1 == NULL)
            return 1;
        else
            return 0;
    }

    else if(num == 2){
        if (raiz2 == NULL)
            return 1;
        else
            return 0;
    }

    else if(num == 3){
        if (raiz3 == NULL)
            return 1;
        else
            return 0;
    }

    else if(num == 4){
        if (raiz == NULL)
            return 1;
        else
            return 0;   
    }
}

void insertar(const pair<int, string> &par, int cabeza, int num)
{
    if(num == 1){
        struct canal1 *nuevo1 = new canal1;
        nuevo1->par = par;
        nuevo1->cabeza = cabeza;
        nuevo1->sig1 = NULL;
        if (vacia(num))
        {
            raiz1 = nuevo1;
            fondo1 = nuevo1;
        }
        else
        {
            fondo1->sig1 = nuevo1;
            fondo1 = nuevo1;
        }
    }

    else if(num == 2){
        struct canal2 *nuevo2 = new canal2;
        nuevo2->par = par;
        nuevo2->cabeza = cabeza;
        nuevo2->sig2 = NULL;
        if (vacia(num))
        {
            raiz2 = nuevo2;
            fondo2 = nuevo2;
        }
        else
        {
            fondo2->sig2 = nuevo2;
            fondo2 = nuevo2;
        }
    }

    else if(num == 3){
        struct canal3 *nuevo3 = new canal3;
        nuevo3->par = par;
        nuevo3->cabeza = cabeza;
        nuevo3->sig3 = NULL;
        if (vacia(num))
        {
            raiz3 = nuevo3;
            fondo3 = nuevo3;
        }
        else
        {
            fondo3->sig3 = nuevo3;
            fondo3 = nuevo3;
        }
    }

    else if(num == 4){
        struct datos *nuevo = new datos;
        nuevo->par = par;
        nuevo->cabeza = cabeza;
        nuevo->sig = NULL;
        if (vacia(num)) {
            raiz = nuevo;
            fondo = nuevo;
        } 
        else {
            fondo->sig = nuevo;
            fondo = nuevo;
        }
    }
}

void extraer(pair<int, string> &par, int &cabeza, int num) {
    if(num == 1){
        if (!vacia(num)) {
            par = raiz1->par;
            cabeza = raiz1->cabeza;
            struct canal1 *bor1 = raiz1;
            if (raiz1 == fondo1) {
                raiz1 = NULL;
                fondo1 = NULL;
            } 
            else {
                raiz1 = raiz1->sig1;
            }
            delete bor1;
        } 
        else {
            par = make_pair(-1, string());
            cabeza = -1;
        }
    }

    else if(num == 2){
        if (!vacia(num)) {
            par = raiz2->par;
            cabeza = raiz2->cabeza;
            struct canal2 *bor2 = raiz2;
            if (raiz2 == fondo2) {
                raiz2 = NULL;
                fondo2 = NULL;
            } 
            else {
                raiz2 = raiz2->sig2;
            }
            delete bor2;
        } 
        else {
            par = make_pair(-1, string());
            cabeza = -1;
        }
    }

    else if(num == 3){
        if (!vacia(num)) {
            par = raiz3->par;
            cabeza = raiz3->cabeza;
            struct canal3 *bor3 = raiz3;
            if (raiz3 == fondo3) {
                raiz3 = NULL;
                fondo3 = NULL;
            } 
            else {
                raiz3 = raiz3->sig3;
            }
            delete bor3;
        } 
        else {
            par = make_pair(-1, string());
            cabeza = -1;
        }
    }

    else if(num == 4){
        if (!vacia(num)) {
            par = raiz->par;
            cabeza = raiz->cabeza;
            struct datos *bor = raiz;
            if (raiz == fondo) {
                raiz = NULL;
                fondo = NULL;
            }
            else {
                raiz = raiz->sig;
            }
            delete bor;
        }
        else {
            par = make_pair(-1, string());
            cabeza = -1;
        }
    } 
}

//insertar los datos de cualquier canal a datos
void pasarDatos() {
    while (!vacia(1)) {
        pair<int, string> par;
        int cabeza;
        extraer(par, cabeza, 1); // Extraer desde canal 1
        insertar(par, cabeza, 4); // Insertar en datos
    }
    while (!vacia(2)) {
        pair<int, string> par;
        int cabeza;
        extraer(par, cabeza, 2); // Extraer desde canal 2
        insertar(par, cabeza, 4); // Insertar en datos
    }
    while(!vacia(3)){
        pair<int, string> par;
        int cabeza;
        extraer(par, cabeza, 3); // Extraer desde canal 3
        insertar(par, cabeza, 4); // Insertar en datos
    }
}

void ordenarDatos() {
    if (raiz == NULL) {
        cout << "La estructura está vacía, no hay datos para ordenar." << endl;
        return;
    }

    struct datos *actual = raiz, *temp;
    
    while (actual->sig != NULL) {
        struct datos *minimo = actual;
        struct datos *siguiente = actual->sig;

        while (siguiente != NULL) {
            // Comparar por el valor de cabeza
            if (siguiente->cabeza < minimo->cabeza) {
                minimo = siguiente;
            }

            siguiente = siguiente->sig;
        }

        // Intercambiar los datos si se encontró un mínimo
        if (minimo != actual) {
            // Intercambiar solo el valor de cabeza
            int tempCabeza = actual->cabeza;
            actual->cabeza = minimo->cabeza;
            minimo->cabeza = tempCabeza;
        }

        actual = actual->sig;
    }

    cout << "Datos ordenados por el valor de cabeza de menor a mayor." << endl;
}

//codificacion shannon_fano
void ShannonFano(vector<shannon_fano>& puntero, int inicio, int final, const string& hoja) {
    if (inicio == final) {
        puntero[inicio].codigo = hoja;
        return;
    }

    int sum = 0;
    for (int i = inicio; i <= final; i++) {
        sum += puntero[i].frec;
    }

    sum /= 2;
    int i, sum2 = puntero[inicio].frec;

    for (i = inicio + 1; i <= final && abs(sum - (sum2 + puntero[i].frec)) < abs(sum - sum2); i++) {
        sum2 += puntero[i].frec;
    }

    ShannonFano(puntero, inicio, i - 1, hoja + "0");
    ShannonFano(puntero, i, final, hoja + "1");
}

vector<string> codificacion_shannon_fano(const vector<shannon_fano>& hojas, const int asciiB[], int tam) {
    vector<string> codigos;

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < hojas.size(); j++) {
            if (asciiB[i] == hojas[j].valor) {
                codigos.push_back(hojas[j].codigo);
                break;
            }
        }
    }

    return codigos;
}

// Modificación de la función agregar los hashes a la estructura de shannon-fano
void agregarHashAEstructura(const vector<shannon_fano>& hojas) {
    for (int i = 0; i < hojas.size(); i++) {
        hojas[i].hash = to_string(Hash(hojas[i].codigo));
    }
}

void mostrarCodigosShannonFano(const vector<shannon_fano>& hojas) {
    cout << "Codigos Shannon-Fano: " << endl;
    for (const shannon_fano& nodo : hojas) {
        cout << "Valor: " << nodo.valor << " Frecuencia: " << nodo.frec
             << " Codigo: " << nodo.codigo << endl;
    }
}

bitset<8> obtenerBinarioDesdeCodigo(const string& codigo, const vector<shannon_fano>& hojas) {
    for (const shannon_fano& caracter : hojas) {
        if (caracter.codigo == codigo) {
            return bitset<8>(caracter.valor);
        }
    }
    cout << "Error: No se pudo encontrar el código correspondiente en las hojas." << endl;
    return bitset<8>();
}

vector<bitset<8>> decodificacion_shannon_fano(const vector<string>& codificaciones, const vector<shannon_fano>& hojas) {
    vector<bitset<8>> binarios;

    for (const string& codificacion : codificaciones) {
        int ind = 0; // Índice de la cadena codificada

        // Mientras haya caracteres en la cadena codificada
        while (ind < codificacion.size()) {
            bool encontrado = false;

            // Buscar el código correspondiente en las hojas
            for (const shannon_fano& caracter : hojas) {
                if (codificacion.find(caracter.codigo, ind) == ind) {
                    // Se encontró el código, obtener el valor binario y almacenarlo
                    binarios.push_back(obtenerBinarioDesdeCodigo(caracter.codigo, hojas));
                    ind += caracter.codigo.size();
                    encontrado = true;
                    break;
                }
            }

            // Manejar el caso en que no se encuentra el código (esto no debería ocurrir si la codificación es correcta)
            if (!encontrado) {
                cout << "Error: No se pudo encontrar un código válido en la posición " << ind << endl;
                break;
            }
        }
    }

    return binarios;
}

unsigned int Hash(const string& str) {
    hash<string> hasher;
    return hasher(str);
}

void intercambiar(const shannon_fano& a, const shannon_fano& b) {
    shannon_fano temp = a;
    const_cast<shannon_fano&>(a) = b;
    const_cast<shannon_fano&>(b) = temp;
}

void mostrarCodigosShannonFanoConHash(const vector<shannon_fano>& hojas) {
    cout << endl << "Codigos Shannon-Fano: " << endl;
    for (const shannon_fano& nodo : hojas) {
        cout << "Valor: " << nodo.valor << " Frecuencia: " << nodo.frec
             << " Codigo: " << nodo.codigo << " Hash: " << nodo.hash << endl;
    }
}

// Implementación de la nueva función
vector<string> conversionHash(const vector<string>& codigos) {
    vector<string> hashes;
    
    // Hashea cada código y agrega el resultado al vector de hashes
    for (const string& codigo : codigos) {
        unsigned int hash = Hash(codigo);
        hashes.push_back(to_string(hash));
    }

    return hashes;
}

string busquedaBinaria(const vector<shannon_fano>& hojas, const string& Hash) {
    int izquierda = 0;
    int derecha = hojas.size() - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (hojas[medio].hash == Hash) {
            // Se encontró el hash, devolver el código asociado
            return hojas[medio].codigo;
        }

        if (hojas[medio].hash < Hash) {
            // El hash está en la mitad derecha
            izquierda = medio + 1;
        } else {
            // El hash está en la mitad izquierda
            derecha = medio - 1;
        }
    }

    // El hash no se encontró en la estructura, devolver una cadena vacía o algún valor que indique que no se encontró
    return "";
}

vector<string> buscarHashes(const vector<shannon_fano>& hojas, const vector<string>& hashes) {
    vector<string> codigosbuscados;

    for (const string& hash : hashes) {
        string codigo = busquedaBinaria(hojas, hash);
        codigosbuscados.push_back(codigo);
    }

    return codigosbuscados;
}