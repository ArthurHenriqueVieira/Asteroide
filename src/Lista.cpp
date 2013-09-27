/*
 * Lista.cpp
 *
 *  Created on: 03/11/2012
 *      Author: Lucas
 */

#include "Lista.h"

Lista::Lista() {
   quantidade = 0;
   primeiroItem = NULL;
}

void Lista::adicionar(ItemLista *item) {
   ItemLista *aux = primeiroItem;
   primeiroItem = item;
   primeiroItem->setProximo(aux);

   quantidade++;
}

void Lista::adicionar(Objeto *valor) {
   adicionar(new ItemLista(valor));
}

bool Lista::removerInicio() {
	if (primeiroItem) {
		ItemLista *aux = primeiroItem;
		primeiroItem = primeiroItem->getProximo();

		quantidade--;
		delete aux;

		return true;
	}

	return false;
}

bool Lista::removerDepois(ItemLista *item) {
	if (item) {
		ItemLista *aux = item->getProximo();
		if (aux) {
			item->setProximo(aux->getProximo());

			quantidade--;
			delete aux;

			return true;
		}
	}

	return false;
}

bool Lista::remover(Objeto *valor) {
	ItemLista *anterior = NULL;

    for (ItemLista *aux = primeiroItem; aux; aux = aux->getProximo()) {
        if (aux->getValor() == valor) {
        	if (anterior == NULL)
        		return removerInicio();
        	else
        		return removerDepois(anterior);
        }
        anterior = aux;
    }

    return false;
}

ItemLista* Lista::getItem() {
	return primeiroItem;
}

int Lista::count() {
	return quantidade;
}

Lista::~Lista() {

}
