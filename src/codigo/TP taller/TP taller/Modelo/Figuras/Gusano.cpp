#include "Gusano.h"



Gusano::Gusano()
{
}


Gusano::Gusano(float x, float y, short int rotacion, b2World* world, bool estatico, float ancho, float alto, float masa)
	: Figura(x , y , rotacion, world, estatico, true)
{
	
	b2PolygonShape rectanguloShape;
	//Divido a la mitad el ancho y alto para que las medidas sean correctas
	rectanguloShape.SetAsBox(ancho/2, alto/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &rectanguloShape;
	float areaRec = ancho * alto;
	fixtureDef.density = masa/areaRec;
	fixtureDef.restitution = restitucion;
	fixtureDef.friction = friccion;
	this->getBody()->CreateFixture(&fixtureDef);
	rectanguloShape.SetAsBox(ancho/2,1,b2Vec2(0,alto/2),0);
	b2FixtureDef fixtureDefSensor;
	fixtureDefSensor.isSensor = true;
	fixtureDefSensor.shape = &rectanguloShape;
	fixtureDefSensor.userData = this;
	this->getBody()->CreateFixture(&fixtureDefSensor);

}

Gusano::~Gusano(void)
{
}

bool Gusano::meClickeo(float x,float y) {
	for (b2Fixture* f = this->getBody()->GetFixtureList(); f; f = f->GetNext())
	{
		  if (f->GetShape()->TestPoint(this->getBody()->GetTransform(),b2Vec2(x,y))) 
			  return true;
	}
	return false;
}
