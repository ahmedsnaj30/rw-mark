// Copyright 2022 Ahmed Shaheen

#include "RandWriter.h"
#include <iostream>
#include <string>

// ./TextWriter k L < input.txt

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Invalid number of args: ./TextWriter k L < filename\n";
    }

    int k;
    int L;
    std::string input, text, output;

    k = std::stoi(argv[1]);
    L = std::stoi(argv[2]);

    while (std::getline(std::cin, text)) {
        input += text;
    }
    std::string kgram = input.substr(0, k);
    RandWriter randObj(input, k);

    output = randObj.generate(kgram, L);

    std::cout << output << std::endl;
}
