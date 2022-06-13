// Copyright 2022 Ahmed Shaheen
#include "RandWriter.h"
#include <chrono>   //NOLINT
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

RandWriter::RandWriter(std::string text, int k) {
    // create a Markov model of order k from given text
    // Assume text has length k
    order_k = k;
    alph = text;

    auto sortAlph = [](std::string letters) {
        std::sort(letters.begin(), letters.end());
    };

    sortAlph(alph);

    int text_size = text.size();

    for (int i = 0; i < text_size; i++) {
        std::string tmp_str = "";
        if (i + k > text_size) {
            int disp = i % (text_size - k);   // displacement after last element
            tmp_str = text.substr(i) + text.substr(0, disp);
            // kgrams[tmp_str][text[i+1]]++;
            kgrams[tmp_str][text[disp]]++;   // insert items into nested map
        } else if (k == 0) {                // if order = 0
            tmp_str += text[i];             // concat string
            if (i + 1 == text_size) {   // check char thats not in array
                tmp_str += text[i];
                kgrams[tmp_str][text[0]]++;   // get first char instead
            } else {
                kgrams[tmp_str][text[i+1]]++;   // else, add items
            }
        } else {
            for (int j = 0; j < k; j++) {
                tmp_str += text[i+j];
            }
            if (i + k >= text_size)
                kgrams[tmp_str][text[0]]++;
            else
                kgrams[tmp_str][text[i+k]]++;
        }
    }
}

int RandWriter::orderK() const {
    // order k of Markov model
    return order_k;
}

int RandWriter::freq(std::string kgram) const {
    // Returns number of kgram occurences in original text
    // throw exception if kgram isn't length k
    int count = 0;
    int k_size = kgram.size();
    if (k_size != order_k) {
        throw std::runtime_error("Error: kgram isn't of length k.");
    }

    // Lambda
    for_each(kgrams.at(kgram).begin(), kgrams.at(kgram).end(),
    [&count](auto j){
        count += j.second;
    });
    return count;
}

int RandWriter::freq(std::string kgram, char c) const {
    // Return number of time kgram was followed by char c in original text
    // throw exception if kgram isn't length k
    int count = 0;
    int k_size = kgram.size();
    if (k_size != order_k) {
        throw std::runtime_error("freq: kgram isn't of length k.");
    }
    for (auto const &i : kgrams) {
        if (i.first == kgram) {
            for (auto const &j : i.second)
                if (j.first == c)
                    count += j.second;
        }
    }
    return count;
}

char RandWriter::kRand(std::string kgram) {
    if (static_cast<size_t>(order_k) > kgram.size()) {
        throw::std::invalid_argument("kRand: kgram isn't of length k.");
    }
    if (freq(kgram) == 0) {
        throw std::runtime_error("kRand: no such kgram.");
    }
    std::vector<double> chance;
    std::vector<char> chr;
    for (auto const &e1 : kgrams) {
        if (kgram == e1.first) {
            for (auto const &e2 : e1.second) {
                chr.push_back(e2.first);
                chance.push_back(1.0 * freq(e1.first, e2.first)
                / freq(e1.first));
            }
        }
    }
    std::mt19937 generator(std::chrono::high_resolution_clock::now().time_since_epoch().count()); //NOLINT
    std::discrete_distribution<> dist(chance.begin(), chance.end());
    return chr[dist(generator)];
}

std::string RandWriter::generate(std::string kgram, int L) {
    // Return string of length L thats a randomly generated stream of chars
    // whose first k chars are the arg kgram.
    int k_size = kgram.size();
    if (k_size != order_k) {
        throw std::runtime_error("generate: kgram isn't of length k.");
    }

    std::string ret_str = kgram;

    for (int i = k_size; i < L; i++) {      // generate
        ret_str += kRand(kgram);
        kgram = ret_str.substr(i - (order_k - 1), order_k);
    }

    return ret_str;
}

std::ostream& operator << (std::ostream& out, RandWriter& obj) {
    out << "Order: " << obj.order_k << ", Alphabet: " << obj.alph << std::endl;

    for (auto const &i : obj.kgrams) {
        out << "kgram: " << i.first << std::endl;
        for (auto const &j : i.second)  {
            out << "char: " << j.first << ", count: "
            << j.second << std::endl;
        }
    }
    return out;
}



