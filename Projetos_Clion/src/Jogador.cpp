#include "../Include/Jogador.h"

//Criar Jogador com o ID, Nome, Morada e Idade referente no ficheiro "pessoas.txt"
Jogador::Jogador(int ID,string Nome_Jogador ,string Morada,int Idade)
{
    this->ID = ID;
    this->Nome_Jogador = Nome_Jogador;
    this->Morada = Morada;
    this->Idade = Idade;
    this->N_Premios = 0;
    this->Tempo_Total = 0;
}

//destuidor de jogadores mas a fun��o est� implementada no casino.c
Jogador::~Jogador()
{
}

//devolve o numero de jogadores
int Jogador::GetCount() const{
    return count;
}

//devolve o id de um jogador
int Jogador::get_ID() const{
    return ID;
}

//devolve o nome de um jogador
string Jogador::get_Nome_Jogador() const{
    return Nome_Jogador;
}

//devovle a morada de um jogador
string Jogador::get_Morada() const {
    return Morada;
}

//devolve a idade de um jogador
int Jogador::get_Idade() const{
    return Idade;
}

//Mostra a informa��o toda de um jogador
void Jogador::Show_Jogador() {
    cout << "ID: " << ID << endl;
    cout << "Nome: " << Nome_Jogador << endl;
    cout << "Morada: " << Morada << endl;
    cout << "Idade: " << Idade << endl;
}



//efsefsefsef
