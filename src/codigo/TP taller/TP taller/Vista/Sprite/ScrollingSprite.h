#include "../Dibujables/DibujableTextura.h"

class ScrollingSprite: public DibujableTextura{

private:

	int velocidadRefresco;
	double anchoEscenario;
	int contador;

public:
	ScrollingSprite(SDL_Renderer* renderer, SDL_Rect rect, string path);
	virtual void dibujar(SDL_Renderer* renderer, int corrimientoX,int corrimientoY, float escalaZoom, int anchoPx, int altoPx) override;
	~ScrollingSprite();
};

