#include <iostream>
using namespace std;


class Nodo{
	int dato;
	Nodo *sig;
	public:
		Nodo();
		Nodo(int d, Nodo* s);
		void setDato(int d);
		void setSig(Nodo* s);
		int getDato();
		Nodo* getSig();
};
Nodo::Nodo(){
	dato = 0;
	sig = NULL;
}
Nodo::Nodo(int d, Nodo* s){
	dato = d;
	sig = s;
}
void Nodo::setDato(int d){
	dato = d;
}
void Nodo::setSig(Nodo* s){
	sig = s;
}
int Nodo::getDato(){
	return dato;
}
Nodo* Nodo::getSig(){
	return sig;
}

class Cola{
	Nodo *fte, *fin;
	
	public:
		Cola();
		~Cola();
		void meter(int x);
		void sacar();
		int getDato();
		int estaVacia();
		void mostrar();
		void radixSort();
};
Cola::Cola(){
	fte = fin = NULL;
}
Cola::~Cola(){
	while(!estaVacia())
		sacar();
}
void Cola::meter(int x){
	Nodo *p;
	p = new Nodo(x, NULL);
	if(!estaVacia())
		fin->setSig(p);
	else
		fte = p;
	fin = p;
}
void Cola::sacar(){
	if(!estaVacia()){
		Nodo *p;
		p = fte;
		if(fin==fte)
			fin = NULL;
		fte = p->getSig();
		delete p;
	}
}

int Cola::getDato(){
	if(estaVacia()){
		cout<<"\nLista vacia en getDato";
		return -1;
	}
	return fte->getDato();
}
int Cola::estaVacia(){
	return fte==NULL;
}
void Cola::mostrar(){
	Cola Caux;
	cout<<"\nfte->";
	while(!estaVacia()){
		cout<<getDato()<<"->";
		Caux.meter(getDato());
		sacar();
	}
	while(!Caux.estaVacia()){
		meter(Caux.getDato());
		Caux.sacar();
	}
	cout<<"fin";
}

void Cola::radixSort(){
	//METODO RADIX SORT
	int n;
	Cola colas[10];
	int modulos[] = {10,100,1000,10000};
	
	//SE EJECUTAN LAS 4 ITERACIONES
	for(int i=0;i<4;i++){
		//SE MUEVEN LOS NUMEROS EN LA COLA QUE CORRESPONDE
		if(i==0){
			while(!estaVacia()){
				n = getDato();
				colas[n%modulos[i]].meter(n);
				sacar();
			}
		}
		else{
			while(!estaVacia()){
				n = getDato();
				colas[(n%modulos[i])/modulos[i-1]].meter(n);
				sacar();
			}
		}
		
		//SE REGRESAN A LA COLA ORIGINAL
		for(int j=0;j<10;j++){
			while(!colas[j].estaVacia()){
				meter(colas[j].getDato());
				colas[j].sacar();
			}
		}
	}
}

int main(){
	Cola cola;
	int n,x;
	//Se piden los datos
	cout<<"Escribe el numero de datos que deseas ordenar: ";
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x;
		cola.meter(x);
	}
	//SE MUESTRA LA COLA INICIAL
	cout<<"\n\nLa cola inicial luce de la siguiente manera: ";
	cola.mostrar();
	//SE ORDENA LA COLA
	cola.radixSort();
	//SE MUESTRA LA COLA ORDENADA
	cout<<"\n\nLa cola despues de ordenarse luce de la siguiente manera: ";
	cola.mostrar();
	return 0;
	
}
