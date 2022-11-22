#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "Pipe.h"
#include "CS.h"
using namespace std;
template <typename T>
T CheckInputNumber(T min, T max) {
    T x;
    while (((std::cin >> x).fail()) || (x <= min) || (x > max)) {
        std::cout << "\nError. Try again\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}

template <typename T>
using FilterPipe = bool (*) (Pipe& p, T par);
template <typename T>
using FilterCs = bool(*) (CS& cs, T par);
template <typename T>
unordered_set<int> SearchPipeByParametr(unordered_map <int, Pipe>& PGroup, FilterPipe<T> f, T par) {
    unordered_set <int> Id;
    for (auto& p : PGroup) {
        if (f(p.second, par))
            Id.insert(p.second.GetId());
    }
    return Id;
}
template <typename T>
unordered_set <int> SearchCsByParametr(unordered_map <int, CS>& CsGroup, FilterCs<T> f, T par) {
    unordered_set<int> Id;
    for (auto& cs : CsGroup) {
        if (f(cs.second, par))
            id.insert(cs.second.GetId());
    }
    return Id;
}