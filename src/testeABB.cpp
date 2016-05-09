#include <abb.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	std::cout << "Teste: \n";

	ABB abb;

	abb.insert(5);
	abb.insert(2);
	abb.insert(4);
	abb.insert(5);
	abb.insert(9);
	abb.insert(1);
	abb.insert(3);
	abb.insert(7);

	abb.print();

    std::cout << "2º Elemento: " << abb.nElement(2) << std::endl;
	std::cout << "Posição do 4: " << abb.position(4) << std::endl;
	std::cout << "Mediana: " << abb.mediana() << std::endl;

	abb.remove(5);
	abb.remove(9);
	std::cout<<abb.toString();
	return 0;
}
