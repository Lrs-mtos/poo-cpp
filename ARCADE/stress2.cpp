/*
Eu fiz esse programa sozinha, utilizei algumas ideias do estressados anterior e demorei cerca de 1h30 em um dia para
terminar o código.
*/
#include <iostream>
#include <fn.hpp>

using namespace fn;

int count(std::vector<int> vet, int value) {
    int ocorrencias { 0 };
    for (int i = 0; i < vet.size(); i++){
        if (vet[i] == value) ocorrencias += 1;
    }
    return ocorrencias;   
}

int sum(std::vector<int> vet) {
    int soma { 0 };
    for (int i = 0; i < vet.size(); i++){
        if(vet[i] < 0){
            soma += (vet[i] * -1);
            continue;
        }
        soma += vet[i];
    }
    return soma; 
}

std::string average(std::vector<int> vet) {
    int soma { 0 };
    for (int i = 0; i < vet.size(); i++){
        if(vet[i] < 0){
            soma += (vet[i] * -1);
            continue;
        }
        soma += vet[i];
    }
    float media = (float)soma/vet.size();
    
    return format("{%.2f}", media);
}

std::string more_man(std::vector<int> vet){
    int men { 0 };
    int women{ 0 };

    for (int i = 0; i < vet.size(); i++){
        if(vet[i] < 0){
            women++;
        }else{
            men++;
        }    
    }

    if (women > men){
        return format("women");
    }else if (men > women){
        return format("men");
    }
    return format("draw");
}

std::string half_compare(std::vector<int> vet){
    int first  { 0 };
    int second { 0 };
    int flag   { 0 };

    for (int i = 0; i < (vet.size()/2); i++){
        flag = i;
        if(vet[i] < 0){
            first += (vet[i] * -1);
            continue;
        }
        first += vet[i];
    }


    for (int i = flag+1; i < vet.size(); i++){
        if(vet[i] < 0){
            second += (vet[i] * -1);
            continue;
        }
        second += vet[i];
    }


    if (first > second){
        return format("first");
    }else if (second > first){
        return format("second");
    }

    return format("draw");
}


std::string sex_battle(std::vector<int> vet){
    int men           { 0 };
    int men_qtdd      { 0 };
    int women         { 0 };
    int women_qtdd    { 0 };
    float media_men   { 0 };
    float media_women { 0 };

    for (int i = 0; i < vet.size(); i++){
        if(vet[i] < 0){
            women += (vet[i] * -1);
            women_qtdd++;
            continue;
        }
        men += vet[i];
        men_qtdd++;
    }
    
    if(women_qtdd != 0){
        media_men = (float)(women)/women_qtdd;
    }

    if(men_qtdd != 0){
        media_women = (float)(men)/men_qtdd;
    }

    if (media_women < media_men){
        return format("women");
    }else if (media_men < media_women){
        return format("men");
    }
    return format("draw");
}


#include <sstream>
#include <algorithm>

int main(){

    auto STRTOVET = [](auto s) { return map(split(s.substr(1, s.size() - 2), ','), FNT(x, (int)+x)); };

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if(args[0] == "end"){
            break;
        }else if(args[0] == "count"){
            write(   tostr(count(STRTOVET(args[1]), +args[2])));
        }
        else if(args[0] == "sum"){
            write(   tostr(sum(STRTOVET(args[1]))));
        }
        else if(args[0] == "average"){
            write(   tostr(average(STRTOVET(args[1]))));
        }
        else if(args[0] == "more_men"){
            write(   tostr(more_man(STRTOVET(args[1]))));
        }
        else if(args[0] == "half_compare"){
            write(   tostr(half_compare(STRTOVET(args[1]))));
        }
        else if(args[0] == "sex_battle"){
            write(   tostr(sex_battle(STRTOVET(args[1]))));
        }
        else{
            write("fail: unknown command");
        }
    }

}