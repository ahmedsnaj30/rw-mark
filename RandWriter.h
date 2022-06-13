// Copyright 2022 Ahmed Shahen
#pragma once
#include <iostream>
#include <map>
#include <string>

class RandWriter {
 public:
  // create a Markov model of order k from given text
  explicit RandWriter(std::string text, int k);
  int orderK() const;   // order k of Markov model
  int freq(std::string kgram) const;   // Number of kgram occurences in text
  int freq(std::string kgram, char c) const;
  char kRand(std::string kgram);
  std::string generate(std::string kgram, int L);
  friend std::ostream& operator<< (std::ostream& out, RandWriter& obj);
 private:
  int order_k;
  std::map <std::string, std::map<char, int>> kgrams;
  std::string alph;
};
