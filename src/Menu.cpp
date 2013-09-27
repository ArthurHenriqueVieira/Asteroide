/*
 * Menu.cpp
 *
 *  Created on: 02/12/2012
 *      Author: Lucas
 */

#include "Menu.h"
#include "Jogo.h"

Menu::Menu(VisualEngine* engine) {
	this->engine = engine;

	rodando = false;
	opcoes = Imagem::CriarImagemBMP("Menu.bmp");
	instrucoes = Imagem::CriarImagemBMP("Instrucoes.bmp");
	controles = Imagem::CriarImagemBMP("Controles.bmp");
	creditos = Imagem::CriarImagemBMP("Creditos.bmp");

	abriJogoOuvinte = NULL;
	abriJogoHandler = NULL;

	telaAtual = 1;

	jogarBotao = new Botao;
	jogarBotao->x = 150;
	jogarBotao->y = 200;
	jogarBotao->altura = 50;
	jogarBotao->largura = 100;

	instrucoesBotao = new Botao;
	instrucoesBotao->x = 100;
	instrucoesBotao->y = 260;
	instrucoesBotao->altura = 50;
	instrucoesBotao->largura = 200;

	creditosBotao = new Botao;
	creditosBotao->x = 110;
	creditosBotao->y = 320;
	creditosBotao->altura = 50;
	creditosBotao->largura = 180;

	sairBotao = new Botao;
	sairBotao->x = 150;
	sairBotao->y = 380;
	sairBotao->altura = 50;
	sairBotao->largura = 100;

	controlesBotao = new Botao;
	controlesBotao->x = 180;
	controlesBotao->y = 400;
	controlesBotao->altura = 50;
	controlesBotao->largura = 230;

	voltarBotao = new Botao;
	voltarBotao->x = 250;
	voltarBotao->y = 480;
	voltarBotao->altura = 100;
	voltarBotao->largura = 200;
}

Menu::~Menu() {
	delete opcoes;
	delete instrucoes;
	delete controles;
	delete creditos;

	delete jogarBotao;
	delete instrucoesBotao;
	delete controlesBotao;
	delete creditosBotao;
	delete sairBotao;
	delete voltarBotao;
}

bool Menu::botaoFoiClicado(Botao* botao, int x, int y) {
	return ( ( x > botao->x ) && ( x < botao->x + botao->largura ) && ( y > botao->y ) && ( y < botao->y + botao->altura ) );
}

Imagem* Menu::getTelaAtual() {
	switch (telaAtual) {
		case 1: // TelaOpcao
			return opcoes;

		case 2: // Tela de instrucoes
			return instrucoes;

		case 3: // Tela de controles
			return controles;

		case 4: // Tela de creditos
			return creditos;
	}

	return NULL;
}

void Menu::sair() {
	rodando = false;
}

void Menu::clicar(int x, int y) {
	switch (telaAtual) {
		case 1: // TelaOpcao
			if (botaoFoiClicado(jogarBotao, x, y)) {
				rodando = false;

				if (abriJogoHandler != NULL)
					abriJogoHandler(abriJogoOuvinte);
			}
			else if (botaoFoiClicado(instrucoesBotao, x, y)) {
				mudarTela(2); //Tela de instruções
			}
			else if (botaoFoiClicado(creditosBotao, x, y)) {
				mudarTela(4); //Tela de Credito
			}
			else if (botaoFoiClicado(sairBotao, x, y)) {
				sair();
			}
			break;

		case 2: // Tela de instrucoes
			if (botaoFoiClicado(controlesBotao, x, y)) {
				mudarTela(3); //tela de controles
			}
			else if (botaoFoiClicado(voltarBotao, x, y)) {
				mudarTela(1); //tela de opcao
			}
			break;

		case 3: // Tela de controles
			if (botaoFoiClicado(voltarBotao, x, y)) {
				mudarTela(1); //tela de opcao
			}
			break;

		case 4: // Tela de creditos
			if (botaoFoiClicado(voltarBotao, x, y)) {
				mudarTela(1); //tela de opcao
			}
			break;
	}

}

void Menu::mudarTela(int tela) {
	telaAtual = tela;
}

void Menu::rodar() {
	if (engine->engineFoiInicializada()) {
		if (engine->criarScreen(MENU_LARGURA, MENU_ALTURA, 32)) {

			engine->setQuitEvent(this, Menu_OnSair);
			engine->setMouseButtonDownEvent(this, Menu_OnMouseButtonDown);

			rodando = true;
			while(rodando) {
				engine->limparScreen();

				engine->desenharImagem(getTelaAtual(), 0, 0);


				engine->atualizarScreen();
				engine->ouvirEvento();
			}
		}
	}
}

void Menu::setAbriJogoEvent(void* ouvinte, AbriJogoHandler handler) {
	abriJogoOuvinte = ouvinte;
	abriJogoHandler = handler;
}

void Menu_OnSair(void* ouvinte) {
	static_cast<Menu*>(ouvinte)->sair();
}

void Menu_OnMouseButtonDown(void* ouvinte, int botao, int x, int y) {
	static_cast<Menu*>(ouvinte)->clicar(x, y);
}

