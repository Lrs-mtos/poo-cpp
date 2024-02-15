/*
Demorei umas 4 horas distribuídas em vários dias. Muitas dessas horas foram perdidas novamente na tentativa de impressão na tela
em um primeiro momento não usei shared_ptr e só passei a usar depois de assistir algumas aulas antigas sobre o assunto e sobre a questão em si no
seu canal do YouTube. Fiz sozinha, mas com a ajuda de vídeos e outros materiais como anotações das aulas. 
*/

#include <fn.hpp>
#include <iomanip>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;
using namespace fn;

class Cliente {
  string fone;
  string id;

public:
  Cliente(string id = "", string fone = "") {
    this->id = id;
    this->fone = fone;
  }

  string getFone() const { return fone; }
  string getId() const { return id; }

  void setFone(string fone) { this->fone = fone; }
  void setId(string id) { this->id = id; }

  string str() const {
    stringstream ss;
    ss << id << ":" << fone;
    return ss.str();
  }
};
ostream &operator<<(ostream &os, Cliente c) { return os << c.str(); }

class Sala {
  vector<shared_ptr<Cliente>> cadeiras;

  auto procurar(string nome) {
    auto it = find_if(cadeiras.begin(), cadeiras.end(), [nome] (const auto& ptr) {
        return ptr != nullptr && ptr->getId() == nome;
    });
    return it;
  }

  bool verificarIndice(int indice) {
    if(indice < 0 || indice > cadeiras.size()){
        write("fail: cadeira nao existe");
        return true;
    }
    if(cadeiras[indice] != nullptr){
        write("fail: cadeira ja esta ocupada");
        return true;
    }
        return false;
  }
  

public:
  Sala(int capacidade = 0) : cadeiras(capacidade, nullptr) {}

  bool reservar(string id, string fone, int ind) {

    if (verificarIndice(ind)) return false;
    if (procurar(id) != cadeiras.end()){
        write("fail: cliente ja esta no cinema");
        return false;
    } 
    
    shared_ptr<Cliente> cliente  = make_shared<Cliente>(id, fone);
    cadeiras[ind] = cliente;
    
    return true;
  }

  void cancelar(string id) {

    auto it = (procurar(id));
    if(it == cadeiras.end()){
        write("fail: cliente nao esta no cinema");
        return;
    }

    *it = nullptr;
    return;
  }

  string str() {
    stringstream ss;
    ss << "[";
    Sala sala;
    for (int i = 0; i < cadeiras.size(); i++) {
      if (cadeiras[i] == nullptr) {
        if (i != 0)
          ss << " -";
        else
          ss << "-";
      } else {
        if ( i != 0){
            ss << " " << cadeiras[i]->str();
        }else ss << cadeiras[i]->str();
      }
        
    }
    ss << "]";
    return ss.str();
  }
};

ostream &operator<<(ostream &os, Sala c) { return os << c.str(); }

int main() {
  Sala sala;

  for (;;) {

    string line = input();
    write("$" + line);
    vector<string> args = split(line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "show") {
      write(sala);
    } else if (args[0] == "init") {
      sala = Sala(+args[1]);
    } else if (args[0] == "reservar") {
      sala.reservar(args[1], args[2], +args[3]);
    } else if (args[0] == "cancelar") {
      sala.cancelar(args[1]);
    } else write("comando invalido");
  }
}
