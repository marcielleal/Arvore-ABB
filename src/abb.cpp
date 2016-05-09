#include <abb.h>
#include <iostream>
#include <math.h>
#include <queue>

ABB::ABB()
{
	this->size=0;
	this->height=0;
	this->root = nullptr;
}

ABB::~ABB()
{
	if(this->root != nullptr)
	{
		delete this->root;
	}
}


ABB::Node * ABB::search_aux(int key, int * f)
{
	if(this->root == nullptr){
		* f = 0;
		return nullptr;
	}

	Node * pt = root;
	bool end = false;

	while(!end)
	{
		if(pt->key == key)
		{
			end = true;
			* f = 1;
		}
		else if (key < pt->key)
		{
			if(pt->left == nullptr)
			{
				end = true;
				* f = 2;
			}
			else
			{
				pt = pt->left;
			}			
		}
		else
		{
			if(pt->right == nullptr)
			{
				end = true;
				* f = 3;
			}
			else
			{
				pt = pt->right;
			}
		}
	}
	return pt;
}

ABB::Node * ABB::search(int key)
{
	int f;
	Node * pt = this->search_aux(key, &f);
	if(f == 1)
	{
		return pt;
	}
	else
	{
		std::cout << "Elemento não encontrado";
		return nullptr;
	}
}

void ABB::insert(int key)
{
	int f = 0;
	Node * pt = search_aux(key, &f);

	if(f == 1)
	{
		std::cout << "Elemento já existe!";
	}
	else
	{
		Node * newNode = new Node();
		newNode->key = key;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->parent = nullptr;
		newNode->leftSize = 0;
		newNode->rightSize = 0;

		if(f == 0)
		{
			this->root = newNode;
		}
		else
		{
			newNode->parent = pt;

			if(f == 2)
				pt->left = newNode;
			else
				pt->right = newNode;
		} 

		pt =  newNode;
		int height = 1;
		while(pt->parent != nullptr)
		{
			if(pt->parent->left == pt)
				pt->parent->leftSize++;
			else
				pt->parent->rightSize++;

			pt = pt->parent;
			height++;
		}

		if(height > this->height)
			this->height = height;

		this->size++;
	}


}

int ABB::nElement(int n)
{
	if(n > this->size)
	{
		std::cout << "Valor inválido";
		return 0;
	}

	int pos = n;
	int key = 0;
	Node * pt = this->root;
	bool end = false;

	int k = 0;
	while(!end)
	{
		k++;
		if(pt->leftSize + 1 == pos)
		{
			key = pt->key;
			end = true;
			std::cout << "Encontrou!" << std::endl;
		}
		else if(pt->leftSize >= pos)
		{
			pt = pt->left;
			std::cout << "Esquerda!" << std::endl;
		}
		else
		{
			pos = pos - (pt->leftSize + 1);
			pt = pt->right;
			std::cout << "Direita!" << std::endl;
		}
	}

	return key;
}

int ABB::position(int key)
{
	if(this->root == nullptr){
		std::cout << "Árvore vazia!";
		return 0;
	}

	Node * pt = root;
	bool end = false;
	int pos = 0;

	while(!end)
	{
		if(pt->key == key)
		{
			pos += pt->leftSize + 1;
			end = true;
		}
		else if (key < pt->key)
		{
			if(pt->left == nullptr)
			{
				end = true;
				pos = 0;
			}
			else
			{
				pt = pt->left;
			}
		}
		else
		{
			if(pt->right == nullptr)
			{
				end = true;
				pos = 0;
			}
			else
			{
				pos += pt->leftSize + 1;
				pt = pt->right;
			}
		}
	}

	return pos;
}

int ABB::mediana()
{
	double n = this->size;
	return nElement(ceil(n/2));
}


void ABB::print()
{
	if(this->root == nullptr){
		std::cout << "Árvore vazia!";
	}

	std::queue <Node *> fila;
	Node * pt = this->root;
	fila.push(pt);
	std::cout << "Tamanho: " << this->size << ", Altura: " << this->height << std::endl;
	while(!fila.empty())
	{
		Node * aux = fila.front();
		fila.pop();

		std::cout << "End.: " << aux << ", Key: " << aux->key <<
			", Left: " << aux->left << "[" << aux->leftSize << "]"  <<
			", Right: " << aux->right << "[" << aux->rightSize << "]" << std::endl;

		if(aux->left != nullptr)
		{
			fila.push(aux->left);
		}			
		if(aux->right != nullptr)
		{
			fila.push(aux->right);
		}
	}
}

bool ABB::ehCheia(){
	float valorTeste=pow(2,this->height)-1;
	if(valorTeste==this->size)
		return true;
	return false;
}


bool ABB::remove(int key)
{
	if(this->root == nullptr)
 		return false;
 	else{
		int f=0;
 		Node* pt = search_aux(key, &f);
 		if(f!=1)
			std::cout<<"Elemento inexistente!"<<std::endl;
		else{
			if(pt->right==nullptr && pt->left==nullptr){	//folha
				Node* ptRem=pt;
				
				//updateRemoval
				int height = 1;
				while(pt->parent != nullptr){
					if(pt->parent->left == pt)
						pt->parent->leftSize--;
					else
						pt->parent->rightSize--;

					pt = pt->parent;
					height++;
				}

				if(height < this->height)
					this->height = height;
				this->size--;	
				if(pt!=this->root)
					this->root=pt;
				//
				
				if(ptRem->parent->left==ptRem)
					pt->parent->left=nullptr;
				else
					pt->parent->right=nullptr;
					
				
									
				delete ptRem;
				return true;
			}else if(pt->left!=nullptr && pt->right!=nullptr){
				Node* ptAux=pt;	//Não será alterado
				std::cout<<"SAASAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA____________________________________________________________________";
				/*-- Achando maior elemento */
				pt=pt->left;
				while(pt->right!=nullptr){
					pt=pt->right;
				}
				//Faz o pai apontar pra nulo e troca o valor pelo do maior elemento
				pt->parent->right=nullptr;
				ptAux->key=pt->key;
				

				//updateRemoval
				int height = 1;
				while(pt->parent != nullptr){
					if(pt->parent->left == pt)
						pt->parent->leftSize--;
					else
						pt->parent->rightSize--;

					pt = pt->parent;
					height++;
				}

				if(height < this->height)
					this->height = height;
				if(pt!=this->root)
					this->root=pt;
				this->size--;
				
				delete pt;
				return true;
			}else if(pt->left==nullptr||pt->right==nullptr){
				Node* ptRem=pt;	//Não será alterado
				
				//Selecionando o elento com subárvore nula
				if(pt->left==nullptr)
					pt=pt->right;
				else
					pt=pt->left;
				
				//Ligo o pai ao neto e o neto ao pai
				if(ptRem->parent!=nullptr){
					if(ptRem->parent->left==ptRem)
						ptRem->parent->left=pt;
					else
						ptRem->parent->right=pt;
				}
				pt->parent=ptRem->parent;
				
				//updateRemoval
				int height = 1;
				while(pt->parent != nullptr){
					if(pt->parent->left == pt)
						pt->parent->leftSize--;
					else
						pt->parent->rightSize--;

					pt = pt->parent;
					height++;
				}

				if(height < this->height)
					this->height = height;
				this->size--;	
				if(pt!=this->root)
					this->root=pt;
				//
				

				delete ptRem;
				return true;		
			}
			else{
				std::cout<<"ERRO NA REMOÇÃO"<<std::endl;
				return false;
			}
		}
	}return false;
}

std::string ABB::toString(){
	std::string buff("");
	if(this->root == nullptr)
		return "{ }";
	
	std::queue <Node*> fila;
	Node* pt = this->root;
	fila.push(pt);
	
	buff+="{";
	while(!fila.empty()){
		Node* aux = fila.front();
		fila.pop();
		
		buff+=std::to_string(aux->key);

		if(aux->left != nullptr)
			fila.push(aux->left);
					
		if(aux->right != nullptr)
			fila.push(aux->right);
			
		if(!fila.empty())
			buff+=",";
	}
	
	buff+="}\n";
	return buff;
}

