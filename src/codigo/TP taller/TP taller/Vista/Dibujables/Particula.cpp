#include "Particula.h"


Particula::Particula(SDL_Renderer* renderer, SDL_Rect pos, int vX, int vY, float angulo, float vAngular, int TTL, string pathImagen): DibujableTextura(renderer, pos , pathImagen, pathImagen)
{
	this->ren = renderer;
	this->vX = vX;
	this->vY = vY;
	this->anguloRotacion = angulo;
	this->velocAngular = vAngular;
	this->tiempoDeVida = TTL;
}

void Particula::actualizar(){
	this->setColor(ParserDeHexARgb::parsearDeHexARgb("#A4A4A4"));
	this->tiempoDeVida --;
	this->rect.x += this->vX;
	this->rect.y += this->vY;

	this->anguloRotacion += velocAngular;
}

Particula::~Particula(){}

void Particula::dibujar(SDL_Renderer* renderer, int corrimientoX, int corrimientoY, int escalaZoom, int anchoPx, int altoPx){
	DibujableTextura::dibujar(renderer, corrimientoX, corrimientoY, escalaZoom, anchoPx, altoPx);
}