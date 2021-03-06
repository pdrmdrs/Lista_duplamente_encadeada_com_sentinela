/*
 *
 *   Este é o único arquivo que você irá modificar durante toda esta atividade.
 *
 */


#include <stdlib.h>
#include <iostream>
#include "Lista.h"

#define VALOR_QUALQUER -10000

No CriarNo(int);
bool DestruirNo(No);

/**
    Função que aloca memória para uma instância da estrutura Lista e inicializa os seus campos.
 */
Lista LIS_Criar()
{
    Lista lista = (Lista)malloc(sizeof(tpLista));
    if( lista == NULL )
    {
        return NULL;
    }
    
    lista->cabeca = CriarNo(VALOR_QUALQUER);//criar no para a cabeça da lista
    if( lista->cabeca == NULL )
    {
        return NULL;
    }

    lista->cauda = CriarNo(VALOR_QUALQUER);//criar no para a cauda da lista
    if( lista->cauda == NULL )
    {
        return NULL;
    }
    
    //setar valores para o proximo e anterior da cabeça e da cauda
    lista->cabeca->proximo  = lista->cauda;
    lista->cabeca->anterior = NULL;

    lista->cauda->anterior = lista->cabeca;
    lista->cauda->proximo = NULL;

    lista->tamanho = 0;

    return lista;
}

/*
    Função que busca a posição de uma determinada chave numa lista.
    @param lista - lista em que será feita a busca
    @param chave - chave a ser buscada na lista
    @return índice que indica a posição do elemento cujo valor é igual a chave. Retorna -1 caso a chave não seja encontrada na lista.
 */
int LIS_Buscar(Lista lista, int chave)
{
    if( lista->tamanho > 0)
    {
        int indice = 1;

        No no = lista->cabeca->proximo;

        while(no != lista->cauda)
        {
            if(no->valor == chave)
            {
                return indice;
            }
            else
            {
                no = no->proximo;
                indice += 1;
            }
        }
        return -1;
    }
    else
    {
        return -1;    
    }
}

/*
 Função que retorna o valor de um elemento na lista que está na posição indicada pelo parâmetro i.
 @param lista - lista em que será feita a busca
 @param i - indica a posição do elemento cujo valor se deseja retornar
 @return valor do elemento na i-esima posição da lista. Retorna -1 se não existir elemento na i-esima posição
 */
int LIS_PegarValor(Lista lista, int i)
{
    if( lista->tamanho > 0)
    {
        int indice = 1;

        No no = lista->cabeca->proximo;

        while(no != lista->cauda)
        {
            if(indice == i)
            {
                return no->valor;
            }
            else
            {
                no = no->proximo;
                indice += 1;
            }
        }
        return -1;
    }
    else
    {
        return -1;    
    }
}

/*
 Função que retorna o valor de um elemento na lista que está na posição indicada pelo parâmetro i.
 @param lista - lista em que será feita a busca
 @param i - indica a posição do elemento cujo valor se deseja retornar
 @return valor do elemento na i-esima posição da lista. Retorna -1 se não existir elemento na i-esima posição
 */
No LIS_PegarNo(Lista lista, int i)
{
    if( lista->tamanho > 0)
    {
        int indice = 1;

        No no = lista->cabeca->proximo;

        while(no != lista->cauda)
        {
            if(indice == i)
            {
                return no;
            }
            else
            {
                no = no->proximo;
                indice += 1;
            }
        }
        return NULL;
    }
    else
    {
        return NULL;    
    }
}

/*
 Função que insere um valor no início da lista. Após a execução desta função, o elemento inserido será o primeiro elemento da lista.
 @param lista - lista em que será feita a inserção
 @param v - valor a ser inserido na lista
 @return true se inseriu com sucesso, false caso contrário
 */
bool LIS_InserirInicio(Lista lista, int v)
{
    No no = CriarNo(v);
    if( no == NULL )
    {
        return false;
    }
    
    No primeiro = lista->cabeca->proximo;
    
    primeiro->anterior = no;

    no->proximo = primeiro;
    no->anterior = lista->cabeca;

    lista->cabeca->proximo = no;
    lista->tamanho += 1;
    
    return true;
}

/*
 Função que insere um valor no fim da lista. Após a execução desta função, o elemento inserido será o último elemento da lista.
 @param lista - lista em que será feita a inserção
 @param v - valor a ser inserido na lista
 @return true se inseriu com sucesso, false caso contrário
 */
bool LIS_InserirFim(Lista lista, int v)
{

    No no = CriarNo(v);
    if( no == NULL )
    {
        return false;
    }
    
    No ultimo = lista->cauda->anterior;
    
    ultimo->proximo = no;

    no->proximo = lista->cauda;
    no->anterior = ultimo;

    lista->cauda->anterior = no;
    lista->tamanho += 1;

    return true;
}

/*
 Função que insere um valor numa determinada posição da lista. Após a execução desta função, o elemento inserido será o i-esimo elemento da lista.
 @param lista - lista em que será feita a inserção
 @param v - valor a ser inserido na lista
 @param i - indica a posição que o novo elemento ocupará após a inserção
 @return true se inseriu com sucesso, false caso contrário
 */
bool LIS_Inserir(Lista lista, int v, int i)
{
    if(i == 1)//adicionar no inicio
    {
        LIS_InserirInicio(lista, v);
    }
    else if(i == (lista->tamanho+1))//adicionar no final
    {
        LIS_InserirFim(lista, v);
    }
    else if(i > (lista->tamanho+1))//tentando adicionar numa posicao maior que o tamanho do vetor
    {
        return false;
    }
    else//adicionar em uma outra posicao
    {
        int indice = 1;

        No iterador = lista->cabeca->proximo;//pega o primeiro elemento da lista para ser o iterador

        while(iterador != lista->cauda)//vai percorrer a lista até chegar na cauda
        {
            if(i == indice)//se o indice for o mesmo da posicao indicada, criar o nó e adicionar ele
            {
                No no = CriarNo(v);//criar o nó que ira ser inserido na lista
                if( no == NULL )
                {
                    return false;
                }

                //setar o proximo e o anterior do novo nó
                no->anterior = iterador->anterior;
                no->proximo = iterador;

                //atualizar o proximo do elemento anterior ao novo nó e o anterior do proximo elemento do novo nó
                iterador->anterior->proximo = no;
                iterador->anterior = no;

                lista->tamanho += 1;

                return true;
            }
            else//se o indice for diferente da posicao indicada, atualizar o iterador e incrementar o indice
            {
                iterador = iterador->proximo;
                indice += 1;
            }
        }
    }  
} 

/*
 Função que remove um valor no início da lista.
 @param lista - lista em que será feita a remoção
 @return retorna o valor do elemento removido. Retorna -1 caso a lista esteja vazia.
 */
int LIS_RemoverInicio(Lista lista)
{    
    if( lista->tamanho > 0 )
    {
        No primeiro = lista->cabeca->proximo;

        lista->cabeca->proximo = primeiro->proximo;

        primeiro->proximo->anterior = lista->cabeca;

        int valor = primeiro->valor;

        lista->tamanho -= 1;

        DestruirNo(primeiro);

        return valor;
    }
    else
    {
        return -1;
    }
}

/*
 Função que remove um valor no fim da lista.
 @param lista - lista em que será feita a remoção
 @return retorna o valor do elemento removido. Retorna -1 caso a lista esteja vazia.
 */
int LIS_RemoverFim(Lista lista)
{
    if( lista->tamanho > 0 )
    {
        No ultimo = lista->cauda->anterior;
        
        lista->cauda->anterior = ultimo->anterior;
        
        ultimo->anterior->proximo = lista->cauda;
        
        int valor = ultimo->valor;
        
        lista->tamanho -= 1;
        
        DestruirNo(ultimo);
        
        return valor;
    }
    else
    {
        return -1;
    }
}

/*
 Função que remove um valor numa determinada posição da lista.
 @param lista - lista em que será feita a remoção
 @param indice - indica a posição na lista do elemento que se deseja remover
 @return retorna o valor do elemento removido. Retorna -1 caso a lista esteja vazia, ou caso o índice não aponte para uma posição válida da lista.
 */
int LIS_Remover(Lista lista, int indice)
{
    if(indice == 1)//remover no inicio
    {
        LIS_RemoverInicio(lista);
    }
    else if(indice == lista->tamanho)//remover no final
    {
        LIS_RemoverFim(lista);
    }
    else if(indice > lista->tamanho)//tentando remover numa posicao maior que o tamanho do vetor
    {
        return -1;
    }
    else//remover em uma outra posicao
    {
        int i = 1;

        No iterador = lista->cabeca->proximo;//pega o primeiro elemento da lista para ser o iterador

        while(iterador != lista->cauda)//vai percorrer a lista até chegar na cauda
        {
            if(i == indice)//se o indice for o mesmo da posicao indicada, remover o nó e retornar o seu valor
            {
                iterador->proximo->anterior = iterador->anterior;
                iterador->anterior->proximo = iterador->proximo;

                int valor;

                valor = iterador->valor;

                lista->tamanho -= 1;

                DestruirNo(iterador);

                return valor;
            }
            else//se o indice for diferente da posicao indicada, atualizar o iterador e incrementar o indice
            {
                iterador = iterador->proximo;
                i += 1;
            }
        }
    }  
} 


/*
    Função que ordena a lista. (Obs.: Implemente os algoritmos: selection sort, insertion sort e bubble sort.)
 */
void LIS_Ordenar(Lista lista)//selection sort
{
    if(lista->tamanho > 1)//se a lista tiver tamanho 0 ou 1, não precisa ser ordenada
    {
	    int i, j, min;
        No aux, no_min, no_i, no_j;
	
        for(i = 0; i < (lista->tamanho-1); i++)
        {
        	min = i;

		for(j = (i+1); j < (lista->tamanho); j++)
		{
		    no_j = LIS_PegarNo(lista, j);
		    no_min = LIS_PegarNo(lista, min);

		    if(no_j->valor < no_min->valor)
			{
				//min = j;
			}
		}

		//no_i = LIS_PegarNo(lista, i);

		//if(no_i->valor != no_min->valor)
		//{
		    /*aux = no_i;

		    //colocar no_i no lugar do min;
		    no_i->proximo = min->proximo;
		    no_i->anterior = min->anterior;

		    min->anterior->proximo = no_i;
		    min->proximo->anterior = no_i;

		    //colocar min no lugar do no_i
		    min->proximo = aux->proximo;
		    min->anterior = aux->anterior;

		    aux->anterior->proximo = min;
		    aux->proximo->anterior = min;*/
		    
		//}
	    }
    }
}

/*
    Função que intercala duas listas ordenadas, retornando uma nova lista contendo a intercalação das duas listas de entrada.
 */
Lista LIS_Intercalar(Lista lista1, Lista lista2)
{
    return NULL;
}

/*
    Função que verifica se uma determinda instância da estrutura lista obedece a todas suas invariantes.
 */
LIS_tpVerificacao LIS_Verificar(Lista lista)
{
    if( lista->cabeca == NULL )
    {
        return LIS_CabecaNula;
    }
    
    if( lista->cauda == NULL )
    {
        return LIS_CaudaNula;
    }
    
    if( lista->cabeca->anterior != NULL )
    {
        return LIS_CabecaAnterior;
    }
    
    
    if( lista->cauda->proximo != NULL )
    {
        return LIS_CaudaProximo;
    }
    
    if(lista->tamanho == 0)
    {
        if( lista->cabeca->proximo != lista->cauda )
        {
            return LIS_CabecaCauda;
        }
        
        if( lista->cabeca != lista->cauda->anterior )
        {
            return LIS_CabecaCauda;
        }
    }
    else
    {
        for(No i = lista->cabeca->proximo; i != lista->cauda; i=i->proximo)
        {
            if( i->proximo->anterior != i )
            {
                return LIS_EncadeamentoErrado;
            }
            if( i->anterior->proximo != i )
            {
                return LIS_EncadeamentoErrado;
            }
        }
    }
    
    return LIS_OK;
}

/*
    Função que imprime todos os elementos de uma lista.
 */
void LIS_Imprimir(Lista lista)
{
    std::cout << "Tamanho " << lista->tamanho << std::endl;
    for(No i = lista->cabeca->proximo; i != lista->cauda; i = i->proximo)
    {
        std::cout << "[" << i->valor << "]->";
    }
    std::cout << std::endl;
}

/**
 Função que libera a memória de uma instância da estrutura Lista, liberando a memória de todos os nós encadeados na lista, incluindo os nós cabeça e cauda.
 */
void LIS_Destruir(Lista lista)
{
    No atual = lista->cabeca;
    while( atual != NULL )
    {
        No destruido = atual;
        atual = atual->proximo;
        DestruirNo(destruido);
    }
    free(lista);
}

/*
 Função que aloca a memória para um nó e inicializa os atributos do nó.
 */
No CriarNo(int v)
{
    No no = (No) malloc( sizeof( tpNo ) );
    if( no == NULL )
    {
        return NULL;
    }
    
    no->proximo = NULL;
    no->anterior = NULL;
    
    no->valor = v;
    
    return no;
}

/*
 Função que libera a memória alocada para um nó.
 */
bool DestruirNo(No no)
{
    free(no);
    return true;
}


