#include "Dibujable.h"

Dibujable::Dibujable(){}

Dibujable::~Dibujable() 
{
}

void Dibujable::setColor(int* rgb){
}

void Dibujable::dibujar(SDL_Renderer* renderer, int corrimientoX, int corrimientoY, float escalaZoom, int anchoPx, int altoPx){
}

string Dibujable::serializar(){
	string serializado = "";
	return serializado;
}

int Dibujable::deserealizar(string aDeserealizar){
	return 0;
}

bool Dibujable::getDestruido(){
	return this->destruido;
}

void Dibujable::setDestruido(bool destruido){
	this->destruido = destruido;
}