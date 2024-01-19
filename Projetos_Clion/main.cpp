#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <locale>
#include <conio.h>
#include <chrono>
#include <thread>

#include "./Include/Casino.h"
#include "./Include/Jogador.h"
#include "./Include/Maquina.h"



using namespace std;

int main() {
    srand(time(0));

    setlocale(LC_ALL, "Portuguese_Portugal.1252");

    Casino("temp").MenuPrincipal();


    return 0;
}
