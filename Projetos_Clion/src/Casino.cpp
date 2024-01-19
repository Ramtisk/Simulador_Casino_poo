#include "../Include/Casino.h"


using namespace std;


//Cria��o de um casino
Casino::Casino(string Nome) //Construtor do Casino

{
    Nome_Casino = Nome;
    EstadoC = ESTADO_CASINO::ABERTO;
}

//Destrui��o do casino e a lista das pessoas e das maquinas
Casino::~Casino() //destrutor do Casino
{
    for (auto jogador : List_Jogador) {
        delete jogador;
    }
    List_Jogador.clear();
    cout << "Lista de jogadores limpa" << endl;

    // Limpar m�quinas
    for (auto maquina : List_Maquina) {
        delete maquina;
    }

}

//Devolve a lista das maquinas
const list<Maquina*>& Casino::GetListaMaquina() const {
    return List_Maquina;
}

//Adiciona um utilizador a lista de users
bool Casino::Add(Jogador *ut){
    if(ut){
        List_Jogador.push_back(ut);
        return true;
    }
    else
        return false;
}

//Adiciona uma maquina a lista de maquinas
bool Casino::Add(Maquina *m){
    if(m){
        List_Maquina.push_back(m);
        return true;
    }
    else
        return false;
}

//Fun��o que compara dois users para ver qual deles tem mais jogadas
bool CompareByCount(Jogador* u1, Jogador* u2) {
    return u1->GetCount() < u2->GetCount();
}


/*list<Jogador *> *Casino::Jogadores_Mais_Frequentes (){ //Fun��o que vai definir o jogador que teve mais intera��es com as m�quinas do casino no dado dia

    int count = 0;
    list<Jogador *> *LU = new list<Jogador *>;
    for(auto it = List_A_Jogar.begin(); it != List_A_Jogar.end(); it++){
        (*it)->Count(count);
        LU->push_back(*it);
    }
    LU->sort(CompareByCount);
    return LU;
}
*/

//Declara o estado do casino
void Casino::Declare_Casino_estado()
{
    if(EstadoC == ESTADO_CASINO::ABERTO)
        cout << "O casino est� aberto" << endl;
    else
        cout << "O casino est� fechado" << endl;

}

//Mostra a informa��o sobre o casino juntamente com a informa��o dos jogadores e maquinas
void Casino::show(ostream &f)
{
    cout << "Informa��es do Casino:" << endl;
    cout << "Nome: " << Nome_Casino << endl;
    cout << "Estado: " << (EstadoC == ABERTO ? "ABERTO" : "FECHADO") << endl;
    cout << "Quantidade de Jogadores: " << List_Jogador.size() << endl;
    cout << "Quantidade de M�quinas: " << List_Maquina.size() << endl;
    cout << "Quantidade de M�quinas avariadas: " << List_Maquina_avariada.size() << endl;
    cout << "\nPressione Enter para continuar...";
    cin.get();
    cout << "";
    cin.get();

    cout << "Detalhes dos Jogadores:" << endl;
    for (auto jogador : List_Jogador)
    {
        f << "ID: " << jogador->get_ID() << ", Nome: " << jogador->get_Nome_Jogador() << ", Morada: " << jogador->get_Morada() << ", Idade: " << jogador->get_Idade() << endl;
    }

    cout << "Detalhes das M�quinas:" << endl;
    for (auto maquina : List_Maquina)
    {
        // Imprima informa��es espec�ficas da m�quina, se necess�rio
    }

};


//carrega os jogadores do ficheiro "pessoas.txt"
bool Casino::LoadJogador(const string &ficheiro)
{
    int contador=0;
    std::ifstream file("pessoas.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            stringstream ss(line);
            string id, nome, localidade, idade_str;
            int idade, ID;

            if (getline(ss, id, '\t') && getline(ss, nome, '\t') && getline(ss, localidade, '\t') && getline(ss, idade_str, '\t'))
            {
                ID = stoi(id); // converte string para int
                idade = stoi(idade_str); // converte string para int
                //cout << "\n[" << idade_str <<"]--------";
                //idade = 33;
                Jogador *jogador = new Jogador(ID, nome, localidade, idade);
                List_Jogador.push_back(jogador);
            }
            //std::cout << line << std::endl;
            //if(contador++ > 10)
            //  break;

        }
        file.close();
    }
    else
    {
        std::cout << "Erro ao abrir o ficheiro" << std::endl;
    }
}


//Fun��o para mostrar quais as maquinas que mais trabalharam
list<string> *Casino::Ranking_Das_Mais_Trabalhadoras() {
    list<string> *ranking = new list<string>;

    // Criar uma c�pia da lista de m�quinas para ordena��o
    list<Maquina *> copia_maquinas = List_Maquina;

    // Ordenar a lista de m�quinas com base no tempo de opera��o
    copia_maquinas.sort([](Maquina *a, Maquina *b) {
        return a->GetTempoOperacao() > b->GetTempoOperacao();
    });

    // Adicionar informa��es ao ranking
    for (auto maquina : copia_maquinas) {
        string info = "ID: " + maquina->GetID() + ", Tempo de Opera��o: " + to_string(maquina->GetTempoOperacao());
        ranking->push_back(info);
    }

    return ranking;
}

//Fun��o para ver qual dos jogadores mais ganhou
list<Jogador *> *Casino::Jogadores_Mais_Ganhos() {
    list<Jogador *> *ranking = new list<Jogador *>;

    // Criar uma c�pia da lista de jogadores para ordena��o
    list<Jogador *> copia_jogadores = List_Jogador;

    // Ordenar a lista de jogadores com base no n�mero de pr�mios ganhos
    copia_jogadores.sort([](Jogador *a, Jogador *b) {
        return a->GetNPremios() > b->GetNPremios();
    });

    // Adicionar informa��es ao ranking
    for (auto jogador : copia_jogadores) {
        string info = "ID: " + to_string(jogador->get_ID()) + ", Pr�mios Ganhos: " + to_string(jogador->GetNPremios());
        ranking->push_back(jogador);
    }

    return ranking;
}

//lista o tipo de uma maquina
list<Maquina *> *Casino::Listar_Tipo(string Tipo, ostream &f)
{
    list<Maquina *> *maquinasDoTipo = new list<Maquina *>();

    for (auto maquina : List_Maquina)
    {
        if (maquina->GetTipo() == Tipo)
        {
            maquinasDoTipo->push_back(maquina);
        }
    }

    // Se um stream de sa�da foi fornecido, imprime as informa��es das m�quinas
    if (&f != &std::cout)
    {
        f << "M�quinas do tipo " << Tipo << ":" << endl;
        for (auto maquina : *maquinasDoTipo)
        {
            f << "ID: " << maquina->GetID() << ", Estado: " << maquina->GetEstado() << endl;
        }
    }

    return maquinasDoTipo;
}

//escolhe um jogador aleatorio da lista de jogadores
Jogador* Casino::EscolherJogadorAleatorio() {
    if (List_Jogador.empty()) {
        cout << "Lista de jogadores vazia.\n";
        return nullptr;
    }

    srand(time(0));
    int randomIndex = rand() % List_Jogador.size();
    auto it = List_Jogador.begin();
    advance(it, randomIndex);

    return *it;
}

//recebe uma maquina e adiciona na lista das maquinas avariadas
Maquina* Casino::AdicionarMaquinaAvariada(Maquina* maquina) {
    List_Maquina_avariada.push_back(maquina);
}

//Escolhe uma maquina aleatoria da lista de maquinas
Maquina* Casino::EscolherMaquinaAleatoria() {
    if (List_Maquina.empty()) {
        cout << "Lista de m�quinas vazia.\n";
        return nullptr;
    }

    srand(time(0));
    int randomIndex = rand() % List_Maquina.size();
    auto it = List_Maquina.begin();
    advance(it, randomIndex);

    return *it;
}

////Fun��o escolhe uma pessoa e uma maquina ao calhas, mostra as informa��es sobre os dois e junta-os dentro de uma fun��o jogobase para serem usados no final a maquina que foi escolhida aleatoriamente ainda tem chance de ficar estragada caso isso aconte�a entra na lista de maquinas estragadas
void Casino::Escolheramalta()
{
    Casino meuCasino("Casino Figueira");
    Maquina minhamaquina("TempID",0,0,0,0,0);
    cout << "Jogador Aleat�rio Escolhido:\n";
    Jogador* jogadorAleatorio = meuCasino.EscolherJogadorAleatorio();
    Maquina* maquinaaleatoria = meuCasino.EscolherMaquinaAleatoria();
    jogadorAleatorio->Show_Jogador();
    maquinaaleatoria->Show_maquina();
    maquinaaleatoria->Jogobase(jogadorAleatorio, maquinaaleatoria->getWinRate());
}

//recebe a informa��o retirada do ficheiro xml e cria uma maquina nova com essa informa��o
Maquina* Casino::criarMaquina(string nomeMaquina, int probabilidadeGanhar, int premio, int x, int y, int tempAviso) {
    // Aqui, com base no nome da m�quina, voc� decide qual tipo de m�quina criar
    if (nomeMaquina == "ClassicSlots") {
        return new ClassicSlots(nomeMaquina,probabilidadeGanhar, premio, x, y, tempAviso);
    } else if (nomeMaquina == "Slots_tematicos") {
        return new Slots_tematicos(nomeMaquina, probabilidadeGanhar, premio, x, y, tempAviso);
    }
    else if (nomeMaquina == "Roleta") {
        return new Roleta(nomeMaquina, probabilidadeGanhar, premio, x, y, tempAviso);
    }
    else if (nomeMaquina == "Blackjack") {
        return new Blackjack(nomeMaquina, probabilidadeGanhar, premio, x, y, tempAviso);
    }
    else if (nomeMaquina == "Variantes_Poker") {
        return new Variantes_Poker(nomeMaquina, probabilidadeGanhar, premio, x, y, tempAviso);
    }
    else if (nomeMaquina == "Slots_de_recursos") {
        return new Slots_de_recursos(nomeMaquina, probabilidadeGanhar, premio, x, y, tempAviso);
    }
    else {

        return nullptr;
    }
}

//fun��o para ler o arquivo xml
void Casino::lerArquivoXML(const std::string& nomeArquivo, Casino& casino) {
    pugi::xml_document doc;
    if (doc.load_file(nomeArquivo.c_str())) {
        pugi::xml_node definicoes = doc.child("DADOS").child("DEFINICOES");
        casino.Nome_Casino = definicoes.child_value("NOME");
        int maxJogadores = definicoes.child("MAX_JOG").text().as_int();
        int probabilidadeUsuario = definicoes.child("PROB_USER").text().as_int();
        int horaInicio = definicoes.child("HORA_INICIO").text().as_int();
        int horaFim = definicoes.child("HORA_FIM").text().as_int();

//        std::cout << "Nome do Casino: " << Nome_Casino << std::endl;
//        std::cout << "Nome da maquina: " << Nome_Maquina << std::endl;
//        std::cout << "M�ximo de Jogadores: " << maxJogadores << std::endl;
//        std::cout << "Probabilidade do Usu�rio: " << probabilidadeUsuario << std::endl;
//        std::cout << "Hora de In�cio: " << horaInicio << std::endl;
//        std::cout << "Hora de Fim: " << horaFim << std::endl;

        pugi::xml_node listaMaquinas = doc.child("DADOS").child("LISTA_MAQ");
        for (pugi::xml_node maquina : listaMaquinas.children("MAQUINA")) {
            std::string nomeMaquina = maquina.child_value("NOME");
            int probabilidadeGanhar = maquina.child("PROB_G").text().as_int();
            int premio = maquina.child("PREMIO").text().as_int();
            int x = maquina.child("X").text().as_int();
            int y = maquina.child("Y").text().as_int();
            int tempAviso = maquina.child("TEMP_AVISO").text().as_int();

            Maquina* novaMaquina = criarMaquina(nomeMaquina, probabilidadeGanhar, premio, x, y, tempAviso);

            // Adicione a nova m�quina � sua lista, se ela n�o for nula
            if (novaMaquina) {
                List_Maquina.push_back(novaMaquina);

                //novaMaquina->Show_maquina();
            }
        }
    } else {
        cout << "Erro ao carregar o arquivo XML." << std::endl;
    }
}



//fun��o principal onde tudo � chamado
void Casino::MenuPrincipal() {

    setlocale(LC_ALL, "Portuguese_Portugal.1252");
    srand(time(0));
    Casino meuCasino(Nome_Casino); //lembrar que o a cira��o assim automaticamente passa no destruir
    Maquina minhamaquina("temp",0,0,0,0,0);

    meuCasino.LoadJogador("pessoas.txt");

    meuCasino.lerArquivoXML("exemploxml.xml", meuCasino);

    list<Jogador*> listaDeJogadores;
    list<Maquina*> listadeMaquinas;
    list<Maquina*> List_Maquina_avariada;

    minhamaquina.setWinRatestart(0.4);
    int memoriaTotal = meuCasino.Memoria_Total();

    do {
        int opcao;

        std::cout << "|====================================|\n";
        std::cout << "|          ";
        meuCasino.mostrarNomeCasino();
        std::cout << "|====================================|\n";
        std::cout << "|                                    |\n";
        std::cout << "| 1. Abrir o casino                  |\n";
        std::cout << "| 2. Informa��es do casino           |\n";
        std::cout << "| 3. Mudar o winrate das maquinas    |\n";
        std::cout << "| 4. Mostrar o winrate               |\n";
        std::cout << "| 5. Abrir o casino todo junto       |\n";
        std::cout << "| 6. Memoria total a ser usada       |\n";
        std::cout << "| 0. Fechar casino                   |\n";
        std::cout << "|                                    |\n";
        std::cout << "|====================================|\n";

        std::cout << "\nO que pretende do Sistema ? ";
        std::cout << "\nOp��o: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
            {
                cout << "Jogador Aleat�rio Escolhido:\n";
                Jogador* jogadorAleatorio = meuCasino.EscolherJogadorAleatorio();
                Maquina* maquinaaleatoria = meuCasino.EscolherMaquinaAleatoria();
                jogadorAleatorio->Show_Jogador();
                maquinaaleatoria->Show_maquina();

                maquinaaleatoria->Jogobase(jogadorAleatorio, maquinaaleatoria->getWinRate());

                // Verificar se a tecla Enter foi pressionada
                while (!_kbhit());  // Aguardar at� que uma tecla seja pressionada
                int tecla = _getch();  // Obter o c�digo da tecla pressionada
                if (tecla == 13) {  // 13 � o c�digo ASCII para Enter
                    system("cls");  // Limpar a tela
                    // Adicione outras verifica��es ou condi��es para sair do loop, se necess�rio
                }
            }
                break;
            case 2:
                meuCasino.show();
                cout << "Pressione Enter para continuar..." << endl;
                for (auto& maquina : List_Maquina) {
                    minhamaquina.Show_maquina();
                }
                cout << "Pressione Enter para continuar...";
                cin.get();
                system("cls");
                break;
            case 3:
                minhamaquina.setWinRate();
                system("cls");
                break;
            case 4:
                minhamaquina.writewinrate();
                cout << "Pressione Enter para continuar..." << endl;
                cin.ignore(); // Limpar o buffer do teclado
                cin.get();
                system("cls");
                break;
            case 5:
                while (true) {
                    for (int i = 12; i <= 72; ++i) {  // Supondo que voc� quer repetir de 12 at� 24 (inclusive)

                        Jogador* jogadorAleatorio = meuCasino.EscolherJogadorAleatorio();
                        Maquina* maquinaaleatoria = meuCasino.EscolherMaquinaAleatoria();
                        jogadorAleatorio->Show_Jogador();
                        maquinaaleatoria->Show_maquina();

                        maquinaaleatoria->Jogobase(jogadorAleatorio, maquinaaleatoria->getWinRate());
                    }
                    while (!_kbhit()) {
                        // Aguardar at� que uma tecla seja pressionada
                    }

                    int tecla = _getch();  // Obter o c�digo da tecla pressionada
                    if (tecla == 13) {  // 13 � o c�digo ASCII para Enter
                        break;  // Sair do loop quando Enter for pressionado
                    }

                    system("cls");  // Limpar a tela
                    // Adicione outras verifica��es ou condi��es para sair do loop, se necess�rio
                }

                break;
            case 6:
                cout << "Mem�ria Total Usada: " << memoriaTotal << " bytes" << std::endl;
                cout << "Pressione Enter para continuar..." << endl;
                cin.ignore(); // Limpar o buffer do teclado
                cin.get();
                system("cls");
                break;
            case 0:
                cout << "\nObrigado Volte sempre!\n";
                break;
            default:
                cout << "\nOp��o inv�lida\n";
        }

        // Se a op��o for 0, sair do loop
        if (opcao == 0) {
            break;
        }

        std::cout << "\n";

    } while (true);
}