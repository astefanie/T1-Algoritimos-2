#include <iostream>
#include <windows.h>
using namespace std;




int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int option;

    do{

    cout << "--- MENU ---" << endl
         << "1 - Novo Jogo " << endl
         << "2 - Continuar " << endl
         << "3 - Sobre " << endl 
         << "4 - Fim " << endl;
         cout << "Escolha uma opção: " << endl;
         cin >> option;

         cout<<"\033c";

         

    switch (option){

        case 1:
        break;

        case 2:
        break;

        case 3:
            cout << "Equipe de desenvolvimento: " << endl
                 << "Stefanie Saffnauer" << endl
                 << "João Victor Atallah" << endl
                 << "Diogo Lucas" << endl
                 << "Setembro, 2026\n" << endl
                 << "Disciplina de Algoritimos II" << endl
                 << "Professor: Thiago Felski" << endl;
                cin.ignore();
                cin.ignore();
                cout<<"\033c";
            break;

        case 4: 
            cout << "Obrigado(a) por jogar!";
            break;

        default:
            cout << "Opção invalida! ";


    }
    }while (option != 4); 
}