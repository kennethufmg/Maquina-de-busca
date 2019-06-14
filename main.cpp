// CLASS txt
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <ostream>
#include <cstring>
#include <vector>
#include "IndiceInvertido.h"





int main(){
	
	IndiceInvertido *Busca =new IndiceInvertido();
	cout<<"Adicione arquivos para imporcacao inserindo seu nome no arquivo documentos.tx"<<endl;
	cout<<"insira um nome de arquivo por linha"<<endl;
	
	Busca->AcrescentarDocumento();
	cout<<" Insira a busca que deseja relizar:"<<endl;
	
	Busca->Busca();
	
	cout<<" Encontramos os textos:"<<endl;
	
	Busca->ranking();
	
	return 0;
}
