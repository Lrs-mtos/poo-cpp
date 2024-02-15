
/*
Eu comecei a atividade baseado no que foi feito em sala de aula, mas tentando refazer do início como foi recomendado. 
Fiz sozinha e demorei umas 5 horas distribuídas em dois dias para fazer e tive pesquisar sobre a função split e write 
(para imprimir variáveis inteiras).
*/
#include <fn.hpp>
#include <iostream>

using namespace std;
using namespace fn;

struct Car {
  int km{0};
  int gas{0};
  int pass{0};
  int passMax{2};
  int kmMax{100};
  int gasMax{100};

  string toString() {
    return "pass: " + tostr(pass) + ", gas: " + tostr(gas) +
        ", km: " + tostr(km);
  }

  void enter() {
    if (pass == passMax) {
      write("fail: limite de pessoas atingido");
    } else
      pass += 1;
  }

  void leave() {
    if (pass == 0) {
      write("fail: nao ha ninguem no carro");
    } else
      pass -= 1;
  }

  void fuel(int value) {
    if ( (gas + value) >= gasMax) {
      gas = gasMax;
    } else
        gas += value;
  }

  void drive(int value) {
    if (pass == 0) {
      write("fail: nao ha ninguem no carro");
    }else if (gas == 0) {
      write("fail: tanque vazio");
    }else if ( (gas - value) < 0) {
      write(tostr(gas, "fail: tanque vazio apos andar %d km"));
      km += gas;
      gas = 0;
    }else {
      km += value;
      gas -= value;
    }
  }
};

int main() {

Car car;

  while (true) {

    string line = input();
    write("$" + line);
    vector<string> args = split(line, ' ');

    if (args[0] == "end") {
      break;
    } else if (args[0] == "show") {
      write(car.toString());
    } else if (args[0] == "enter") {
      car.enter();
    } else if (args[0] == "leave") {
      car.leave();
    } else if (args[0] == "fuel") {
      car.fuel(+(args[1]));
    } else if (args[0] == "drive") {
      car.drive(+(args[1]));
    }
  }
}
