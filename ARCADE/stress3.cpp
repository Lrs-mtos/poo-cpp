/* 
Para fazer essa atividade eu tive que estudar um pouco melhor algumas funções envolvendo vector, além de seu comportamento.
Para isso, eu usei um site que foi recomendado em sala: https://www.learncpp.com/cpp-tutorial/an-introduction-to-stdvector/.
Demorei bastante tempo fazendo um algortimo de sorting que funcionasse direito (até onde eu percebi). Por conta desses fatores
eu devo ter demorado umas 8h distribuídas em 3 dias para terminar esse código por completo.
*/
#include <algorithm>
#include <fn.hpp>
#include <iostream>
#include <vector>

using namespace fn;

std::vector<int> get_men(std::vector<int> vet) {
    std::vector<int> men(vet.size());

    int j{0};
    for (int i = 0; i < vet.size(); i++) {
            if (vet[i] > 0) {
            men.at(j) = vet[i];
            j++;
        }
    }

    men.resize(j);
    return men;
}

std::vector<int> get_calm_women(std::vector<int> vet) {
    std::vector<int> calm_women(vet.size());

    int j{0};
    for (int i = 0; i < vet.size(); i++) {
        if (vet[i] > -10 && vet[i] < 0) {
            calm_women.at(j) = vet[i];
            j++;
        }
    }

    calm_women.resize(j);
    return calm_women;
}

// bubble sort
std::vector<int> sort(std::vector<int> vet) {

    int maior{vet.at(0)};
    int menor{vet.at(0)};

    for (int i = 0; i < vet.size(); i++) {
        if (vet.at(i) > maior) maior = vet.at(i);
        if (vet.at(i) < menor) menor = vet.at(i);
    }

    std::vector<int> aux(vet);
    int i {0};

    for (i = 0; i < vet.size(); i++) {

        if (vet.at(i) > vet.at(i + 1)) {
            aux.at(i) = vet.at(i + 1);
            aux.at(i + 1) = vet.at(i);
            vet = aux;

            for(int h = 0; h < vet.size()-1; h++){
                if(aux[h] > aux[h+1]){
                    i = -1;
                    break;
                }
            }

        }
        if (i + 1 == vet.size() - 1) {
            i = 0;
            break;
        }
    }
    return aux;
}

std::vector<int> sort_stress(std::vector<int> vet) {

    std::vector<int> vet_negative (vet);
    int j {0};
    for(int i = 0; i < vet.size(); i++){
        if(vet[i] < 0){
            vet_negative[j] = vet[i];
            vet[i] = (vet[i]* -1 );
            j++;
        }

    }
    vet_negative.resize(j);

    std::vector<int> aux (sort(vet));
    
    for(int i = 0; i < aux.size(); i++){
        int k {0};
        while(k < j){

            if(aux[i] == (vet_negative[k] * -1)){
                aux[i] = (aux[i]* -1 );
                vet_negative[k] = 0;
            }
            k++;

        }
    }

    return aux;
}

std::vector<int> reverse(std::vector<int> vet) {
    std::vector<int> aux(vet.size());

    for(int i = 0, j = vet.size()-1; i < vet.size(), j >= 0; i++, j--){
        aux[i] = vet[j];
    }
    return aux;
}

std::vector<int> reverse_inplace(std::vector<int> vet){

    int a {0};
    int b {0};

    for(int i = 0, j = vet.size()-1; i < (vet.size()/2); i++, j--){
        a = vet[i];
        b = vet[j];
        vet[i] = b;
        vet[j] = a;
        write("teste");
    }
    return vet;

}

std::vector<int> unique(std::vector<int> vet) {
    std::vector<int> aux(vet.size());
    int count = -1;
    int j =  {0};
    aux[0] = vet[0];

    for(int i = 0; i < vet.size(); i++){
        
        for( ; j < vet.size(); j++){ 
            if(vet[i] == aux[j]){
                count = 0;
                break;
            }
        }
        j = 0;
        if(count == -1){
            aux[i] = vet[i];
        }else {
            count = -1;
        }
    }

    std::vector<int> aux2(vet.size());
    int value { 0 };
    for(int i = 0; i < vet.size(); i++){

        if(aux[i] != 0){
            aux2[value] = aux[i];
            value ++;
        }
    }

    aux2.resize(value);
    return aux2;
}

std::vector<int> repeated(std::vector<int> vet) {

    std::vector<int> aux(vet.size());
    int count = -1;
    int j = {0};
    std::vector<int> repeated(vet.size());
    aux[0] = vet[0];

    for(int i = 0; i < vet.size(); i++){
        
        for( ; j < vet.size(); j++){ 
            if(vet[i] == aux[j] && i != 0){
                repeated[i] = vet[i];
                count = 0;
                break;
            }
        }
        j = 0;
        if(count == -1){
            aux[i] = vet[i];
        }else {
            count = -1;
        }
    }

    std::vector<int> aux2(vet.size());
    int value { 0 };
    for(int i = 0; i < vet.size(); i++){

        if(repeated[i] != 0){
            aux2[value] = repeated[i];
            value ++;
        }
    }

    aux2.resize(value);
    return aux2;
}

int main() {
    auto strToVet = [](auto s) {
    return s.substr(1, s.size() - 2) | SPLIT(',') | MAP(FNT(x, (int)+x));
    };

    while (true) {
        std::string line = input();
        auto args = split(line, ' ');
        write('$' + line);

        if (args[0] == "get_men")             { write(get_men(strToVet(args[1])));    }
        else if (args[0] == "get_calm_women") { write(get_calm_women(strToVet(args[1])));}
        else if (args[0] == "sort")           { write(sort(strToVet(args[1])));       }
        else if(args[0] == "sort_stress")     { write(sort_stress(strToVet(args[1])));}
        else if(args[0] == "reverse")         { write(reverse(strToVet(args[1])));    } 
        else if(args[0] == "unique")          { write(unique(strToVet(args[1])));   } 
        else if(args[0] == "repeated"       ) { write(repeated(strToVet(args[1]))); }
        else if(args[0] == "reverse_inplace"       ) { write(reverse_inplace(strToVet(args[1]))); }
        else if (args[0] == "end") {
        break;
        } else
        fn::write("fail: comando invalido");
    }
}