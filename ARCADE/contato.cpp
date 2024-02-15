/* 
Eu fiz a atividade sozinha em cerca de 3h, eu não estava muito familiarizada com listas, entãi eu fiz algumas pesquisas para algumas partes do código
como em ind_first_not_of e o uso do for-range.
*/

#include <iostream>
#include <iomanip>
#include <fn.hpp>
#include <memory>
#include <string>
#include <list>
#include <algorithm>

class Fone{

    std::string id;
    std::string number;

public:

    Fone(std::string id = "", std::string number = "") : id(id), number(number) {}

    bool isValid(){
        std::string validos {"1234567890()."};
        auto found = getNumber().find_first_not_of(validos);
        if(found == std::string::npos) return true;

        return false;
    }

    std::string getId() const{return id;}

    std::string getNumber() const{return number;}

    std::string str() const{
        std::stringstream ss;
        ss << id << ":" << number;
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream &os, Fone f) { return os << f.str(); }

class Contact{
    bool fav;
    std::list<std::shared_ptr<Fone>> fones;
    std::string name;

public:

    Contact(std::string name = "") : fav(false), name(name), fones() {}

    void addFone(std::string id, std::string number){
        std::shared_ptr<Fone> fone = std::make_shared<Fone>(id, number);
        if(!fone->isValid()){
            fn::write("fail: invalid number");
            return;
        }
        fones.push_back(fone);
    }

    void rmFone(int index){
        auto it = fones.begin();
        std::advance(it, index);

        if (it != fones.end()) {
            fones.erase(it);
        }else{
            fn::write("fail: indice invalido");
        }
    }

    void toggleFavorited(){fav = !fav;}

    bool isFavorited(){
        if(fav == true) return true;
        return false;
    }

    std::list<std::shared_ptr<Fone>> getFones() const{return fones;}

    std::string getName() const{return name;}

    void setName(std::string name) {this->name = name;}

    std::string str() const {
        std::stringstream ss;
        if(!fav){
          ss << "- ";      
        }else{
            ss << "@ ";
        }
        ss << name << " [";
        for (const auto &fone : fones) {
        if (fones.front() == fone) {
            ss << fone->str();
        } else {
            ss << ", " << fone->str();
        }
        }
        ss << "]";
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream &os, Contact c) { return os << c.str(); }

int main(){
    Contact contact;

    for (;;) {

        std::string line = fn::input();
        fn::write("$" + line);
        std::vector<std::string> args = fn::split(line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "show") {
            fn::write(contact);
        } else if (args[0] == "init") {
            contact = Contact(args[1]);
        } else if (args[0] == "add") {
            contact.addFone(args[1], args[2]);
        } else if (args[0] == "rm") {
            contact.rmFone(+args[1]);
        } else if (args[0] == "tfav") {
            contact.toggleFavorited();
        } else fn::write("comando invalido");
  
    }
    return 0;
}