// CLASS txt
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <ostream>
#include <cstring>
#include <vector>
#include <math.h>

 using namespace std;
 
class IndiceInvertido{
	public:
			
		
	
	void TratamentoString ( string *texto );
	
	void InicializaMap (); // PRIVADA OU PUBLICA?
	
	void AcrescentarDocumento ();
	
	float idf (string palavraBusca);// inverso da frequencia do termo - 
	//importância de uma palavra Px dentro da coleção de documentos
	
	int tf(string palavraBusca, char Documento);  // frequencia do termo - 
	//tf é a quantidade de vezes que uma palavra (palavraBusca) aparece dentro de um determinado documento (nomeDocumento);
	
	float similaridade(string Documento, string palavraBusca);
	
	//int get__numDocumentosTotais();
	
	private:
		
	vector<char[50]> Arquivos;	
		
	map<string, map<string,int> > _IndiceBusca;
	map<string, map<string,int> > ::iterator _itmap;
	
	//int _numDocumentosTotais;
	
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


// IMPLEMENTANDO
void IndiceInvertido::InicializaMap (){
	ifstream arquivo;
	string palavra;
	int i;
	char Texto[50] = "d1.txt";
	
	//ENCONTRAR MODO DE ABRIR ARQUIVO COM NOME DE ENTRADA EXTERNA
	arquivo.open(Texto);//
	
	if(arquivo.is_open()) {
		cout<< " -- ARQUIVO ABERTO COM SUCESSO -- \n"  ;
		cout<< " -- lendo palavras -- \n";
		//LEITURA DE CADA PALAVRA NO DOCUMENTO PARA A VARIAVEL PALAVRA
		while(arquivo >> palavra){			
			TratamentoString( &palavra);
			_itmap=_IndiceBusca.find(palavra);
			//cout<<palavra<<" corrigido"<<endl;
			if(_itmap==_IndiceBusca.end()){
				//INSERE A PALAVRA AO MAP DUPLO COM TEXTO ONDE SE LOCALIZA E O NUMERO DE REPETI?OES NO TEXTO
				_IndiceBusca[palavra][Texto]=1;
				}
			else{
				//PALAVRA JA EXISTE NO MAP
				_IndiceBusca[palavra][Texto]++;
			}	
		}
	}
	else {
		cout << " NAO FOI POSSIVEL ABRIR O ARQUIVO" << endl;
	}
	// fechamento de arquivo
	arquivo.close();
	
	//TESTE IMPRESSAO DO MAP CONSTRUIDO
	arquivo.open(Texto);
	while(arquivo >> palavra){
		TratamentoString( &palavra);
		cout << palavra <<":"<< _IndiceBusca[palavra][Texto] <<endl;
	}
	arquivo.close();
	//FIM TESTE
}

void IndiceInvertido::AcrescentarDocumento (){
	
	int i,Ndocs;
	char NomeDoc[50];
	cout<<" Digite o numero de documentos a inserir:"<<endl;
	cin >> Ndocs;
	for(i=0;i<Ndocs;i++){
		cout<<"Insira o nome do documento na forma : documento1.txt "<<endl;
		cin >>NomeDoc;
		//FALTA ATRIBUIR O NOME DOC AO VETOR ARQUIVOS
		InicializaMap();
		
		Arquivos[Arquivos.size()];
		//_numDocumentosTotais++;
	}
}

float IndiceInvertido::idf (string palavraBusca){
	// inverso da frequencia do termo - 
	//importância de uma palavra Px dentro da coleção de documentos
	_itmap=_IndiceBusca.find(palavraBusca);

	if(_itmap==_IndiceBusca.end()){
		//a palavra existe em algum documento
		return  log10((Arquivos.size()/(_IndiceBusca[palavraBusca].size())));
		}
	else{
	//a palavra  nao existe em nenhum documento
	return 0;
	}	

};
	
int IndiceInvertido::tf(string palavraBusca, char Documento){
	//tf é a quantidade de vezes que uma palavra (palavraBusca) aparece dentro de um determinado documento (nomeDocumento);
	_itmap=_IndiceBusca.find(palavraBusca);
	if(_itmap==_IndiceBusca.end()){
		return 0;
	}
	return _IndiceBusca[palavraBusca][Documento];
}; // retorna o numero de documentos em que a palavra apararece por documento


float IndiceInvertido::similaridade(string Documento, string palavraBusca){
	/*dj = documento
	Pi = palavra
	qi = busca/consulta solicitada
	
		
	
	*/
};


