#ifndef MAQUINA_H
#define MAQUINA_H

#pragma once

#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "Jogador.h"

using namespace std;

class Maquina
{
    //posicao da maquina x,y no casino
    int posicao_x;
    int posicao_y;

    //estado da maquina (ON, OFF, REPAIR)
    string estado;

    //tempo de opera��o da maquina
    float tempo_operacao;

    string ID;
    float WINRATE = 1.0;
    int PREMIO;
    int X;
    int Y;
    int TEMPAVISO;
    string Modo;
    string Tipo;

public:
    string GetID() const { return ID; };
    string GetTipo() const;
    float GetTempoOperacao() const { return tempo_operacao; }

    float getWinRate() {
        return WINRATE;
    }

    float writewinrate() {
        cout << "WinRate: " << WINRATE << endl;
    }

    float setWinRate() {
        cout << "Digite a WinRate (0 - 1): ";
        while (!(cin >> WINRATE) || WINRATE < 0 || WINRATE > 1) {
            cout << "Valor inv�lido. Digite um n�mero entre 0 e 1: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        cout << "Winrate alterada para: " << WINRATE << endl;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Pressione Enter para continuar...";
        cin.get();

        return WINRATE;
    }

    void setWinRatestart(float value) {
        WINRATE = value;
    }


    // Atualiza o tempo de opera��o da m�quina
    void AtualizarTempoOperacao(float tempo) {
        tempo_operacao += tempo;
    }

    string GetEstado() const { return estado; };
    Maquina(string id, int probabilidadeGanhar, int premio, int x, int y, int tempAviso);
    ~Maquina();
    void Escolheramalta();
    virtual void Jogobase(Jogador* jogador, float winRate);
    void Show_maquina();
    void AdicionarMaquinaAvariada(Maquina* maquina);
};

// heran�a ------------------------------------>

class ClassicSlots : public Maquina {
public:
    ClassicSlots(string id, int probabilidadeGanhar, int premio, int x, int y, int tempAviso);
    virtual ~ClassicSlots();
};

class Slots_tematicos : public Maquina {
public:
    Slots_tematicos(string id, int probabilidadeGanhar, int premio, int x, int y, int tempAviso);
    virtual ~Slots_tematicos();
};

class Slots_de_recursos : public Maquina {
public:
    Slots_de_recursos(string id, int probabilidadeGanhar, int premio, int x, int y, int tempAviso);
    virtual ~Slots_de_recursos();
};

class Blackjack : public Maquina {
public:
    Blackjack(string id, int probabilidadeGanhar, int premio, int x, int y, int tempAviso);
    virtual ~Blackjack();
};

class Roleta : public Maquina {
public:
    Roleta(string id, int probabilidadeGanhar, int premio, int x, int y, int tempAviso);
    virtual ~Roleta();
};

class Variantes_Poker : public Maquina {
public:
    Variantes_Poker(string id, int probabilidadeGanhar, int premio, int x, int y, int tempAviso);
    virtual ~Variantes_Poker();
};


#endif // MAQUINA_H