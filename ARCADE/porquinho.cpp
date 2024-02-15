/*
Para fazer essa atividade, eu acredito ter demorado umas 4h e precisei de uns exemplos de outras atividades. Eu fiz sozinha e 
minha maior dificuldade foi entender como as classes, métodos e objetos se comunicam entre si.
*/
#include <fn.hpp>
#include <utility>
#include <iomanip> //setprecision

class Coin {
    double value;
    int volume;
    std::string label;

    Coin(double value, int volume, std::string label) :
        value(value), volume(volume), label(label) {
    }
public:
    const static Coin C10;
    const static Coin C25;
    const static Coin C50;
    const static Coin C100;

    float getValue() const { 
        return value; 
    }
    int getVolume() const { 
        return volume; 
    }
    std::string getLabel() const { 
        return label; 
    }
};

const Coin Coin::C10 {0.10, 1, "C10"};
const Coin Coin::C25 {0.25, 2, "C25"};
const Coin Coin::C50 {0.50, 3, "C50"};
const Coin Coin::C100 {1.00, 4, "C100"};


class Item {
    std::string label;
    int volume;
public:
    Item(std::string label, int volume) {
        this->label = label;
        this->volume = volume;
    }
    int getVolume() const {
        return volume;
    }
     std::string getLabel() const {
        return label;
    }
     
};

class Pig {
    std::vector<std::string> itens;
    double value {0};
    int volume {0};
    int volumeMax {0};
    bool broken {false};

public:
    Pig(int volumeMax = 0) {
        this->value = value;
        this->volume = volume;
        this->volumeMax = volumeMax;
        this->broken = broken;
        this->itens = itens;
    }
    
    bool addCoin(Coin coin) {
        if(broken == true){
            fn::write("fail: the pig is broken");
            return false;
        }
        if( (volume+coin.getVolume()) > volumeMax){
            fn::write("fail: the pig is full");
            return false;
        }

        value += coin.getValue();
        volume += coin.getVolume();

        return true;
    }

    bool addItem(Item item) {
        if(broken == true){
            fn::write("fail: the pig is broken");
            return false;
        }
        
        if( (volume+item.getVolume() ) > volumeMax){
            fn::write("fail: the pig is full");
            return false;
        }

        itens.push_back(item.getLabel());
        volume += item.getVolume();
        return true;

    }

    bool breakPig() {
        if(broken != false){
            fn::write("fail: the pig is broken");
        }
        broken = true;
        volume = 0;
        return true;
    }

    double getCoins() {
        if(broken == false){
            fn::write("fail: you must break the pig first");
            return 0;
        }
        double v = value;
        value = 0;
        return v;
    }

    std::vector<std::string> getItems() {
        std::vector<std::string> v {};
        if(broken == false){
                fn::write("fail: you must break the pig first");
                return v;

        }
        v = itens;
        itens.clear();
        return v;
    }

    std::string str() const {

        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) 
            << fn::format("", itens)
            << " : " << value << "$ : " << volume << "/" << volumeMax << " : ";
            if (broken == false)
                ss << "unbroken";
            else
                ss << "broken";

        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Pig& pig) {
    return os << pig.str();
}


int main() {

    Pig pig;
    while (true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line);

        if      (args[0] == "end"    ) { break; }
        else if (args[0] == "show"   ) { fn::write(pig);                               }
        else if (args[0] == "addCoin") { 
            if      (args[1] == "10" ) pig.addCoin(Coin::C10);
            else if (args[1] == "25" ) pig.addCoin(Coin::C25);
            else if (args[1] == "50" ) pig.addCoin(Coin::C50);
            else if (args[1] == "100") pig.addCoin(Coin::C100);
        }
        else if (args[0] == "init"    ) { pig = Pig( (int) +(args[1]));                 }
        else if (args[0] == "addItem" ) { pig.addItem(Item(args[1], (int) +(args[2]))); }
        else if (args[0] == "break"   ) { pig.breakPig();                               }
        else if (args[0] == "getCoins") { fn::write(fn::tostr(pig.getCoins(), "%.2f")); }
        else if (args[0] == "getItems") { fn::write(pig.getItems());                    }
        else                            { fn::write("fail: invalid command"); }
    }
}
