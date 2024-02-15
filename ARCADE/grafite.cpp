#include <iostream>
#include <sstream>
#include <memory>  //sharedptr
#include <iomanip> //setprecision
#include <utility> //exchange
#include <fn.hpp>

using namespace fn;

class Lead {
    float thickness;
    std::string hardness;
    int size;

public:
    Lead(float thickness, std::string hardness, int size) {
        this->thickness = thickness;
        this->hardness = hardness;
        this->size = size;
    }

    int usagePerSheet() const {
        int usage = 0;
        switch (hardness[0]) {
            case 'H':
                usage = 0;
                break;
            case '2':
                usage = 2;
                break;
            case '4':
                usage = 4;
                break;
            case '6':
                usage = 6;
                break;
            default:
                usage = 0;
                break;
        }
    return usage;
}


    float getThickness() const {
        return {thickness}; 
    }

    std::string getHardness() const {
        return {hardness};
    }

    int getSize() const {
        return {size};
    }

    void setSize(int size) {

        if(this->size == 10){
            write("fail: tamanho insuficiente");
            return;
        }

        if((getSize()-size) < 10){
            write("fail: folha incompleta");
            this->size = 10;
            return;
        }
        
        this->size = (getSize()-size);
        return;
        
    }

    std::string str() const {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) 
           << thickness << ":" << hardness << ":" << size;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& ss, Lead gr) {
    return ss << gr.str();
}

struct Pencil {
    float thickness {0.f};
    std::shared_ptr<Lead> tip {nullptr};

    Pencil(float thickness = 0.0) { 
        this->thickness = thickness;
    }

    bool hasGrafite() {
        if (tip == nullptr) return false;
        return true;
    }

    bool insert(std::shared_ptr<Lead> grafite) {
        if(hasGrafite()){
            fn::write("fail: ja existe grafite");
            return false;
        }
        if(thickness != grafite->getThickness()){
            fn::write("fail: calibre incompativel");
            return false;
        }

        tip = grafite;
        return true;
    }

    std::shared_ptr<Lead> remove() {
        if(hasGrafite() != true){
            fn::write("fail: nao existe grafite");
            return tip;
        } else {
            tip = nullptr;
            return nullptr;
        }
    }

    void writePage() {
        if(hasGrafite() != true){
            fn::write("fail: nao existe grafite");
            return;
        }

        int value = tip->usagePerSheet();

        tip->setSize(value);

    }

    std::string str() {
        std::stringstream ss;
        ss << "calibre: " << thickness << ", grafite: ";
        if (tip != nullptr)
            ss << "[" << *tip << "]";
        else
            ss << "null";
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pencil l) {
    return os << l.str();
}

using namespace fn;

int main() {
    Pencil pencil;

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"   ) { break;                                                                                  }
        else if (args[0] == "show"  ) { write(pencil);                                                                          }
        else if (args[0] == "init"  ) { pencil = Pencil(number(args[1]));                                                       }
        else if (args[0] == "insert") { pencil.insert(std::make_shared<Lead>(number(args[1]), args[2], (int) number(args[3]))); }
        else if (args[0] == "remove") { pencil.remove();                                                                        }
        else if (args[0] == "write" ) { pencil.writePage();                                                                     }
        else                          { write("fail: unknown command");                                                         }
    }
}


