//============================================================================
// Name        : Asteroids.cpp
// Author      : Lucas
// Version     :
// Copyright   : 
//============================================================================

#include <iostream>
#include <fstream>
#include <time.h>
#include "Menu.h"
#include "Jogo.h"
#include "JogoSetup.h"
#include "VisualEngine.h"
#include "SDLVisualEngine.h"

using namespace std;

void Asteroids_AbrirJogo(void* ouvinte);
void Asteroids_AbrirMenu(void* ouvinte);

class Asteroids {
private:
	VisualEngine* engine;
	Menu* menu;
	Jogo* jogo;
	JogoSetup* setup;

	JogoSetup* lerArquivoConfiguracao(const char *nomeArquivo);

public:
	Asteroids(const char *nomeArquivoConfiguracao);
	virtual ~Asteroids();
	void rodar();

	friend void Asteroids_AbrirJogo(void* ouvinte);
	friend void Asteroids_AbrirMenu(void* ouvinte);
};
//TODO: CONTAGEM DE PONTOS, melhorar a morte da nave, alien

int main(int argC, char **argV) {
	//Para definir uma nova serie de numeros semi-randomicos para o rand.
	srand(time(0));

	Asteroids jogo("Asteroids.config");
	jogo.rodar();

	return 0;
}


JogoSetup* Asteroids::lerArquivoConfiguracao(const char *nomeArquivo) {
	 JogoSetup* setup = NULL;
	 ifstream arquivo(nomeArquivo);

	 if (arquivo) {
		setup = new JogoSetup;
		setup->asteroides = new Lista;

		string titulo;
		int x, y, raio;
		string cor;

		while (true) {
			arquivo >> titulo;

			if (titulo == "janela") {
				arquivo >> setup->tela.Largura;
				arquivo >> setup->tela.Altura;
			}
			else if (titulo == "passo_simulacao") {
				arquivo >> setup->passoTemporal;
			}
			else if (titulo == "vidas") {
				arquivo >> setup->vidas;
			}
			else if (titulo == "asteroide") {
				arquivo >> x;
				arquivo >> y;
				arquivo >> raio;
				arquivo >> cor;

				if (x == 0 && y == 0 && raio == 0)
					break;
				else
					setup->asteroides->adicionar(new Asteroide(x, y, raio));
			}
		}

		arquivo.close();
	 }
	 else {
		 cout << "O arquivo '" << nomeArquivo << "' não pode ser aberto. \n";
		 system("PAUSE");
		 exit(EXIT_FAILURE);
	 }

	 return setup;
}

Asteroids::Asteroids(const char *nomeArquivoConfiguracao) {
	engine = new SDLVisualEngine;

	setup = lerArquivoConfiguracao(nomeArquivoConfiguracao);

	menu = new Menu(engine);
	jogo = new Jogo(engine, setup);

	menu->setAbriJogoEvent(this, Asteroids_AbrirJogo);
	jogo->setSairJogoEvent(this, Asteroids_AbrirMenu);
}

Asteroids::~Asteroids() {
	delete engine;
	delete menu;
	delete jogo;
	delete setup;
}

void Asteroids::rodar() {
	menu->rodar();
}

void Asteroids_AbrirJogo(void* ouvinte) {
	Asteroids* asteroids = static_cast<Asteroids*>(ouvinte);
	asteroids->jogo->rodar();

}

void Asteroids_AbrirMenu(void* ouvinte) {
	Asteroids* asteroids = static_cast<Asteroids*>(ouvinte);
	asteroids->menu->rodar();
}


