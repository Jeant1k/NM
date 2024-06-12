#pragma once

#include <vector>
#include <tuple>

#include "equation.hpp"

using namespace std;

template<typename... Args>
class EqSystem {
public:
    EqSystem(const vector<Equation<Args...>>& equations, const vector<vector<Equation<Args...>>>& partialDer)
        : system(equations)
        , J(partialDer)
    {}

    EqSystem(const vector<Equation<Args...>>& equations, const vector<Equation<Args...>>& phi)
        : system(equations)
        , phi(phi)
    {}

    vector<double> evalSystem(Args... args) {
        vector<double> results;
        for (auto& eq : system)
            results.push_back(eq.eval(forward<Args>(args)...));
        return results;
    }

    vector<double> evalPhi(Args... args) {
        vector<double> results;
        for (auto& eq : phi)
            results.push_back(eq.eval(forward<Args>(args)...));
        return results;
    }

    vector<vector<double>> evalJ(Args... args) {
        vector<vector<double>> results;
        for (auto& row : J) {
            vector<double> r;
            for (auto& der : row)
                r.push_back(der.eval(forward<Args>(args)...));
            results.push_back(r);
        }
        return results;
    }

private:
    vector<Equation<Args...>> system;
    vector<Equation<Args...>> phi;
    vector<vector<Equation<Args...>>> J;
};

template<size_t... Is>
auto vec2TupleImpl(const vector<double>& v, index_sequence<Is...>) {
    return make_tuple(v[Is]...);
}

template<size_t N>
auto vec2Tuple(const vector<double>& v) {
    return vec2TupleImpl(v, make_index_sequence<N>{});
}