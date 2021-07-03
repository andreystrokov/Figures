#include <iostream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <vector>
#include <math.h>

using namespace std;


class Figure {
public:
    Figure(const string& name) : name_(name){};
    virtual string Name(){
        return name_;
    };
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
private:
    const string name_;
};
class Rect : public Figure{
public:
    Rect(const string& name, double wight, double height) : Figure(name),
                                                    wight_(wight),
                                                    height_(height){};

    double Perimeter() override {
        return (wight_ + height_ )* 2;
    }

    double Area(){
        return wight_ * height_;
    }
private:
    double wight_;
    double height_;
};
class Triangle : public Figure{
public:
    Triangle(const string& name,double a,double b,double c) : Figure(name),
                                                     a_(a), b_(b), c_(c) {};

    double Perimeter() override {
        return a_ + b_ + c_;
    }

    double Area() override {
        double pp = (a_ + b_ + c_)/2;
        return sqrt(pp*(pp - a_)*(pp - b_)*(pp - c_));
    }
private:
    double a_;
    double b_;
    double c_;
};
class Circle : public Figure{
public:
    Circle(const string& name, double r) : Figure(name),r_(r){};

    double Perimeter() override {
        return 2 * 3.14 * (r_);
    }

    double Area() override {

        return 3.14 * (r_*r_);
    }
private:
    double r_;
};
shared_ptr<Figure> CreateFigure(istringstream& is){
    string type;
    is >> type;
    is.ignore(1);
    if (type == "RECT"){
        double w,h;
        is >> w >> h;
        return shared_ptr<Rect>() = make_shared<Rect>(type,w,h);
    } else if (type == "TRIANGLE"){
        double a_;
        double b_;
        double c_;
        is >> a_ >> b_ >> c_;
        return shared_ptr<Triangle>() = make_shared<Triangle>(type,a_,b_,c_);
    } else {
        double r;
        is >> r;
        return shared_ptr<Circle>() = make_shared<Circle>(type,r);
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}