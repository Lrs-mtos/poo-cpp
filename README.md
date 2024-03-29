# Trabalhos de POO em C++

## Introdução

Este repositório contém meus trabalhos da disciplina de Programação Orientada a Objetos em C++. O objetivo desse repositório é documentar as atividades feitas pelo decorrer do semestre.

---

## Ementa da Disciplina

Introduzir o paradigma de Programação Orientada a Objetos (OO), juntamente com seus conceitos de classes, objetos, herança, encapsulamento e polimorfismo, além dos conceitos de Interfaces e exceções que são inerentes às linguagens de programação orientadas a objetos. Desenvolvimento de um pequeno sistema baseados no paradigma de programação OO.

---

## Pré-requisitos
Para que os códigos rodem, é preciso seguir o seguinte passso a passo disponível [aqui](https://github.com/senapk/cppaux#requisitos). Para facilitar, se você usa Ubuntu, basta fazer o que está adiante:

- Você precisa do GCC 7.3 ou superior para compilar o código.
- Copie o arquivo para uma pasta de includes do sistema e use no seu código como ```#include <fn.hpp>```.

```bash
sudo curl https://raw.githubusercontent.com/senapk/cppaux/master/fn.hpp -o /usr/local/include/fn.hpp
```
- Quando for compilar, utilize a flag -std=c++17. Por exemplo:

```bash
g++ -std=c++17 main.cpp -o main.out
```
- Para executar:
```bash
./main.out
```
### Códigos SFML

Dentro desse repositório existem também códigos que utilizam a biblioteca [SFML](https://www.sfml-dev.org/tutorials/2.6/) para jogos em C++. Para que eles rodem é preciso fazer um passo a passo a mais disponível em [SFML and Linux](https://www.sfml-dev.org/tutorials/2.6/start-linux.php). Em resumo, devemos
- Instalar o SFML:
```bash
sudo apt-get install libsfml-dev
```
- Compilar o código:
```bash
  g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
```
- Rodar o código:
```bash
  ./sfml-app
```

---
## Referências

Este repositório baseia-se nas atividades e materiais fornecidos pelo professor David Sena. É possível encontrar o material completo (enunciado, explicações, resoluções, etc) aqui: [arcade](https://github.com/qxcodepoo/arcade?tab=readme-ov-file#00-configura%C3%A7%C3%A3o-de-ambiente).
