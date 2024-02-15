/* 
Estou entregando esta atividade com um dia de atraso. Eu demorei bastante nela porque fiz do zero praticamente e ainda fiquei presa na função setSlot
porque em vez de deixar o parâmetro como Espiral slot, eu estava deixando std::vector<Espiral> slot e isso me confundiu muito. Meu amigo Samuel também
me ajudou e para identificar o erro do método setSlot eu acompanhei um dos vídeos sobre essa questão no seu canal do youtube, mas em outra linguagem.
*/


#include <iostream>
#include <fn.hpp>
#include <iomanip> //setprecision


class Espiral{

    std::string name;
    float price;
    int quantity;

public:

    Espiral(std::string name = "   empty", float price = 0.0, int quantity = 0){
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }

    std::string getName() const {
        return name;
    }

    float getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }

    void setName(std::string name) {
        //todo
        this->name = name;
        return;
    }

    void setPrice(float price) {
        //todo
        this->price = price;
        return;
    }

    void setQuantity(int quantity) {
        //todo
        this->quantity = quantity;
        return;
    }

    std::string str() const {
        std::stringstream ss;
        ss << "[" << std::setw(8) << std::setfill(' ') << name << " : " 
        << quantity << " U : " << std::fixed << std::setprecision(2) 
        << price << " RS]";
        return ss.str();
        //0 [ tampico : 1 U : 1.50 RS]
    }

};

std::ostream& operator<<(std::ostream& os, const Espiral espiral) {
    return os << espiral.str();
}


class Machine{

    std::vector<Espiral> slot;
    float profit {0.0};
    float cash   {0.0};
    int capacity {0};

public:

    Machine(int capacity = 0) : slot{(long unsigned int)capacity} {
        this->capacity = capacity;
    }

    std::vector<Espiral> getSlot(int index) {
        return slot;
    }
    
    void setSlot(int index, Espiral slot){
        if(index > this->capacity-1){
            fn::write("fail: indice nao existe");
            return;
        }

        this->slot[index] = slot;
        return;
    }

    void clearSlot(int index){
        if(index > this->capacity-1){
            fn::write("fail: indice nao existe");
            return;
        }
        this->slot[index] = Espiral();
        return;
    }

    void insertCash(float cash){
        this->cash += cash;
        return;
    }

    float withdrawCash(){
        float dinheiro = this->cash;
        this->cash = 0.0;
        return dinheiro;
    }

    float getCash(){
        return this->cash;
    }

    float getProfit(){
        float troco = this->profit;
        this->profit = this->cash;
        this->cash = 0.0;
        std::cout << "voce recebeu " << std::fixed << std::setprecision(2) << this->profit << " RS" << std::endl;
        return troco;
    }

    void buyItem(int index){
        
        if(index > this->capacity-1){
            fn::write("fail: indice nao existe");
            return;
        }
        
        Espiral espiral = slot[index];

        if((cash - espiral.getPrice()) < 0){
            fn::write("fail: saldo insuficiente");
            return;
        }

        if(espiral.getName() == "    empty" || espiral.getQuantity() == 0 || espiral.getPrice() == 0.0){
            fn::write("fail: espiral sem produtos");
            return;
        }


        cash -= espiral.getPrice();
        profit += espiral.getPrice();

        espiral.setQuantity(espiral.getQuantity() - 1);
        
        this->slot[index] = espiral;
        std::cout << "voce comprou um " << espiral.getName() << std::endl;
        return;

    }

    std::string str() const {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);
        ss << "saldo: " << cash << "\n";
        for(int i = 0; i < capacity; i++){
            ss << i << " " << slot[i].str();
            if(i != capacity-1){
                ss <<  "\n";
            }
        }
        return ss.str();
    }

};

std::ostream& operator<<(std::ostream& os, const Machine machine) {
    return os << machine.str();
}


int main(){

    Machine machine;
    Espiral slot;

    for(;;){
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line);

        if(args[0] == "end"    ) { break; }
        else if(args[0] == "show"    ) { fn::write(machine); }
        else if(args[0] == "set"     ) {
            slot.setName(args[2]);
            slot.setQuantity(+args[3]);
            slot.setPrice(+args[4]);
            machine.setSlot(+args[1], slot);

        }
        else if((args[0] == "limpar"    )){ machine.clearSlot(+args[1]);}
        else if((args[0] == "dinheiro"  )){ machine.insertCash(+args[1]);}
        else if((args[0] == "troco"  )){ machine.getProfit();}
        else if((args[0] == "comprar"  )){ machine.buyItem(+args[1]);}
        else if (args[0] == "init"  ) { machine = Machine(fn::number(args[1])); }
        else { fn::write("fail: invalid command"); }
    }
    
}
/*
init 3
set 2 todinho 3 2.50
set 0 tampico 1 1.50
set 1 xaverde 3 5.00

*/


    /**
     * Apenas iniciei o vetor de Espiral com a quantidade passada pelo "init [numero]"
     * Em cima da seção SHELL, que tem os casos, tem o exemplo do construtor de Machine, deixei selecionado na página do Github,
     * ele invoca o construtor da lista de Espirais (slot) passando a quantidade de objetos lá dentro (capacity).
     * O erro estava acontecendo pois o slot estava vazio, e para imprimir vc acessa uma posição dele (slot[i]), por isso dá segmentation
     * E dava certo com o "slot{'a'}" pois ele n deixava mais o vetor vazio. Acredito que seja por isso.
     * Eu testei com init 2 e init 10 e funcionou. Esse casting foi só para tirar uma warning q apareceu, tu pode tirar e checar
     * a warning depois. 
     */