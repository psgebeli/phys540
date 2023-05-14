#include <iostream> //import input/output library

using std::cout; //character output
using std::endl; //to insert newline character


//making main method

int main()
{
  //practice using the character data type
  char a = 'k';

  /*send text to console in the order of "He", then the letter after k (l, done with a
   pre increment), then "lo World!"*/

  cout << "He" << ++a << "lo World!" << endl;

  /*since our method is an int type we need to return an int, 0 is the convention and is
    essentially saying "the program was successful"*/
  
  return 0;

}
