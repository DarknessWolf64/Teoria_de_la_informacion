//librerias
#include <string.h>
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


//prototipos
void fuente(string cadena);
void trasnmisor(string cadena);
void canal(string cadena);
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
    
    for(int k=0;k<cadena.size();k++){
        palabra.push_back(letras[k]);
    }
    
    string cifrado = palabra;

    cout << cifrado << endl;
    canal(cifrado);
}


void canal(string cadena){
    char letras[50];
    int rnum;

    srand(time(NULL));
    int num = rand() % 6 + 1;

    switch(num){

        case 1:
        rnum = rand() % 3 + 1;
        cout << "Cable de par trenzado sin apantallar (UTP)" << endl;


        break;

        case 2:
        cout << "Cable de par trenzado apantallado (FTP)" << endl;
        break;

        case 3:
        cout << "Cable de par trenzado apantallado (STP)" << endl;
        break;

        case 4:
        cout << "Cable coaxial" << endl;
        break;

        case 5:
        cout << "Cable de fibra optica" << endl;
        break;

        case 6:
        cout << "Inalambricamente" << endl;
        break;
    }
    
    string envio = cadena;

    receptor(envio);
}

void receptor(string cadena){
    char mayusculas[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char minusculas[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    char letras[50];
    int num = 0;
    string palabra;
    
    for(int i=0;i<cadena.size();i++){
        for(int j=0;j<26;j++){
            if(minusculas[j] == cadena[i]){
                letras[i] = minusculas[j - 3];
                num = num + 1; 
            }
            else if(mayusculas[j] == cadena[i]){
                letras[i] = mayusculas[j - 3];
                num = num + 1;
            }
        }
    }
    
    for(int k=0;k<cadena.size();k++){
        palabra.push_back(letras[k]);
    }
    
    string descifrado = palabra;
    cout << descifrado << endl;
}









