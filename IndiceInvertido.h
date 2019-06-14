// CLASS txt
#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <ostream>
#include <vector>
#include <math.h>

 using namespace std;
 
class IndiceInvertido{
	public:
			
	void TratamentoString ( string *texto );
	
	void InicializaMap (map<int, string> &Documento); // PRIVADA OU PUBLICA?
	
	void AcrescentarDocumento ();
	
	float idf (string palavraBusca );// inverso da frequencia do termo - 
	//importância de uma palavra Px dentro da coleção de documentos
	
	float tf(string palavraBusca, string Documento);  // frequencia do termo - 
	//tf é a quantidade de vezes que uma palavra (palavraBusca) aparece dentro de um determinado documento (nomeDocumento);
	
	float similaridade(string Documento);
	
	float W(string palavraBusca, string Documento);
	
	void const imprimeMapBusca();
	
	void const imprimeMapPalavras();
	
	void Busca();
	
	void IniciaMapBusca(string palavra);
	
	void ranking ();
	
	private:
	
	map<string, float> _mapNT;
	
	string _DocBusca = "busca";	
		
	vector<string> _Arquivos;
	
	map<string, float> _mapRank;
		
	map<string, map<string,float> > _IndiceBusca;
	
	map<string, map<string,float> > ::iterator _itmap;
	
	map<string, map<string,float> > _BuscaSolicitada;
	
};

void IndiceInvertido::TratamentoString( string *texto){
	// REMOVE SINAIS DO TIPO !@?& DA STRING LIDA;
	// transforma todas as letras da string em minuscula
	
		int i,j,k;
		char caracter;
		string strAuxiliar;
		strAuxiliar = *texto;
		
		for(i=0;i<texto->length();i++){
			//TRANSFORMA MAISCULA EM MINUSCULA
			caracter= (char)strAuxiliar[i];
			strAuxiliar[i]=tolower(caracter);
			//REMOVE PONTUAÇÃO E JUNTA PALAVRAS DIVIDAS
			if((isalpha(caracter)==false)&&(caracter='-')){
				k=strAuxiliar.length();
				k=k-1;
				for(j=i;j<k;j++){
					strAuxiliar[j]=strAuxiliar[j+1];
				}
			}
			if(isalpha(caracter)==false){				
				k=strAuxiliar.length();
				strAuxiliar.resize (k-1);
			}
			*texto=strAuxiliar;		
		}
}

void IndiceInvertido::InicializaMap (map<int,string> &Documento){
	ifstream arquivo;
	string palavra;
	string palavraBusca;
	string nomeTexto;
	string nomeAux;
	map<int,string> :: iterator it;
	
	for ( auto it = Documento.cbegin(); it != Documento.cend(); ++it) {
        //cout << "{" << (*it).first << ": " << (*it).second << "}\n";-------------Testa a entrada das palavras do map 
		nomeTexto=(*it).second;
        cout<<"Esse e o arquivo: "<<nomeTexto<<endl;
        arquivo.open(nomeTexto);
	if(arquivo.is_open()) {
		
		_Arquivos.push_back(nomeTexto);
		cout<< " -- ARQUIVO ABERTO COM SUCESSO -- \n"  ;
		cout<< " -- lendo palavras -- \n";
		//LEITURA DE CADA PALAVRA NO DOCUMENTO PARA A VARIAVEL PALAVRA
		while(arquivo >> palavra){
			int inter=0;
			TratamentoString( &palavra);
			_itmap=_IndiceBusca.find(palavra);
			if(_itmap==_IndiceBusca.end()){
				//INSERE A PALAVRA AO MAP DUPLO COM TEXTO ONDE SE LOCALIZA E O NUMERO DE REPETI?OES NO TEXTO
				nomeAux=nomeTexto;
				TratamentoString(&nomeAux);
				_IndiceBusca[palavra][nomeAux]=1;
			}
			else{
				nomeAux=nomeTexto;
				TratamentoString(&nomeAux);
				//PALAVRA JA EXISTE NO MAP
				_IndiceBusca[palavra][nomeAux]=_IndiceBusca[palavra][nomeAux]+1;
				
			}	
		}	
		}
		
	else {
		cout << " NAO FOI POSSIVEL ABRIR O ARQUIVO" << endl;
	}
	// fechamento de arquivo
	arquivo.close();
}
};

void IndiceInvertido::AcrescentarDocumento (){
	ifstream in("documentos.txt");
	typedef map<int,string> vetor;
	vetor ler;
	char str[255];
	int quantLinhas=0;
	vetor::iterator pos;
	
  	if(!in) {
    cout << "Cannot open input file.\n";
    cout<<"ERRO";
  	}
	while(in) {
		in.getline(str, 255);  // delim defaults to '\n'
		ler.insert(std::make_pair(quantLinhas,str));
		quantLinhas++;
	}
	InicializaMap (ler);
}

float IndiceInvertido::idf (string palavraBusca){
	// inverso da frequencia do termo - 
	//importância de uma palavra Px dentro da coleção de documentos
	_itmap=_IndiceBusca.find(palavraBusca);
	float ln;
	
	if(_itmap!=_IndiceBusca.end()){
		ln=  log((float)((float)_Arquivos.size()/(float)(_IndiceBusca[palavraBusca].size())));
		return ln;
		}
	else{	
	//a palavra  nao existe em nenhum documento
	return 0;
	}	
};
	
float IndiceInvertido::tf(string palavraBusca, string Documento){
	string nomeAux;
	float n;
	map<string, map<string,int> > *apontador;
	//tf é a quantidade de vezes que uma palavra (palavraBusca) aparece dentro de um determinado documento (nomeDocumento);
	if(Documento=="busca"){
		_itmap=_BuscaSolicitada.find(palavraBusca);
		if(_itmap==_BuscaSolicitada.end()){
			return 0.0;	
		}
		else if(_itmap!=_BuscaSolicitada.end()){
				nomeAux=Documento;
				TratamentoString(&nomeAux);
			return _BuscaSolicitada[palavraBusca][nomeAux];
		}
	}
	
	else{ 
		_itmap=_IndiceBusca.find(palavraBusca);
		if(_itmap==_IndiceBusca.end()){
			return 0.0;	
		}
		else {
		//PROBLEMA CRITICO
			nomeAux=Documento;
			TratamentoString(&nomeAux);
			//cout<<_IndiceBusca[palavraBusca][nomeAux]<<endl;
			return _IndiceBusca[palavraBusca][nomeAux];
		}
	}
}; // retorna o numero de documentos em que a palavra apararece por documento

float IndiceInvertido::similaridade(string Documento){
	//CALCULO DO SIM DO CONJUNTO TEXTO DA BUSCA EM UM DETERMINADO DOCUMENTO
	
	float sim = 0.0;
	map<string, map<string,float> > ::iterator itmap2;
	string palavraNaBusca;
	float w1,w3,w4;
	w1=0.0;w3=0.0;w4=0.0;
	
	for (itmap2=_BuscaSolicitada.begin();itmap2!=_BuscaSolicitada.end();itmap2++){
		//cout<<"documento: "<< Documento<<endl;
		 w1= w1 + (W(Documento,itmap2->first )* W(_DocBusca,itmap2->first ));
		 w3= w3 + (float)pow(W(Documento,itmap2->first),2.0) ;
		 w4= w4 + (float)pow(W(_DocBusca,itmap2->first),2.0) ;
	}
	//cout<<"w1:"<<w1<<"w3:"<<w3<<"w4:"<<w4<<endl;
	
	if (((w3)*(w4))==0.0){
		return 0.0;
	}
	
	else {
		sim = float((float)(w1)/(float)(sqrt(w3)*sqrt(w4)));
		return (float)sim;
	}
};

float IndiceInvertido ::  W (string Documento, string palavraBusca){
	
	return idf( palavraBusca) * tf(palavraBusca,Documento);
	
};

void const IndiceInvertido :: imprimeMapBusca(){
		_itmap= _BuscaSolicitada.begin();
		for(_itmap= _BuscaSolicitada.begin();_itmap!=_BuscaSolicitada.end();_itmap++){
			cout << _itmap->first <<endl;
		}	
};

void const IndiceInvertido :: imprimeMapPalavras(){
	_itmap= _IndiceBusca.begin();
		for(_itmap= _IndiceBusca.begin();_itmap!=_IndiceBusca.end();_itmap++){
			cout << _itmap->first <<endl;
		}	
}

void IndiceInvertido ::Busca(){
	string palavra;
	char palavra2[500];
	char * c;
	gets(palavra2);
	c = strtok(palavra2," \0");
	while(c!=NULL){
		palavra=(string)c;
		c = strtok(NULL," \0");
		TratamentoString(&palavra);
		IniciaMapBusca(palavra);
	}
};	

void IndiceInvertido::IniciaMapBusca(string palavra){
	_itmap=_BuscaSolicitada.find(palavra);
			if(_itmap==_BuscaSolicitada.end()){
				//INSERE A PALAVRA AO MAP DUPLO COM TEXTO ONDE SE LOCALIZA E O NUMERO DE REPETICOES NO TEXTO
				_BuscaSolicitada[palavra][_DocBusca]=1;
				}
			else{
				//PALAVRA JA EXISTE NO MAP
				_BuscaSolicitada[palavra][_DocBusca]++;
			}	
};

void IndiceInvertido::ranking (){
	vector<string> ::iterator  itvector;
	string nomeAux;
	for(itvector=_Arquivos.begin();itvector!=_Arquivos.end();itvector++){
		
		//CACULA PARA TODOS OS DOCUMENTOS UM MAP CONTENDO O CONJUNTO MAP <NOME DOCUMENTO, SIM>
		// SALVA O O VALOR DE SIM NO  MAP _mapRank; 	
		nomeAux=*itvector;
		TratamentoString(&nomeAux);
		float simDoc;
		simDoc=similaridade(nomeAux);
		//cout<<nomeAux<<": simDoc= "<<simDoc<<" "<<endl;	
		_mapRank[nomeAux]=simDoc;
	} 
	
	// IMPRIME EM ORDEM DE SEMELHANÇA DOS TEXTOS
	cout<<"Ordem de maior similaridade dos documentos com a busca:"<<endl;
	map<string,float> ::iterator itImp;
	float AuxMaior=0.0;
	int j,i=1;
	for(j=0;j<_Arquivos.size();j++){
	
		for(itImp=_mapRank.begin(); itImp!=_mapRank.end(); itImp++){
			if( itImp->second> AuxMaior){
				AuxMaior= itImp->second;
			}
		}
		//cout<<"maior: "<<AuxMaior<<endl;
		for(itImp=_mapRank.begin(); itImp!=_mapRank.end(); itImp++){
			if(itImp->second==AuxMaior){
				if(AuxMaior!=0.0){
					cout<<i<<":"<<itImp->first<<endl;
					_mapRank.erase(itImp->first);
					i++;
					AuxMaior=0;
				}	
			}
		}
	}
	if(AuxMaior== 0.0){
		cout<<"Fim dos resultados"<<endl;
		
	}
	

};


