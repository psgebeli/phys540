#include <cstddef>
using std::size_t;

#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
using std::random_shuffle;

#ifdef USE_OPENGL
 #ifdef __APPLE__
  #include <GLUT/glut.h>
 #else
  #include <GL/glut.h>
 #endif
#endif

#include "mtrand.hpp"
mtrand R(1975);

#ifdef USE_OPENGL
const size_t L = 51;
const double d = 0.75/L;
const double dd = 0.85/L;
const int delay = 0; // milliseconds
#else
const size_t L = 501;
#endif

unsigned int sand[L][L];
unsigned long int grains = 0;

class coord
{
   public:
      size_t x;
      size_t y;
      coord(size_t x_, size_t y_) : x(x_), y(y_) {}
      friend bool operator<(const coord &c1, const coord &c2)
      {
         return c1.x < c2.x or (c1.x == c2.x and c1.y < c2.y);
      }
      friend bool operator==(const coord &c1, const coord &c2)
      {
         return c1.x == c2.x and c1.y == c2.y;
      }
};

#include <queue>
using std::queue; // pop from the front and push to the back
queue<coord> perim;

#include <set>
using std::set; // no duplicate items
set<coord> landslide;

void initialize_grid(void)
{
   for (size_t i = 0; i < L; ++i)
      for (size_t j = 0; j < L; ++j)
         sand[i][j] = 0;
}

void sweep_grid(void)
{
   size_t i, j;
   if (perim.empty())
   {
      if (!landslide.empty())
      {
         cout << grains << "\t" << landslide.size() << endl;
         landslide.clear();
      }
      i = R(L); // rand number in {0, 1, ..., L-1}
      j = R(L);
      ++grains;
   }
   else
   {
      coord c = perim.front();
      perim.pop();
      i = c.x;
      j = c.y;
   }
   ++sand[i][j];

   if (sand[i][j] >= 4)
   {
      sand[i][j] -= 4; // = 0;
      size_t indx[4] = { 0, 1, 2, 3 };
      const coord c[4] = { coord((i+1)%L,j), coord(i,(j+1)%L), 
         coord(i,(L+j-1)%L), coord((L+i-1)%L,j) };
      random_shuffle(indx,indx+4,R);
      perim.push(c[indx[0]]);
      perim.push(c[indx[1]]);
      perim.push(c[indx[2]]);
      perim.push(c[indx[3]]);
      landslide.insert(coord(i,j));
   }
}

#ifdef USE_OPENGL
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
   for (const auto &c : landslide)
   {
      const double x = 2.0*(c.x+0.5)/L - 1.0;
      const double y = 2.0*(c.y+0.5)/L - 1.0;
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
   glutDisplayFunc(display);
   glutTimerFunc(delay,animate,0);

   initialize_grid();
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glutMainLoop();
}
#else
int main()
{
   initialize_grid();
   for (unsigned long int i = 0; i < 400ul*L*L; ++i)
      sweep_grid();
}
#endif
