#include <iostream>

#include "../include/chan/chan.hpp"

#define BOLD_BLUE   "\033[1;34m"
#define GREEN       "\033[32m"
#define RED         "\033[31m"
#define RESET       "\033[0m"

const int test_value1 = 5;
const int test_value2 = 10;

int recv(chan<int>& ch) {
    int value;
    ch >> value;
    return value;
}

void send(chan<int>& ch, int value) {
    ch << value;
}

inline int test_assert(bool condition, std::string name) {
    if (condition)
        std::cout << GREEN << "[+] " << name << RESET << std::endl;
    else
        std::cout << RED << "[-] Failed " << name << RESET << std::endl;

    return !condition;
}

int test_bidirectional_chan() {
    std::cout << BOLD_BLUE << "\nBIDIRECTIONAL CHAN" << RESET << std::endl;

    chan<int> ch;

    send(ch, test_value1);
    send(ch, test_value2);

    return test_assert(
        recv(ch) == test_value1 && 
        recv(ch) == test_value2,
        "write and read"
    );
}

int test_unidirectional_chans() {
    std::cout << BOLD_BLUE << "\nMONODIRECTIONAL CHAN" << RESET << std::endl;

    auto [tx, rx] = chanpair::get_new<int>();

    send(tx, test_value1);
    return test_assert(
        recv(rx) == test_value1,
        "write and read"
    );
}

int main() {
    int failed {0};
    
    failed += test_bidirectional_chan();
    failed += test_unidirectional_chans();

    std::cout << std::endl << failed << " tests failed\n\n";
    return 0;
}