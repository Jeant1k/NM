#pragma once

#include <cmath>
#include <functional>

using namespace std;

template<typename... Args>
class Equation {
public:
    Equation(function<double(Args...)> func) : func(func) {}
    
    double eval(Args... args) { return func(forward<Args>(args)...); }

private:
    function<double(Args...)> func;
};