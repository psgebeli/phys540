#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

int main()
{
  for (int i = 0; i < 32; ++i)
    {
      cout
	<< setw(3) << i << " : "
	<< (i & 16 ? 'o' : '-')
	<< (i & 8 ? 'o' : '-')
	<< (i & 4 ? 'o' : '-')
	<< (i & 2 ? 'o' : '-')
	<< (i & 1 ? 'o' : '-')
	<< endl;
    }
  return 0;
}
