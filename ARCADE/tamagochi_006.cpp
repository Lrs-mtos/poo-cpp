/*
Para fazer essa atividade por completo eu demorei 4 horas distribuídas em 3 dias, 
tive ajuda do meu querido amigo Samuel para uma lógica mais prática para o "init".
Aprendi melhor como funcionam os "setters" e "getters" e suas funções dentro do
código.
*/

#include <fn.hpp>
#include <iostream>

class Pet {
private:
  bool alive;
  int energyMax{0};
  int hungryMax{0};
  int cleanMax{0};
  int clean{0};
  int energy{0};
  int hungry{0};
  int age{0};
  int diamonds{0};

  bool testAlive() {
    if (alive)
      return true;

    fn::write("fail: pet esta morto");
    return false;
  }

  void setClean(int value) {

    if (value <= 0) {
      clean = 0;
      fn::write("fail: pet morreu de sujeira");
      alive = false;
    } else if (value > cleanMax) {
      clean = cleanMax;
    } else {
      clean = value;
    }
  }

  void setEnergy(int value) {
    if (value <= 0) {
      energy = 0;
      fn::write("fail: pet morreu de fraqueza");
      alive = false;
    } else if (value > energyMax) {
      energy = energyMax;
    } else {
      energy = value;
    }
  }

  void setHungry(int value) {
    if (value <= 0) {
      hungry = 0;
      fn::write("fail: pet morreu de fome");
      alive = false;
    } else if (value > hungryMax) {
      hungry = hungryMax;
    } else {
      hungry = value;
    }
  }

public:
  Pet(int energy = 0, int hungry = 0, int clean = 0) {
    this->energy = energy;
    this->hungry = hungry;
    this->clean = clean;
    this->energyMax = energy;
    this->hungryMax = hungry;
    this->cleanMax = clean;
    this->alive = true;
  }

  void play() {
    if (!testAlive())
      return;

    setEnergy(getEnergy() - 2);
    setHungry(getHungry() - 1);
    setClean(getClean() - 3);
    diamonds += 1;
    age += 1;
  }

  void eat() {

    if (!testAlive())
      return;

    setEnergy(getEnergy() - 1);
    setHungry(getHungry() + 4);
    setClean(getClean() - 2);
    age += 1;
  }

  void shower() {

    if (!testAlive())
      return;

    setEnergy(getEnergy() - 3);
    setHungry(getHungry() - 1);
    setClean(getCleanMax());
    age += 2;
  }

  void sleep() {

    if (!testAlive())
      return;

    if ((energyMax - energy) < 5) {
      fn::write("fail: nao esta com sono");
      // fn::write(fn::tostr(energyMax, "%d\n"));
      // fn::write(fn::tostr(energy, "%d\n"));
      return;
    }

    setEnergy(getEnergyMax());
    setHungry(getHungry() - 1);
    age += 5;
  }

  int getCleanMax() { return cleanMax; }

  int getHungryMax() { return hungryMax; }

  int getEnergyMax() { return energyMax; }

  int getClean() { return clean; }

  int getHungry() { return hungry; }

  int getEnergy() { return energy; }

  std::string toString() {
    return fn::format("E:{}/{}, S:{}/{}, L:{}/{}, D:{}, I:{}", energy,
                      energyMax, hungry, hungryMax, clean, cleanMax, diamonds,
                      age);
  }
};

int main() {

  Pet pet(0, 0, 0);

  while (true) {
    std::string line = fn::input();
    std::vector<std::string> args = fn::split(line, ' ');

    fn::write("$" + line);

    if (args[0] == "show") {
      fn::write(pet.toString());

    } else if (args[0] == "init") {
      pet = Pet(+args[1], +args[2], +args[3]);

    } else if (args[0] == "play") {
      pet.play();

    } else if (args[0] == "shower") {
      pet.shower();

    } else if (args[0] == "eat") {
      pet.eat();

    } else if (args[0] == "sleep") {
      pet.sleep();

    } else if (args[0] == "end") {
      break;
    } else {
      fn::write("fail:comando invalido");
    }
  }
}