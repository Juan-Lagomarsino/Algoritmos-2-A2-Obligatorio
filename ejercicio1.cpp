#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
//Entiendo que no hay que usar templates porque el tipo es uno solo.
struct NodoAVL{
    string idJugador;
    string nombreUsuario;
    int puntajeActual;
    int alturaAVL;
    NodoAVL * izq;
    NodoAVL * der;
};

class AVL {
    private:
    NodoAVL * raizId;
    NodoAVL * raizPuntaje;

    

    public:
    AVL () {
        raizId = NULL;
        raizPuntaje = NULL;
    };
    void ADD(string id, string nombre, int puntaje){
        //Logica
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
        //Logica
    }
};

int main()
{
    AVL * ejercicio1 = new AVL();
    
    /*
    
    Aca va a haber algo con un switch con las operaciones, tipo ADD FIND RANK TOP1 COUNT
    */

}