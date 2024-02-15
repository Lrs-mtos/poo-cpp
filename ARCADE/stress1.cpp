//-std=c++17
#include <iostream>
#include <vector>
#include <fn.hpp>

bool in(std::vector<int> vet, int value) {
    for (auto elem : vet){
        if (value == elem) return true;
    } 
    return false;
}

int index_of(std::vector<int> vet, int value) {
    for (int i = 0; i < vet.size(); i++){
        if (vet[i] == value) return i;
    }
    return -1;   
}

int find_if(const std::vector<int>& vet) {
    for (int i = 0; i < vet.size(); i++){
        if (vet[i] > 0) return i;
    }
    return -1; 
}


int min_element(const std::vector<int>& vet) {
    int min_index = -1;

    if (vet.empty() == true){
        return min_index;
    }
    
    signed int min_value = vet[0];
    for (int i = 0; i < vet.size(); i++){
        if (vet[i] <= min_value){
            min_value = vet[i];
            min_index = i;
        }
    }
    return min_index;
}


int find_min_if(const std::vector<int>& vet) {

    int man_index = 0;
    int man_vet = 0;
    for (int i = 0; i < vet.size(); i++){
        if (vet[i] > 0){
            man_vet = 1;
            man_index = vet[i];
        }
    }

    if (man_vet != 1){
        return -1; 
    }

    int stress_man = 0;

    for (int i = 0; i < vet.size(); i++){
        if (vet[i] > 0 && man_index <= vet[i]){
            stress_man = i;
        }
    }
    return stress_man;

}

#include <sstream>
#include <algorithm>

using namespace fn;

int main() {

    auto STRTOVET = [](auto s) { return map(split(s.substr(1, s.size() - 2), ','), FNT(x, (int)+x)); };

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);
        

        if      (args[0] == "end"        ) { break;                                            }
        else if (args[0] == "in"         ) { write(   tostr(in(STRTOVET(args[1]), +args[2]))); }
        else if (args[0] == "index_of"   ) { write(   index_of(STRTOVET(args[1]), +args[2]));  }
        else if (args[0] == "find_if"    ) { write(    find_if(STRTOVET(args[1])));            }
        else if (args[0] == "min_element") { write(min_element(STRTOVET(args[1])));            }
        else if (args[0] == "find_min_if") { write(find_min_if(STRTOVET(args[1])));            }
        else                               { write("fail: unknown command");                   }
    
    
    }     

    

}
/* x
index_of [-1,-50,-1,-99] -50
index_of [-1,-50,-1,-99] -99
index_of [-1,-50,-1,-99] 10
end
find_if [5,3,-1,-50,-1,-99]
find_if [-1,-50,-1,-99,-444]
end
min_element [5,3,-1,-50,-1,-99]
min_element [-1,-50,-1,-99,-444]
min_element [-2,5,3,-1,50,-1]
min_element []
end
find_min_if [5,3,-1,-50,-1,-99]
find_min_if [-1,-50,-1,-99,-444]
end
x */