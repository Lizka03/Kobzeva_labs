#pragma once
template <typename T>
T CheckInputNumber(T min, T max) {
    T x;
    while (!((std::cin >> x).good()) || (x <= min) || (x > max)) {
        std::cout << "\nError. Try again\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}