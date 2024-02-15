#include <iostream>

int main(){

    int capacidade { 0 };
    std::cin >> capacidade;
    int onibus { 0 };

    int passageiro { 0 };
    for(int i = 0; ; i++){

        std::cin >> passageiro;
        onibus += passageiro;
        if(onibus == 0){
            std::cout << "vazio\n";
        }
        else if(onibus < capacidade){
            std::cout << "ainda cabe\n";
        }
        else if(onibus > 2*capacidade){
            std::cout << "hora de partir\n";
            break;

        } else std::cout << "lotado\n";
    }

}