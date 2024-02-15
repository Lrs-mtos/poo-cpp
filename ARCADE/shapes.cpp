/* 
Fiz a atividade sozinha, a maioria da ajuda veio do que tinha no grupo da disciplina, principalmente - novamente - por conta da impressão dos
dados na tela. Demorei cerca de 4h para fazer a atividade e me baseei em atividades anteriores para fazer esta.
*/

#include <iostream>
#include <fn.hpp>
#include <iomanip> //setprecision
#include <cmath>

using namespace fn;
using namespace std;

static const float pi = 3.141592;

class Point2D {
public:
    double x;
    double y;

    Point2D(double x, double y) : x(x), y(y) {}

    Point2D(string serial) {
        stringstream ss(serial);
        char c {};
        ss >> c >> x >> c >> y >> c;
    }

    string str() const {
        ostringstream oss;
        oss << fixed << setprecision(2) << "(" << x 
        << ", " << y << ")";
        return oss.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Point2D& p) 
{ return os << p.str(); }


class Calc {
public:
    // h^2 = ca^2 + co^2
    static double distance (Point2D p1, Point2D p2){
        float abs_pwr = (p1.x-p2.x)*(p1.x-p2.x);
        float ord_pwr = (p1.y-p2.y)*(p1.y-p2.y);
        return (sqrt(abs_pwr + ord_pwr));
    }
};

class Shape{
    string name;
public:
    Shape(string name = " ") : name(name) {}

    virtual ~Shape(){}

    virtual bool inside(Point2D p) const = 0;

    virtual double getArea() const = 0;

    virtual double getPerimeter() const = 0;

    virtual string getName() const {
        return name;
    }

    virtual string str() const {
        return this->getName();
    }

};

ostream& operator<<(ostream& os, const Shape& p) 
{ return os << p.str(); }

class Circle : public Shape{
    Point2D center;
    double radius;

public:
    Circle(Point2D center, double radius) : 
Shape("Circ"), center(center), radius(radius) {}

    bool inside(Point2D p) const override {
        double dist_cp = Calc::distance(center, p);
        if(dist_cp > radius) return false;
        return true;

    }

    double getArea() const override {
        return pi*(radius*radius);
    }

    double getPerimeter() const override {
        return 2*pi*radius;
    }

    string str() const override {
        std::ostringstream oss;
        oss << fixed << this->getName() << ": "
        << "C=" << center.str() << ", R="
        << fixed << setprecision(2) << this->radius;
        return oss.str();
    }
};

class Rectangle : public Shape {
    Point2D p1;
    Point2D p2;

public:
    Rectangle(Point2D p1, Point2D p2) :
Shape("Rect"), p1(p1), p2(p2) {}

    bool inside(Point2D p) const override {
        double dist_p1_p2 = Calc::distance(p1, p2);
        double dist1_p1_p = Calc::distance(p1, p);
        double dist1_p2_p = Calc::distance(p2, p);
        if((dist1_p1_p + dist1_p2_p) > dist_p1_p2) return false;
        return true;
    }

    double getArea() const override {
        return (p1.x-p2.x)*(p1.y-p2.y);
    }

    double getPerimeter() const override {
        return ((p2.x-p1.x)*2) + ((p2.y-p1.y)*2);
    }

    Point2D getP1() const {
        return p1;
    }

    Point2D getP2() const {
        return p2;
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << fixed << this->getName() << ": " << "P1=" << p1.str() << " P2=" << p2.str();
        return oss.str();
    }

};


int main(){
    vector<shared_ptr<Shape>> shapes;

    for(;;){
        auto line = input();
        auto args = split(line, ' ');
        write("$" + line);

        if (args[0] == "end") {
            break;
        }
        else if (args[0] == "show") {
            for (auto shape : shapes) {
                fn::write(shape->str());
            }
        }
        else if (args[0] == "circle") { 
            auto x = +args[1];
            auto y = +args[2]; 
            auto r = +args[3];
            shapes.push_back(std::make_shared<Circle>(Point2D{x, y}, r));
        }
        else if (args[0] == "rect") { 
            auto p1 = Point2D{+args[1], +args[2]};
            auto p2 = Point2D{+args[3], +args[4]};
            shapes.push_back(std::make_shared<Rectangle>(p1, p2));
        }
        else if (args[0] == "info") {
            for (auto shape : shapes) {
                print("{}: A={%.2f} P={%.2f}\n", 
                shape->getName(), shape->getArea(), shape->getPerimeter());
            }
        }
        else{
                fn::write("fail: comando invalido");
            }
    }
}
