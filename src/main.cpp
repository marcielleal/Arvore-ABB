#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <abb.h>

int main (int argc, char *argv[]){
    std::ifstream inputFileA;
    std::ifstream inputFileC;
    std::string b;
	std::cout<<argv[1];
    
    if(argc<2){
        std::cout<<"Argumentos insuficientes!"<<std::endl;
        std::cout<<"É preciso a inserção de mais argumentos!"<<std::endl;
        std::cout<<"A forma geral de chamada do programa é:"<<std::endl;
        std::cout<<"./bin/main arquivo_entrada arquivo_de_comandos"<<std::endl;
        return 1;
    }

	inputFileA.open(argv[1],std::ifstream::in);
	inputFileC.open(argv[2],std::ifstream::in);
	
	if(!inputFileA.is_open()||!inputFileC.is_open()) {
		if(!inputFileA.is_open())
			std::cout<<"Erro ao abrir o arquivo "<<argv[1]<<std::endl;
		if(!inputFileC.is_open())
			std::cout<<"Erro ao abrir o arquivo "<<argv[2]<<std::endl;
		return 1;
	}
	
	ABB abb;
	
	std::string input;

	std::getline(inputFileA,input);
	std::stringstream stream(input);
	int a;
	while(1){
		stream>>a;
		abb.insert(a);
		if(!stream)
			break;
	}

    
    while(!inputFileC.fail()){
		std::getline(inputFileC,input);
		
		std::stringstream ss;
		if(input.find("ENESIMO")!=std::string::npos){
			int a;
			ss<<input;
			ss>>a;
			std::cout<<abb.nElement(a);
		}
		else if(input.find("POSICAO")!=std::string::npos){
			int a;
			ss<<input;
			ss>>a;
			std::cout<<abb.position(a);
		}
		else if(input.find("MEDIANA")!=std::string::npos){
			std::cout<<abb.mediana();
		}
		else if(input.find("CHEIA")!=std::string::npos){
			if(abb.ehCheia())
				std::cout<<"É cheia"<<std::endl;
			else	
				std::cout<<"Não é cheia"<<std::endl;
		}
		else if(input.find("IMPRIMA")!=std::string::npos){
			std::cout<<abb.toString();
		}
		else if(input.find("REMOVA")!=std::string::npos){
			int a;
			ss<<input;
			ss>>a;
			abb.remove(a);
		}
	}

	inputFileA.close();
	inputFileC.close();

    return 0;
}
