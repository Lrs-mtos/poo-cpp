




/* #include <iostream>
#include <vector>
#include <fn.hpp>

int divide (){
    int a {};
    int b {};
    std::cout << "Digite dois valores A e B:" << std::endl;
    std::cin >> a >> b;
    return a/b;
}

int main(){
    std::vector<int> v(5);

    
    while (true){
        auto line = fn::input();
        auto args = fn::split(line, ' ');

        if(args[0] == "div"){
            std::cout << divide();
        } else if (args[0] == "show"){
            std::cout << v.size();
        } else 
        try {

        } catch ( std::out_of_range& e){

        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
} */