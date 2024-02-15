#include <iostream>
#include <map>
#include <unordered_map>
#include <fn.hpp>

//map -> criar, percorrer, achar, alterar e remover

int main(){
    //criar
    std::map<std::string, int> dieta;
    dieta["uva"] = 3;
    dieta["castanha"] = 5;
    dieta["banana"] = 1;
    dieta["ovo"] = 2;
    dieta["frango"] = 2;
    dieta["hamburguer"] = 1;

    fn::write(dieta);

    //percorrer, alterar
    for (auto& [comida, qtdd] : dieta){
        qtdd += 1;
        std::cout << "voce tem " << qtdd << " " << comida << "(s)\n";
    }

    //achar, remover
    auto it = dieta.find("uva");
    if( it != dieta.end() ){
        std::cout << it->first << " " << it->second << std::endl;
        dieta.erase(it);
        fn::write(dieta);
        //std::cout << it->first << " " << it->second << std::endl;
    }

    /* bool teste;
    teste = true;
    std::cout << teste << std::endl;
    teste = not teste;
    std::cout << teste << std::endl; */

}