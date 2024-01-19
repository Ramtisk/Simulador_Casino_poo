#ifndef CASINO_H
#define CASINO_H

#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <ctime>
#include "Jogador.h"
#include "Maquina.h"
#include "../xml/pugixml.hpp"

using namespace std;

class Casino
{

    list<Jogador *> List_Jogador;
    list<Maquina *> List_Maquina;
    list<Jogador *> List_A_Jogar;
    list<Maquina *> List_Maquina_avariada;

    string Nome_Casino;
    string Nome_Maquina;

public:

    enum ESTADO_CASINO
    {
        ABERTO,
        FECHADO
    };

    enum ESTADO_MAQUINA
    {
        FUNCIONAL,
        AVARIADO
    };

    ESTADO_CASINO EstadoC;
    // Listar o estado atual do Casino
    ESTADO_MAQUINA EstadoM;
    // Listar o estado atual das maquinas

    Casino(string Nome); //PLACEHOLDER

    ~Casino(); //PLACEHOLDER

    void mostrarNomeCasino() const {
        cout << Nome_Casino << "          |"<< endl;
    }

    //bool Casino::Load(const string &ficheiro);
    void  Declare_Casino_estado();

    void AdicionarMaquina(Maquina* maquina) {
        List_Maquina.push_back(maquina);
    }

    int Memoria_Total() const {
        int total = 0;

        for (const auto& maquina : List_Maquina) {
            // Adicione o tamanho da inst�ncia da Maquina � mem�ria total
            total += sizeof(*maquina);
        }

        for (const auto& jogador : List_Jogador) {
            // Adicione o tamanho da inst�ncia do Jogador � mem�ria total
            total += sizeof(*jogador);
        }

        return total;
    }


    const list<Maquina*>& GetListaMaquina() const;

    bool Add(Jogador *ut);
    bool Add(Maquina *m);

    void lerArquivoXML(const std::string& nomeArquivo, Casino& casino);
    Maquina* criarMaquina(string nomeMaquina, int probabilidadeGanhar, int premio, int x, int y, int tempAviso);

    void show(ostream &f = std::cout);
    ESTADO_MAQUINA Get_Estado(int id_maq);
    list<Maquina *> *Listar_Tipo(string Tipo, ostream &f);
    list<string> *Ranking_Dos_Fracos();
    list<string> *Ranking_Das_Mais_Trabalhadoras();
    list<Jogador *> *Jogadores_Mais_Frequentes(); // Fun��o que vai definir o jogador que teve mais intera��es com as m�quinas do casino no dado dia
    list<Jogador *> *Jogadores_Mais_Ganhos ();
    // void Casino::Relatorio(string fich_xml)
    // void Casino::SubirProbabilidadeVizinhas(Maquina *M_ganhou, float R, List<Maquina *> &lmvizinhas)
    bool LoadJogador(const string &ficheiro);
    void *MostrarInfoJogador(int numeroJogador, ostream &os) const;
    Jogador* EscolherJogadorAleatorio();
    Maquina* EscolherMaquinaAleatoria();
    Maquina* AdicionarMaquinaAvariada(Maquina* maquina);
    void InicializarMaquinas();
    bool Load(const string &ficheiro);
    void MenuPrincipal();
    void Escolheramalta();
    void Jogobase(Jogador* jogador, float winRate);
    void printVirtualTime(int &VHours,int &VMinutes);
    void Run(bool Debug);



};

#endif // CASINO_HPP
