// Version 4:
// Small Language Model that generates next words from the previous 
// four, three, two, or one, in descreasing order depending on whether 
// a match is available. This version handles collisions in the map, 
// with the degeneracies stored ('+'-separated in a single concatenated
// string) and later sampled probabilistically. Here, the colouring
// indicates whether the next word is purely deterministic (green text)
// or has been chosen randomly (yellow).

#include <array>
using std::array;

#include <string>
using std::string;

#include <map>
using std::map;

#include <algorithm>
using std::rotate;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <sstream>
using std::stringstream;

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;

#include <tuple>
using std::tuple;
using std::make_tuple;
using std::tie;

#include <functional>
using std::bind;
using std::ref;

#include <random>
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::random_device;
using std::seed_seq;

// mersenne twistor random number generator
static mt19937 rng; 
// draw a real random number uniformly from [0,1)
static auto rnd = bind(uniform_real_distribution<double>(0,1),ref(rng)); 

void initialize_rng()
{
   array<int,624> seed_data;
   random_device r;
   generate_n(seed_data.data(), seed_data.size(), std::ref(r));
   seed_seq seq(std::begin(seed_data), std::end(seed_data));
   rng.seed(seq);
}

const string BrightRed = "\u001b[31;1m"; // \u001b = ESCAPE
const string BrightGreen = "\u001b[32;1m";
const string BrightYellow = "\u001b[33;1m";
const string BrightBlue = "\u001b[34;1m";
const string BrightMagenta = "\u001b[35;1m";
const string ResetColour = "\u001b[0m";

tuple<string,string> select(const string &s)
{
   vector<string> result;
   stringstream ss(s);
   string item;
   while (getline (ss, item, '+')) result.push_back(item);
   if (result.size() == 1) return make_tuple(BrightGreen,result[0]);
   else
      return make_tuple(BrightYellow,result[size_t(rnd()*result.size())]);
}

int main(int argc, char* argv[])
{
   // Training phase
   
   ifstream fin("corpus.txt");
   if (!fin.is_open())
   {
      cerr << "Could not find file 'corpus.txt'" << endl;
      exit(1);
   }
   
   map< array<string,4>, string > dictionary4;
   map< array<string,3>, string > dictionary3;
   map< array<string,2>, string > dictionary2;
   map< string, string > dictionary1;
   
   {
      array<string,5> words;
      fin >> words[0];
      fin >> words[1];
      fin >> words[2];
      fin >> words[3];
      fin >> words[4];

      dictionary3[{words[0], words[1], words[2] }] = words[3];
   
      dictionary2[{words[0], words[1] }] = words[2];
      dictionary2[{words[1], words[2] }] = words[3];

      dictionary1[words[0]] = words[1];
      dictionary1[words[1]] = words[2];
      dictionary1[words[2]] = words[3];
      
      const bool verbose = false;
      if (verbose)
         cout << "======================" << endl;
      while (fin)
      {
         if (verbose)
         {
            for (auto word : words)
               cout << word << " ";
            cout << endl;
         }
         
         if (!dictionary4.contains({words[0], words[1], words[2], words[3]}))
               dictionary4[{ words[0], words[1], words[2], words[3] }] = words[4];
         else dictionary4[{ words[0], words[1], words[2], words[3] }] += ("+" + words[4]);
         if (!dictionary3.contains({ words[1], words[2], words[3] }))
            dictionary3[{ words[1], words[2], words[3] }] = words[4];
         else
            dictionary3[{ words[1], words[2], words[3] }] += ("+" + words[4]);
         if (dictionary2.contains({ words[2], words[3] }))
            dictionary2[{ words[2], words[3] }] = words[4];
         else
            dictionary2[{ words[2], words[3] }] += ("+" + words[4]);
         
         if (dictionary1.contains(words[3]))
            dictionary1[words[3]] = words[4];
         else
            dictionary1[words[3]] += ("+" + words[4]);
         
         rotate(words.begin(), words.begin()+1, words.end());
         fin >> words[4];
      }
      if (verbose)
         cout << "======================" << endl;
   }

   // Generator phase
   
   if (argc != 5)
   {
      cerr << "Usage: slm four words as seed" << endl;
      exit(1);
   }

   initialize_rng();

   {
      array<string,4> words = { argv[1], argv[2], argv[3], argv[4] };
      for (auto word : words)
         cout << word << " ";

      for (size_t n = 0; n < 250; ++n)
      {
         string colour;
         string response;
         if (dictionary4.contains(words))
         {
            tie(colour,response) = select(dictionary4[words]);
         }
         else if (dictionary3.contains({ words[1], words[2], words[3] }))
         {
            tie(colour,response) = select(dictionary3[{ words[1], words[2], words[3] }]);
         }
         else if (dictionary2.contains({words[2],words[3]}))
         {
            tie(colour,response) = select(dictionary2[{ words[2], words[3] }]);
         }
         else if (dictionary1.contains(words[3]))
         {
            tie(colour,response) = select(dictionary1[words[3]]);
         }
         else
         {
            cout << ResetColour << endl;
            exit(1);
         }
         cout << colour << response << " ";
         rotate(words.begin(), words.begin()+1, words.end());
         words[3] = response;
      }
   }
   cout << endl;
   return 0;
}

