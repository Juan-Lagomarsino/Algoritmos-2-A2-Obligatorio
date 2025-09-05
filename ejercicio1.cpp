#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
//Entiendo que no hay que usar templates porque el tipo es uno solo.
struct NodoAVL{
    int idJugador;
    string nombreUsuario;
    int puntajeActual;
    int alturaAVL;
    int cantidadJugadores;
    NodoAVL * izq;
    NodoAVL * der;
};

class AVL {
    private:
    NodoAVL * raizId;
    NodoAVL * raizPuntaje;

    int alturaPermitida(NodoAVL * nodo){
        /* if(nodo==NULL)return 0;
        else return nodo->alturaAVL;
        */
    }
    int balance(NodoAVL * nodo){

    }
    void actualizarAlturaNodo(NodoAVL * nodo ){

    }
    void actualizarCantidad(NodoAVL * nodo){

    }
    void rotacionDerecha(NodoAVL * nodo){

    }
    void rotacionIzquierda(NodoAVL * nodo){

    }
    void ADDRecursivo(){

    }



    public:
    AVL () {
        raizId = NULL;
        raizPuntaje = NULL;
    };
    void ADD(string id, string nombre, int puntaje){
        //Logica tiene que mandar recursivo a this->raizId, y this->raizPuntaje
    };

    void FIND(string id){
        //Logica
    };

    void RANK(int puntaje){
        //Logica
    }

    void TOP1(){
        //Logica
    }

    void COUNT(){
        //Logica tiene que ser this->cantidadElementos
    }
};

int main()
{
    AVL * ejercicio1 = new AVL();
    
    /*
    
    Aca va a haber algo con un switch con las operaciones, tipo ADD FIND RANK TOP1 COUNT
    */

}