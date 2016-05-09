#include <abb.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	std::cout << "Teste: \n";

	ABB abb;

	abb.insert(1);
	abb.insert(2);
	abb.insert(4);
	abb.insert(5);
	abb.insert(9);

	abb.print();

    	std::cout << "2º Elemento: " << abb.nElement(2) << std::endl;
	std::cout << "Posição do 4: " << abb.position(4) << std::endl;
	std::cout << "Mediana: " << abb.mediana() << std::endl;
	std::cout<<"TAMANHO   "<<abb.getSize()<<"ALTURA  "<<
	abb.getHeight();

	
	abb.remove(1);
	abb.toString();
	return 0;
}
