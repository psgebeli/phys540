// Version 2:
// Small Language Model that generates next words from the previous 
// four, three, two, or one, in descreasing order depending on whether 
// a match is available.

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

#include <fstream>
using std::ifstream;

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

         dictionary4[{ words[0], words[1], words[2], words[3] }] = words[4];
         dictionary3[{ words[1], words[2], words[3] }] = words[4];
         dictionary2[{ words[2], words[3] }] = words[4];
         dictionary1[ words[3] ] = words[4];
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

   {
      array<string,4> words = { argv[1], argv[2], argv[3], argv[4] };
      for (auto word : words)
         cout << word << " ";

      for (size_t n = 0; n < 250; ++n)
      {
         string response;
         if (dictionary4.contains(words))
            response = dictionary4[words];
         else if (dictionary3.contains({ words[1], words[2], words[3] }))
            response = dictionary3[{ words[1], words[2], words[3] }]; 
         else if (dictionary2.contains({ words[2], words[3] }))
            response = dictionary2[{ words[2], words[3] }];
         else if (dictionary1.contains(words[3]))
            response = dictionary1[words[3]];
         else
         {
            cout << endl;
            exit(1);
         }
         cout << response << " ";
         rotate(words.begin(), words.begin()+1, words.end());
         words[3] = response;
      }
   }
   cout << endl;
   return 0;
}

