//librerias
#include <string.h>
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>
#include <bitset>

using namespace std;

//prototipos
void fuente(string cadena);
void trasnmisor(string cadena);
void canal(const pair<int, bitset<8>>& par, int rnum);
void receptor(string cadena);
void destino(string cadena);

int main()
{
    //fuente que se va enviar en este caso un mensaje
    string cadena = "HolaBuenas";

    //el trasnmisor utilizado es una encriptacion en cesar
    fuente(cadena);
}

void fuente(string cadena){
    cout << "El mansaje fue enviado" << endl;
    trasnmisor(cadena);
}

void trasnmisor(string cadena){
    char mayusculas[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char minusculas[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    int tam = cadena.size();
    string palabra;
    char letras[50];
    pair<int, bitset<8>> pares[tam];

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

    srand(time(NULL));
    int num = rand() % 6 + 1;
    
    for (int x=0;x<tam;x++) {
        bitset<8> binario(letras[x]);
        pares[x] = make_pair(x, binario);
        canal(pares[x], num);
    }

    //implementar una lista que solo saque las bits y enviarlos al receptor y hacer el cambio de bits a letras y juntarlos en una cadena para su desciframiento.
    
    string cifrado = palabra;
    cout << "\n" << cifrado << endl;
}

void canal(const pair<int, bitset<8>>& par, int num){
    // regresar solo el mensaje y implementar que el ruido sea enviado en lugar de generarlo aqui
    int letras[50];

    srand(time(NULL));
    int rnum = rand() % 3 + 1;
    int velocidad = 0;

    switch(num){

        case 1:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por UTP el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        break;

        case 2:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por FTP el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        break;

        case 3:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por STP el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        break;

        case 4:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por cable coaxial el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        break;

        case 5:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por fibra optica el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        break;

        case 6:
        if(rnum == 1){
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] sin ruido" << endl;
            for(int i=0;i<10;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 2){
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] con poco ruido" << endl;
            for(int i=0;i<20;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }
        else if(rnum == 3){
            cout << "\nEl paquete fue enviado por wifi el cual es: [" << par.first << "]-[" << par.second << "] con bastante ruido" << endl;
            for(int i=0;i<30;i++){
                velocidad = velocidad + 1;
            }
            cout << "\nLa velocidad a la que se mando el paquete fue de " << velocidad << " segundos." << endl;
        }break;
    }

}

void receptor(string cadena){
    char mayusculas[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char minusculas[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    char letras[50];
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
        palabra.push_back(letras[k]);
    }
    
    string descifrado = palabra;
    cout << descifrado << endl;
}

