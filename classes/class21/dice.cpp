#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <utility>
using std::pair;
using std::make_pair;

#include <algorithm>
using std::make_pair;

// fair dice
//vector<int> dieA = { 1, 2, 3, 4, 5, 6 };
//vector<int> dieB = { 1, 2, 3, 4, 5, 6 };

// nontransitive dice
//vector<int> dieA = { 2, 3, 4, 15, 16, 17 };
//vector<int> dieB = { 5, 6, 7, 8, 9, 18 };
//vector<int> dieC = { 1, 10, 11, 12, 13, 14 };

// Badley Efron's dice
vector<int> dieA = { 1, 1, 5, 5, 5, 5 };
vector<int> dieB = { 4, 4, 4, 4, 4, 4 };
vector<int> dieC = { 3, 3, 3, 3, 7, 7 };
vector<int> dieD = { 2, 2, 2, 6, 6, 6 };

pair<int, int> compete(const vector<int> &A, const vector<int> &B)
{
   int tallyA = 0;
   int tallyB = 0;
   for (auto a : A)
      for (auto b : B)
         if (a > b)
            ++tallyA;
         else if (b > a)
            ++tallyB;
   return make_pair(tallyA, tallyB);
}

void report_wins(const vector<int> &die1, const vector<int> &die2)
{
   auto [ wins1, wins2 ] = compete(die1, die2);
   cout << wins1 << (wins1 > wins2 ? " > " :
                     (wins1 < wins2 ? " < " : " = "))
        << wins2 << endl;
}

void report_winner(string name1, string name2,
      const pair<int, int> &wins)
{
   if (wins.first == wins.second)
   {
      cout << "Dice " << name1 << " and " << name2 << " are tied." << endl;
      return;
   }
   if (wins.second > wins.first)
      swap(name1, name2);
   cout << "Die " << name1 << " beats die " << name2 << "." << endl;
   return;
}

int main()
{
   report_winner("A", "B", compete(dieA, dieB));
   report_wins(dieA, dieB);
   report_winner("B", "C", compete(dieB, dieC));
   report_wins(dieB, dieC);
   report_winner("C", "D", compete(dieC, dieD));
   report_wins(dieC, dieD);
   report_winner("D", "A", compete(dieD, dieA));
   report_wins(dieD, dieA);

   return 0;
}
