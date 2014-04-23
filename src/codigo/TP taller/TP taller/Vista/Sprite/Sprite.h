#include "../Dibujables/DibujableTextura.h"

class Sprite: public DibujableTextura{

private:

	SDL_Rect* recCuadro;
	SDL_Rect recDest;
	SDL_Texture* textura;
	int frame;
	int numCuadros;
	int velocidadRefresco;
	int contador;

public:
	Sprite(SDL_Renderer* renderer, SDL_Rect recFrame, string path, int col, int fil, int anchoTex, int altoTex);
	virtual void dibujar(SDL_Renderer* renderer, int corrimiento, int escalaZoom, int posZoomX, int posZoomY) override;
	~Sprite();
};

