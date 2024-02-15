/*
Para fazer essa atividade por completo eu demorei 4 horas distribuídas em 3 dias, 
tive ajuda do meu querido amigo Samuel para uma lógica mais prática para o "init".
Aprendi melhor como funcionam os "setters" e "getters" e suas funções dentro do
código.
*/
#include <fn.hpp>
#include <iostream>
#include <vector>

using namespace fn;
using namespace std;

class Time {
  int hour{0};
  int minute{0};
  int second{0};

public:
  Time(int hour = 0, int minute = 0, int second = 0) {
    this->setHour(hour);
    this->setMinute(minute);
    this->setSecond(second);
  }

  string toString() {
    return fn::format("{%02d}:{%02d}:{%02d}", hour, minute, second);
  }

  int getHour() { return hour; }

  int getMinute() { return minute; }

  int getSecond() { return second; }

  void setHour(int hour) {
    if (hour >= 0 && hour <= 23) {
      this->hour = hour;
    } else
      fn::write("fail: hora invalida");
  }

  void setMinute(int minute) {
    if (minute >= 0 && minute <= 59) {
      this->minute = minute;
    } else
      fn::write("fail: minuto invalido");
  }

  void setSecond(int second) {
    if (second >= 0 && second <= 59) {
      this->second = second;
    } else
      fn::write("fail: segundo invalido");
  }

  void nextSecond(int second, int minute, int hour) {

    if ((this->second + 1) < 60) {
      this->second = second + 1;
    } else {
      this->second = 0;
      if ((this->minute + 1) < 60) {
        this->second = second + 1;
      } else {
        this->minute = 0;
        if ((this->hour + 1) < 24) {
          this->hour = hour + 1;
        } else
          this->hour = 0;
      }
    }
  }
};

int main() {

  Time time(0, 0, 0);

  while (true) {

    string line = input();
    write("$" + line);
    vector<string> args = split(line, ' ');

    if (args[0] == "show") {
      write(time.toString());
    } else if (args[0] == "set") {
      time.setHour(+args[1]);
      time.setMinute(+args[2]);
      time.setSecond(+args[3]);

    } else if (args[0] == "init") {
      time.setHour(0);
      time.setMinute(0);
      time.setSecond(0);

      time.setHour(+args[1]);
      time.setMinute(+args[2]);
      time.setSecond(+args[3]);

    } else if (args[0] == "next") {
      time.nextSecond(time.getSecond(), time.getMinute(), time.getHour());
    } else if (args[0] == "end") {
      break;
    } else
      fn::write("fail: comando invalido");
  }
}
