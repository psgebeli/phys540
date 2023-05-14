// Place k beads into n positions along a string
// Generate and print all possible configurations

#include <cstdlib>
using std::exit;
using std::strtol;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

void usage(void)
{
  cerr << "Usage: beads (k value) (n value)" << endl;
  cerr << " -- place k beads into n positions" << endl;
  cerr << " -- requires 0 < k <=n" << endl;
  exit(1);
}

int main(int argc, char *argv[])
{
  // parse the cmd line args
  size_t k, n;
  if (argc != 3)
    usage();

  return 0;
}
  
