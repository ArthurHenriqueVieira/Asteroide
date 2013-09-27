/*
 * Jogo.cpp
 *
 *  Created on: 23/11/2012
 *      Author: Lucas
 */

#include "Jogo.h"

Jogo::Jogo(VisualEngine* engine, JogoSetup* setup) {
	this->engine = engine;
	this->setup = setup;

	rodando = false;
	nave = NULL;
	listaTiro = NULL;
	listaAsteroide = NULL;
	fps = 0;

	sairJogoOuvinte = NULL;
	sairJogoHandler = NULL;

	marcadorVida = Imagem::CriarImagemBMP("Nave.bmp");
	gameOver = Imagem::CriarImagemBMP("GameOver.bmp");
}

void Jogo::carregandoSetup() {
	engine->setQuitEvent(this, Jogo_onSair);
	engine->setKeyDownEvent(this, Jogo_onKeyDown);
	engine->setKeyUpEvent(this, Jogo_onKeyUp);

	jogador.zerarPontos();
	tela = setup->tela;
	jogador.setVidas(setup->vidas);
	fps = (1000 / setup->passoTemporal);

	listaAsteroide = new Lista;
	for (ItemLista *item = setup->asteroides->getItem(); item; item = item->getProximo()) {
		listaAsteroide->adicionar(item->getValor());
	}
}

Jogo::~Jogo() {
	delete nave;
	delete listaTiro;
	delete marcadorVida;
	delete gameOver;
}

void Jogo::moverObjeto(Objeto *obj) {
	GeometriaAnalitica::moverPonto(obj->getPontoCentral(), obj->getTrajetoria(), obj->getVelocidade() * -1);
}

void Jogo::desenharAsteroide(Asteroide *asteroide) {
	double zoom = 1;
	switch (asteroide->getLevel()) {
	case 1:
		zoom = 1;
		break;
	case 2:
		zoom = 0.70;
		break;

	case 3:
		zoom = 0.3;
		break;
	}
	engine->rotacionarImagem(asteroide->getImagem(), asteroide->getPontoCentral(), 0, zoom);
}

void Jogo::desenharNave(Nave *n) {
	engine->rotacionarImagem(n->getImagem(), n->getPontoCentral(), n->getTrajetoria());
}

bool testarColisao(Objeto *a, Objeto *b) {
	float distanciaEntrePontos = GeometriaAnalitica::distanciaEntrePontos(a->getPontoCentral(), b->getPontoCentral());
	return (distanciaEntrePontos <= (a->getRaio() + b->getRaio()));
}

void Jogo::validarEspacoCiclico(Objeto *a) {
	Ponto *ponto = a->getPontoCentral();

	if (ponto->x < 0)
		ponto->x = tela.Largura;

	if (ponto->x > tela.Largura)
		ponto->x = 0;

	if (ponto->y < 0)
		ponto->y = tela.Altura;

	if (ponto->y > tela.Altura)
		ponto->y = 0;
}

bool Jogo::saiuLimite(Objeto *a) {
	Ponto *ponto = a->getPontoCentral();

	return (ponto->x < 0 || ponto->x > tela.Largura || ponto->y < 0 || ponto->y > tela.Altura);
}

Tiro* Jogo::criarTiro(Nave *n) {
	return new Tiro(n->getPontoCentral()->x, n->getPontoCentral()->y, n->getTrajetoria(), n->getCorTiro());
}

void Jogo::desenharTiro(Tiro *tiro) {
	engine->desenharCirculo(tiro->getPontoCentral(), tiro->getRaio(), tiro->getCor());
}

void Jogo::colisaoAsteroide(Asteroide* asteroide) {
	if (asteroide->getLevel() < 3) {
		Asteroide *a1 = new Asteroide(asteroide->getPontoCentral()->x, asteroide->getPontoCentral()->y, asteroide->getRaio() / 2, asteroide->getLevel() + 1);
		Asteroide *a2 = new Asteroide(asteroide->getPontoCentral()->x, asteroide->getPontoCentral()->y, asteroide->getRaio() / 2, asteroide->getLevel() + 1);
		listaAsteroide->adicionar(a1);
		listaAsteroide->adicionar(a2);
	}
	listaAsteroide->remover(asteroide);
}

void Jogo::colisaoNaveAsteroide(Asteroide* asteroide) {
	colisaoAsteroide(asteroide);
	jogador.setVidas(jogador.getVidas() - 1);
	nave->getPontoCentral()->x = tela.Largura / 2;
	nave->getPontoCentral()->y = tela.Altura / 2;
	nave->setTrajetoria(0);
}

void Jogo::colisaoTiroAsteroide(Asteroide* asteroide, Tiro* tiro) {
	int pontos = 1;

	switch (asteroide->getLevel()) {
		case 1:
			pontos = 10;
			break;
		case 2:
			pontos = 20;
			break;

		case 3:
			pontos = 50;
			break;
	}

	jogador.adicionarPontos(pontos);

	colisaoAsteroide(asteroide);
	listaTiro->remover(tiro);
}

void Jogo::desenharContadorVidas() {
	int x = 0, y = 10;
	for (int i = 0; i < jogador.getVidas(); i++, x += 30) {
		engine->desenharImagem(marcadorVida, x, y);
	}
}

void Jogo::desenharGameOver() {
	Ponto pontoCentral;
	pontoCentral.x = tela.Largura / 2;
	pontoCentral.y =  tela.Altura / 2;
	engine->desenharImagem(gameOver, &pontoCentral);
}

void Jogo::desenharPontuacao() {
	int pontos = jogador.getPontos();
	char spontos[5];
	stringstream ss;

	ss << pontos;
	ss >> spontos;
	engine->escreverTexto(1, 1, spontos, 0xC0C0C0B5);
}

Nave* Jogo::criarNave() {
	Nave* n = new Nave(tela.Largura / 2 , tela.Altura / 2);
	n->setDispararTiroEvent(this, Jogo_onNaveAtirar);

	return n;
}

void Jogo::validarColisao() {
	Asteroide* asteroide;
	for (ItemLista *item = listaAsteroide->getItem(); item; item = item->getProximo()) {
		asteroide = (Asteroide*)(item->getValor());
		if (testarColisao(asteroide, nave)) {
			colisaoNaveAsteroide(asteroide);
		}
		else {
			for (ItemLista *item = listaTiro->getItem(); item; item = item->getProximo()) {
				if (testarColisao(asteroide, item->getValor())) {
					colisaoTiroAsteroide(asteroide, (Tiro*)( item->getValor()));
					break;
				}
			}
		}
	}
}

bool Jogo::finalizouLevel() {
	return (listaAsteroide->count() == 0);
}

void Jogo::reiniciarLevel() {
	for (ItemLista *item = setup->asteroides->getItem(); item; item = item->getProximo()) {
		listaAsteroide->adicionar(item->getValor());
	}
}

void Jogo::moverDesenharAsteroides() {
	Asteroide* asteroide;
	for (ItemLista *item = listaAsteroide->getItem(); item; item = item->getProximo()) {
		asteroide = (Asteroide*)(item->getValor());
		moverObjeto(asteroide);
		validarEspacoCiclico(asteroide);
		desenharAsteroide(asteroide);
	}
}

void Jogo::moverDesenharNave() {
	moverObjeto(nave);
	validarEspacoCiclico(nave);
	desenharNave(nave);
}

void Jogo::moverDesenharTiros() {
	Tiro* tiro;
	for (ItemLista *item = listaTiro->getItem(); item; item = item->getProximo()) {
		tiro = (Tiro*)(item->getValor());
		moverObjeto(tiro);
		if (saiuLimite(tiro))
			listaTiro->remover(tiro);
		else
			desenharTiro(tiro);
	}
}

void Jogo::rodar() {

	carregandoSetup();

	if (engine->engineFoiInicializada()) {
		if (engine->criarScreen(tela.Largura, tela.Altura, 32)) {
			engine->setFramePerSecond(fps);

			rodando = true;

			nave = criarNave();
			listaTiro = new Lista;

			while(rodando) {
				engine->limparScreen();

				desenharPontuacao();

				moverDesenharAsteroides();

				if (isGameOver()) {
					desenharGameOver();
				}
				else
				{
					desenharContadorVidas();

					//faz as ações da nave
					nave->acao();
					moverDesenharNave();

					moverDesenharTiros();

					validarColisao();

					if (finalizouLevel())
						reiniciarLevel();
				}

				engine->atualizarScreen();
				engine->ouvirEvento();
			}
		}
	}
}

void Jogo::sair() {
	rodando = false;

	if (sairJogoHandler != NULL)
		sairJogoHandler(sairJogoOuvinte);
}

void Jogo::setSairJogoEvent(void* ouvinte, SairJogoHandler handler) {
	sairJogoOuvinte = ouvinte;
	sairJogoHandler = handler;
}

bool Jogo::isGameOver() {
	return jogador.getVidas() == 0;
}

void Jogo_onSair(void* ouvinte) {
	static_cast<Jogo*>(ouvinte)->sair();
}

void Jogo_onKeyDown(void* ouvinte, int key) {
	Jogo *jogo = static_cast<Jogo*>(ouvinte);

	switch (key) {
		case SDLK_ESCAPE:
			Jogo_onSair(ouvinte);
			break;

		case SDLK_UP:
			jogo->nave->acelerar(true);
			break;

		case SDLK_DOWN:
			jogo->nave->acelerar(false);
			break;

		case SDLK_LEFT:
			jogo->nave->virarEsquerda(true);
			break;

		case SDLK_RIGHT:
			jogo->nave->virarDireita(true);
			break;

		case SDLK_SPACE:
			jogo->nave->atirar(true);
			break;
	}

}

void Jogo_onKeyUp(void* ouvinte, int key) {
	Jogo *jogo = static_cast<Jogo*>(ouvinte);

	switch (key) {
		case SDLK_UP:
			jogo->nave->acelerar(false);
			break;

		case SDLK_LEFT:
			jogo->nave->virarEsquerda(false);
			break;

		case SDLK_RIGHT:
			jogo->nave->virarDireita(false);
			break;

		case SDLK_SPACE:
			jogo->nave->atirar(false);
			break;
	}
}

void Jogo_onNaveAtirar(void* ouvinte, Nave *n) {
	Jogo *jogo = static_cast<Jogo*>(ouvinte);
	jogo->listaTiro->adicionar(jogo->criarTiro(n));
}
