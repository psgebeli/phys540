// Version 1:
// Small Language Model that generates next words from the previous four

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

   map< array<string,4>, string > dictionary;

   array<string,5> words;
   fin >> words[0];
   fin >> words[1];
   fin >> words[2];
   fin >> words[3];
   fin >> words[4];

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

      const array<string,4> call = { words[0], words[1], words[2], words[3] };
      const string response = words[4];
      dictionary[call] = response;
      rotate(words.begin(), words.begin()+1, words.end());
      fin >> words[4];
   }
   if (verbose)
      cout << "======================" << endl;

   // Generator phase
   
   if (argc != 5)
   {
      cerr << "Usage: slm four words as seed" << endl;
      exit(1);
   }

   array<string,4> call = { argv[1], argv[2], argv[3], argv[4] };
   for (auto word : call)
      cout << word << " ";

   for (size_t n = 0; n < 500; ++n)
   {
      if (dictionary.contains(call))
      {
         const string response = dictionary[call];
         cout << response << " ";
         rotate(call.begin(), call.begin()+1, call.end());
         call[3] = response;
         // ( call[0], call[1], call[2], call[3] )
         // --> ( call[1], call[2], call[2], response )
      }
      else
         exit(1);
   }
   cout << endl;
   return 0;
}

