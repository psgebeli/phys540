#include <cstddef>
using std::size_t;

#include <cassert>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <algorithm>
using std::shuffle;
using std::generate_n;

#include <functional>
using std::bind;
using std::ref;

//#include <utility>
//using std::pair;

#include <tuple>
using std::tuple;
using std::make_tuple;
using std::get;

#ifdef USE_OPENGL
 #ifdef __APPLE__
  #include <GLUT/glut.h>
 #else
  #include <GL/glut.h>
 #endif
#endif
      
#ifdef USE_OPENGL
const size_t L = 13;
const double d = 0.75/L;
const double dd = 0.85/L;
const int delay = 0; // milliseconds
#else
const size_t L = 501;
#endif

unsigned int sand[L][L];
unsigned long int grains = 0;

#include <random>
using std::mt19937;
using std::uniform_int_distribution;
using std::random_device;
using std::seed_seq;

// mersenne twistor random number generator
static mt19937 rng; 
// draw a random number uniformly from {0,2,...,L-1}
static auto rnd = bind(uniform_int_distribution<int>(0,L-1),ref(rng)); 

#include <array>
using std::array;

void initialize_rng()
{
   array<int,624> seed_data;
   random_device r;
   generate_n(seed_data.data(), seed_data.size(), std::ref(r));
   seed_seq seq(std::begin(seed_data), std::end(seed_data));
   rng.seed(seq);
}

#include <queue>
using std::queue; // pop from the front and push to the back
//queue<coord> perim;
queue<tuple<size_t,size_t>> perim;

#include <set>
using std::set; // no duplicate items
//set<coord> landslide;
set<tuple<size_t,size_t>> landslide;

void initialize_grid(void)
{
   for (size_t i = 0; i < L; ++i)
      for (size_t j = 0; j < L; ++j)
         sand[i][j] = 0;
}

void sweep_grid(void)
{
   tuple<size_t, size_t> here;
   if (perim.empty())
   {
      if (!landslide.empty())
      {
#ifndef USE_OPENGL         
         cout << grains << "\t" << landslide.size() << endl;
#endif         
         landslide.clear();
      }
      here = make_tuple(rnd(),rnd());
      ++grains;
   }
   else
   {
      here = perim.front();
      perim.pop();
   }
   const auto [i,j] = here;
   ++sand[i][j];
   if (sand[i][j] >= 4)
   {
      sand[i][j] -= 4; // = 0;
      tuple<size_t,size_t> neighbour[4] = { make_tuple((i+1)%L,j), 
                                            make_tuple(i,(j+1)%L),
                                            make_tuple(i,(L+j-1)%L), 
                                            make_tuple((L+i-1)%L,j) };
      shuffle(neighbour,neighbour+4,rng);
      perim.push(neighbour[0]);
      perim.push(neighbour[1]);
      perim.push(neighbour[2]);
      perim.push(neighbour[3]);
      landslide.insert(here);
   }
}

#ifdef USE_OPENGL
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q') exit(0);
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   for (size_t i = 0; i < L; ++i)
      for (size_t j = 0; j < L; ++j)
         if (sand[i][j] != 0)
         {
            const double x = 2.0*(i+0.5)/L - 1.0;
            const double y = 2.0*(j+0.5)/L - 1.0;
            const double c = 0.25*sand[i][j];
            glColor3d(1.0-c*c, 1.0-c, 1.0-c*c);
            glBegin(GL_POLYGON);
               glVertex2f(x-d,y-d);
               glVertex2f(x-d,y+d);
               glVertex2f(x+d,y+d);
               glVertex2f(x+d,y-d);
            glEnd();
            glFlush();
         }
   for (const auto &coord : landslide)
   {
      const double x = 2.0*(get<0>(coord)+0.5)/L - 1.0;
      const double y = 2.0*(get<1>(coord)+0.5)/L - 1.0;
      glColor3d(0.0, 0.0, 0.0);
      glBegin(GL_LINE_LOOP);
      glVertex2f(x-dd,y-dd);
      glVertex2f(x-dd,y+dd);
      glVertex2f(x+dd,y+dd);
      glVertex2f(x+dd,y-dd);
      glEnd();
      glFlush();
   }
   glutSwapBuffers();
}

void animate(int)
{
   sweep_grid();
   glutPostRedisplay();
   glutTimerFunc(delay,animate,0);
}

int main(int argc, char **argv)
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(640,640);
   glutInitWindowPosition(100,100);
   glutCreateWindow("Sandpile");
	glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutTimerFunc(delay,animate,0);

   initialize_rng();
   initialize_grid();
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glutMainLoop();
}
#else
int main()
{
   initialize_rng();
   initialize_grid();
   for (unsigned long int i = 0; i < 750ul*L*L; ++i)
   {
      if (i%50000 == 0)
         cerr << "sweep: " << i/10000 << " x 10000"<< endl;
      sweep_grid();
   }
}
#endif
