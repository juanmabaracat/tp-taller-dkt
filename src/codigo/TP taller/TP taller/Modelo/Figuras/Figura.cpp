#include "Figura.h"


Figura::Figura()
{
	//DEFINIR LOS VALORES POR DEFECTO
}

Figura::Figura(float x, float y, short int rotacion, b2World* world, bool estatico, bool rotacionFija)
{
	this->destruido = false;
	b2BodyDef myBodyDef;
	if (estatico){
	myBodyDef.type = b2_staticBody;
	} else {
		myBodyDef.type = b2_dynamicBody;
	}
	myBodyDef.allowSleep = false;
	myBodyDef.fixedRotation = rotacionFija;
	myBodyDef.position.Set(x, y);
	this->posicionInicial = b2Vec2(x,y);
	this->anguloInicial = rotacion * DEGTORAD;
	//Angulo en radianes
	myBodyDef.angle = this->anguloInicial; 

	this->body = world->CreateBody(&myBodyDef);
	this->movimientoDer = false;
	this->movimientoIzq = false;
	this->muerto = false;
	this->ahogado = false;
}

void Figura::quieto(){

	this->setMovimientoIzq(false);
	this->setMovimientoDer(false);
}

b2Body* Figura::getBody()
{
	return this->body;
}


void Figura::setPosicion(float x, float y, float angulo)
{
	this->body->SetTransform( b2Vec2 (x, y), angulo);
}

b2Vec2 Figura::getPosicion()
{
	return this->body->GetPosition();
}

float Figura::getAngulo()
{
	return this->body->GetAngle();
}

void Figura::comenzarOtraPartida(){
	this->setPosicion(this->posicionInicial.x,this->posicionInicial.y,this->anguloInicial);
	this->body->SetAngularVelocity(0);
	this->body->SetLinearVelocity(b2Vec2(0,0));
	this->body->SetAwake(true);
	this->setMovimientoIzq(false);
	this->setMovimientoDer(false);
}

void Figura::reiniciar(){

	//this->body->SetAwake(true);
	this->setMovimientoIzq(false);
	this->setMovimientoDer(false);
}

Figura::~Figura(void)
{
}

bool Figura::seMueveALaDer(){
	return this->movimientoDer;
}

void Figura::setMovimientoDer(bool movDer){
	this->movimientoDer = movDer;
}

bool Figura::seMueveALaIzq(){
	return this->movimientoIzq;
}

void Figura::setMovimientoIzq(bool movIzq){
	this->movimientoIzq = movIzq;
}

bool Figura::meClickeo(float x,float y) {
	return false;
}

void Figura::simularAgua(int nivelAgua){
}

bool Figura::estaMuerto(){
	return this->muerto;
}

void Figura::setMuerto(bool estado){
	this->muerto = estado;
}

void Figura::BeginContact() {
}

void Figura::EndContact(){
}

void Figura::PostSolve(float impulso){
}

void Figura::explotar(float fuerza) {
}

void Figura::setAhogado(bool estado){
	this->ahogado = estado;
}

bool Figura::estaAhogado(){
	return this->ahogado;
}

bool Figura::getDestruido(){
	return this->destruido;
}

void Figura::setDestruido(bool destruido){
	this->destruido = destruido;
}