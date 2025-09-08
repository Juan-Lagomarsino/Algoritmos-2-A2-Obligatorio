#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
// Entendemos que no hay que usar templates porque el tipo es uno solo.
struct Jugador {
    int idJugador;
    string nombreUsuario;
    int puntajeActual; // O(1)
    Jugador(int id,string nombre,int puntaje) : idJugador(id),nombreUsuario(nombre), puntajeActual(puntaje) {}
};
struct NodoAVL{
    Jugador * jugador;
    int alturaAVL;
    NodoAVL * izq;
    NodoAVL * der;
    int cantidadJugadores; // O(1)
    NodoAVL():jugador(NULL),alturaAVL(1), izq(NULL), der(NULL) {}
};

class AVL
{
private:
    NodoAVL * raizId;
    NodoAVL * raizPuntaje;
    Jugador * top1;
    
    int alturaPermitida(NodoAVL*nodo){
        if (nodo == NULL){
            return 0;
        }else{
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

    void actualizarAlturaNodo(NodoAVL*nodo)
    {
        if (nodo != NULL)
        {
            nodo->alturaAVL = 1 + max(alturaPermitida(nodo->izq), alturaPermitida(nodo->der));
        }
    }

    void actualizarCantidadJugadores(NodoAVL*nodo){
        nodo->cantidadJugadores++;
    }

    void rotacionDerecha(NodoAVL *&B)
    {
        NodoAVL *A = B->izq;
        NodoAVL *T2 = A->der;
        B->izq = T2;
        A->der = B;
        actualizarAlturaNodo(B);
        actualizarAlturaNodo(A);
        B = A;
    }

    void rotacionIzquierda(NodoAVL *&A)
    {
        NodoAVL *B = A->der;
        NodoAVL *T2 = B->izq;
        A->der = T2;
        B->izq = A;
        actualizarAlturaNodo(A);
        actualizarAlturaNodo(B);
        A = B;
    }

    void ADDRecursivoId(NodoAVL *&nodo, int id, string nombre, int puntaje){
        if(nodo == NULL) {
            nodo = new NodoAVL();
            nodo->jugador= new Jugador(id, nombre, puntaje);
            ADDRecursivoPtj()
        } else if (nodo->jugador->idJugador < id){
            ADDRecursivoId(nodo->der, id, nombre, puntaje);
        } else if (nodo->jugador->idJugador > id){
            ADDRecursivoId(nodo->izq, id, nombre, puntaje);
        }else{
            return;
        }
        
    
        actualizarAlturaNodo(nodo);

        int balance = darBalance(nodo);
        
        // caso izq izq
        if(balance < -1 && nodo->izq->jugador->idJugador > id) {
            rotacionDerecha(nodo);
        // caso izq der
        }else if( balance < -1 && nodo->izq->jugador->idJugador < id) {
            rotacionIzquierda(nodo->izq);
            rotacionDerecha(nodo);
        // caso der der
        }else if(balance > 1 && nodo->der->jugador->idJugador < id) {
            rotacionIzquierda(nodo);
        // caso der izq
        }else if( balance > 1 && nodo->der->jugador->idJugador > id) {
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
        if(balance < -1 && nodo->izq->jugador->puntajeActual > puntaje) {
            rotacionDerecha(nodo);
        // caso izq der
        }else if( balance < -1 && nodo->izq->jugador->puntajeActual < puntaje) {
            rotacionIzquierda(nodo->izq);
            rotacionDerecha(nodo);
        // caso der der
        }else if(balance > 1 && nodo->der->jugador->puntajeActual < puntaje) {
            rotacionIzquierda(nodo);
        // caso der izq
        }else if( balance > 1 && nodo->der->jugador->puntajeActual > puntaje) {
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
    AVL()
    {
        raizId = NULL;
        raizPuntaje = NULL;
        top1 =NULL;
    };
    void ADD(int id, string nombre, int puntaje) {
        this->ADDRecursivoId(this->raizId, id, nombre, puntaje);
        this->ADDRecursivoPtj(this->raizPuntaje, id, nombre, puntaje);
    };

    void FIND(int id) {
        this->FINDRecursivo(raizId, id);
    };

    void RANK(int puntaje)
    {
        cout << this->RANKRecursivo(raizPuntaje, puntaje) << endl;
    }

    void TOP1()
    {
        if(this->raizPuntaje==NULL){
            cout << "sin_jugadores" << endl;
        }else{
            cout << this->top1->nombreUsuario << " " << this->top1->puntajeActual << endl;
        }}

    void COUNT()
    {
        cout << this->cantidadJugadores << endl;
    }

};


int main()
{
    AVL * ejercicio1 = new AVL();

    ejercicio1->ADD(101, "Alice", 750);
    ejercicio1->ADD(202,"Bob" ,850);
    ejercicio1->ADD (303,"Charlie", 600);
    ejercicio1->FIND(202);
    ejercicio1->TOP1();
    ejercicio1->COUNT();
    ejercicio1->RANK(700);
    ejercicio1->ADD (404 ,"Diana", 850);
    ejercicio1->TOP1();
    ejercicio1->ADD (202, "Bobby", 900);
    ejercicio1->COUNT();
    /*int n;
    cin >> n;
    cin.ignore(); // Limpia el espacio para depsues no haya errores de identacion.

    for (int i =0 ; i<n ; i++)
    {
        string opcion;
        getline(cin,opcion); // Que agarre toda la palabra
        char primerLetra = opcion.front();
        int pos = opcion.find(" ");
        string inst = opcion.substr(pos,opcion.length()-pos);
            
        if (primerLetra == 'A')
        {
            int id = stoi(inst.substr(0,inst.find(" "))); //stoi es el parseInt, substr corta la cadena.
            inst = inst.substr(0,inst.find(" "));
            string nombre = inst.substr(0,inst.find(" ")); //stoi es el parseInt, substr corta la cadena.
            inst = inst.substr(0,inst.find(" "));
            int puntaje = stoi(inst.substr(0,inst.find(" ")));
            
            ejercicio1->ADD(id,nombre,puntaje);
        }
        else if (primerLetra == 'F')
        {

        }
        else if (primerLetra == 'R')
        {

        }
        else if (primerLetra == 'T')
        {

        }
        else if (primerLetra == 'C')
        {

        }
        else
        {
            return; // No deberia pasar.
        }
    }
*/
    /*

    Aca va a haber algo con un switch con las operaciones, tipo ADD FIND RANK TOP1 COUNT

    Esa era la idea original pero no se podia hacer switch con strings.
    */
    
}