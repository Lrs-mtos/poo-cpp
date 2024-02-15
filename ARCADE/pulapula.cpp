/* 
eu demorei cerca de duas horas para fazer essa atividade. Demorei um pouco para perceber que a manipulação das listas seria
com os métodos push e pop, e pesquisei na internet meios de fazer a função lambda, que aprendemos na última aula, funcionar. Percebi que estava errada na 
comparação para retirar os nomes da lista, em vez de usar os ponteiros, estava tentando criar nomes em si e comparar strings somente (linha 49).
*/

#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include <vector>
#include <fn.hpp>
#include <algorithm>

using namespace fn;

class Kid {
private:
    int age;
    std::string name;

public:
    Kid(std::string name, int age) {
        this->age = age;
        this->name = name;
    }
    int getAge() {
        return age;
    }
    std::string getName() {
        return name;
    }
    std::string str() {
        return name + ":" + std::to_string(age);
    }
};

std::ostream& operator<<(std::ostream& os,  Kid kid) {
    return os << kid.str();
}

using PtrKid = std::shared_ptr<Kid>;

class Trampoline {
    std::list<PtrKid> waiting;
    std::list<PtrKid> playing;
    
    PtrKid removeFromList(std::string name, std::list<PtrKid>& lista) {

        /* if(lista.front() != nullptr) {
            lista.remove_if([&name](std::string nome){ return nome == name; }); 
        } */

        auto it = std::find_if(lista.begin(), lista.end(), [&name](const PtrKid& ptr) {
            return ptr != nullptr && ptr->getName() == name; 
        });
        if (it != lista.end()) {
            auto kid = *it;
            lista.erase(it);
            return kid;
        }

        return nullptr;
    }

public:
    Trampoline() {
    }
    
    void arrive(PtrKid kid) {
        kid->getAge();
        kid->getName();

        waiting.push_front(kid);

        return;
    }


    void enter() {
        playing.push_front(waiting.back());
        waiting.pop_back();
        return;
    }

    void leave() {
        if(playing.front() == nullptr) return;

        waiting.push_front(playing.back());
        playing.pop_back();

        return;
    }

    PtrKid removeKid(std::string name) {
        removeFromList(name, waiting);
        removeFromList(name, playing);

        return nullptr;
    }

    std::string str() {
        return fn::tostr(waiting) + " => " + fn::tostr(playing);
    }
};

int main() {
    Trampoline tr;

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"   ) { break;                                                     }
        else if (args[0] == "arrive") { tr.arrive(std::make_shared<Kid>(args[1], (int) +args[2])); }
        else if (args[0] == "enter" ) { tr.enter();                                                }
        else if (args[0] == "leave" ) { tr.leave();                                                }
        else if (args[0] == "remove") { tr.removeKid(args[1]);                                     }
        else if (args[0] == "show"  ) { write(tr.str());                                           }
        else                          { write("fail: invalid command");                            }
    }
}