/*
 * Lista.h
 *
 *  Created on: 03/11/2012
 *      Author: Lucas
 */

#ifndef LISTA_H_
#define LISTA_H_

#include <iostream>
#include "ItemLista.h"
#include "Objeto.h"

//Classe que define uma estrutura de dados Lista
class Lista
{
private:
        ItemLista *primeiroItem;
        int quantidade;
        //Adiciona um item na lista
        void adicionar(ItemLista *item);
public:
       Lista();
       virtual ~Lista();
       //Criar um item e adiciona na lista
       void adicionar(Objeto *valor);
       //Remove um item da lista procurando pelo valor
       bool remover(Objeto *valor);
       //Remove o primeiro item da lista
       bool removerInicio();
       //Remove o proximo item
       bool removerDepois(ItemLista *item);
       //Retorna o primeiro item
       ItemLista* getItem();
       //Retorna a quantidade de itens da lista
       int count();
};

#endif /* LISTA_H_ */
