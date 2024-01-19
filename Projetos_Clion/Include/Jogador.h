#ifndef JOGADOR_H
#define JOGADOR_H


#pragma once

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <ctime>

class Maquina;
class Casino;

using namespace std;

class Jogador{

    int ID;
    string Nome_Jogador;
    string Morada;
    int Idade;
    int count;
    int N_Premios;

    //Tempo total de jogo .2F
    float Tempo_Total;

    //cada jogador est� associado a uma maquina
    Maquina *maquina;

public:
    Jogador(int ID,string Nome_Jogador ,string Morada,int Idade);
    ~Jogador();
    int GetCount() const;
    int get_ID() const;
    string get_Nome_Jogador() const;
    string get_Morada() const;
    int get_Idade() const;
    void Show_Jogador();
    float GetTempoTotal() const { return Tempo_Total; };
    void Count(int &result) const {
        result = count;
    }
    int GetNPremios() const {
        return N_Premios;
    }

};


#endif // JOGADOR_H