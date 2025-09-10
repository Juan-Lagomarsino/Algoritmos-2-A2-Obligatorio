#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
// Entendemos que no hay que usar templates porque el tipo es uno solo.
struct NodoAVL
{
    int idJugador;
    string nombreUsuario;
    int puntajeActual; // O(1)
    int alturaAVL;
    NodoAVL *izq;
    NodoAVL *der;
    NodoAVL(int id, string user, int ptj) : idJugador(id), nombreUsuario(user), puntajeActual(ptj), alturaAVL(1), izq(NULL), der(NULL) {}
};

class AVL
{
private:
    NodoAVL *raizId;
    NodoAVL *raizPuntaje;
    NodoAVL *top1;
    int cantidadJugadores; // O(1)

    int alturaPermitida(NodoAVL *nodo){
        if (nodo == NULL){
            return 0;
        }
        else{
            return nodo->alturaAVL;
        }
    }

    int darBalance(NodoAVL *nodo){
        if (nodo == NULL){
            return 0;
        }
        else{
            return alturaPermitida(nodo->der) - alturaPermitida(nodo->izq);
        }
    }

    void actualizarAlturaNodo(NodoAVL *nodo){
        if (nodo != NULL){
            nodo->alturaAVL = 1 + max(alturaPermitida(nodo->izq), alturaPermitida(nodo->der));
        }
    }

    void rotacionDerecha(NodoAVL *&B){
        NodoAVL *A = B->izq;
        NodoAVL *T2 = A->der;
        B->izq = T2;
        A->der = B;
        actualizarAlturaNodo(B);
        actualizarAlturaNodo(A);
        B = A;
    }

    void rotacionIzquierda(NodoAVL *&A){
        NodoAVL *B = A->der;
        NodoAVL *T2 = B->izq;
        A->der = T2;
        B->izq = A;
        actualizarAlturaNodo(B);
        actualizarAlturaNodo(A);
        A = B;
    }

    void ADDRecursivoId(NodoAVL *&nodo, int id, string nombre, int puntaje){
        if(nodo == NULL) {
            nodo = new NodoAVL(id, nombre, puntaje);
            this->cantidadJugadores++;
            this->ADDRecursivoPtj(this->raizPuntaje, id, nombre, puntaje);
        } else if (nodo->idJugador < id){
            ADDRecursivoId(nodo->der, id, nombre, puntaje);
        } else if (nodo->idJugador > id){
            ADDRecursivoId(nodo->izq, id, nombre, puntaje);
        }else{
            return;
        }
        
    
        actualizarAlturaNodo(nodo);

        int balance = darBalance(nodo);
        
        // caso izq izq
        if(balance < -1 && nodo->izq->idJugador > id) {
            rotacionDerecha(nodo);
        // caso izq der
        }else if( balance < -1 && nodo->izq->idJugador < id) {
            rotacionIzquierda(nodo->izq);
            rotacionDerecha(nodo);
        // caso der der
        }else if(balance > 1 && nodo->der->idJugador < id) {
            rotacionIzquierda(nodo);
        // caso der izq
        }else if( balance > 1 && nodo->der->idJugador > id) {
            rotacionDerecha(nodo->der);
            rotacionIzquierda(nodo);
        }
        
    }
    
    void ADDRecursivoPtj(NodoAVL *&nodo, int id, string nombre, int puntaje){
        if(nodo == NULL) {
            nodo = new NodoAVL(id, nombre, puntaje);
            if((this->top1!=NULL && nodo->puntajeActual > this->top1->puntajeActual) || (this->top1!=NULL && nodo->puntajeActual == this->top1->puntajeActual && nodo->idJugador < this->top1->idJugador)||(this->top1==NULL)){
                this->top1 = nodo;
            }
        } else if (nodo->puntajeActual < puntaje){
            ADDRecursivoPtj(nodo->der, id, nombre, puntaje);
        } else if (nodo->puntajeActual >= puntaje){
            ADDRecursivoPtj(nodo->izq, id, nombre, puntaje);
        }
        
    
        actualizarAlturaNodo(nodo);

        int balance = darBalance(nodo);
        
        // caso izq izq
        if(balance < -1 && nodo->izq->puntajeActual > puntaje) {
            rotacionDerecha(nodo);
        // caso izq der
        }else if( balance < -1 && nodo->izq->puntajeActual < puntaje) {
            rotacionIzquierda(nodo->izq);
            rotacionDerecha(nodo);
        // caso der der
        }else if(balance > 1 && nodo->der->puntajeActual < puntaje) {
            rotacionIzquierda(nodo);
        // caso der izq
        }else if( balance > 1 && nodo->der->puntajeActual > puntaje) {
            rotacionDerecha(nodo->der);
            rotacionIzquierda(nodo);
        }
    }

    void FINDRecursivo(NodoAVL* nodo, int id){
        if(nodo == NULL){
            cout << "jugador_no_encontrado" << endl;
        }
        else if(nodo->idJugador == id){
            cout << nodo->nombreUsuario << " " <<nodo->puntajeActual << endl;
        }
        else if(nodo->idJugador > id){
            FINDRecursivo(nodo->izq, id);
        }
        else if(nodo->idJugador < id){
            FINDRecursivo(nodo->der, id);
        }
    }
    
    int RANKRecursivo(NodoAVL* nodo,int puntaje){
        if(nodo!=NULL){
            if(nodo->puntajeActual>=puntaje){
                return 1 + RANKRecursivo(nodo->izq,puntaje) + RANKRecursivo(nodo->der,puntaje);
            }else{
                return RANKRecursivo(nodo->izq,puntaje) + RANKRecursivo(nodo->der,puntaje);
            }
        }
        return 0;
    }

public:
    AVL(){
        raizId = NULL;
        raizPuntaje = NULL;
        top1 =NULL;
    };
    void ADD(int id, string nombre, int puntaje) {
        this->ADDRecursivoId(this->raizId, id, nombre, puntaje);
        
    };

    void FIND(int id) {
        this->FINDRecursivo(raizId, id);
    };

    void RANK(int puntaje){
        cout << this->RANKRecursivo(raizPuntaje, puntaje) << endl;
    }

    void TOP1(){
        if(this->top1==NULL){
            cout << "sin_jugadores" << endl;
        }else{
            cout << this->top1->nombreUsuario << " " << this->top1->puntajeActual << endl;
        }}

    void COUNT(){
        cout << this->cantidadJugadores << endl;
    }

};


int main(){
    AVL * ejercicio1 = new AVL();
    int n;
    cin >> n;
    cin.ignore(); // Limpia el espacio para depsues no haya errores de identacion.

    for (int i =0 ; i<n ; i++){
        string opcion;
        getline(cin,opcion); // Que agarre toda la palabra
        char primerLetra = opcion.front();
            
        if (primerLetra == 'A'){   
            if (primerLetra == 'A') {
                int pos1 = opcion.find(" ");
                int pos2 = opcion.find(" ", pos1 + 1);
                int pos3 = opcion.find(" ", pos2 + 1);

                int id = stoi(opcion.substr(pos1 + 1, pos2 - pos1 - 1));
                string nombre = opcion.substr(pos2 + 1, pos3 - pos2 - 1);
                int puntaje = stoi(opcion.substr(pos3 + 1));

                ejercicio1->ADD(id, nombre, puntaje);
            }
        }
        else if (primerLetra == 'F'){   
            int pos = opcion.find(" ");
            string inst = opcion.substr(pos,opcion.length()-pos);
            int id = stoi(inst);
            ejercicio1->FIND(id);
        }
        else if (primerLetra == 'R'){   
            int pos = opcion.find(" ");
            string inst = opcion.substr(pos,opcion.length()-pos);
            int puntaje = stoi(inst);
            ejercicio1->RANK(puntaje);

        }
        else if (primerLetra == 'T'){
            ejercicio1->TOP1();
        }
        else if (primerLetra == 'C'){
            ejercicio1->COUNT();
        }
    }
}