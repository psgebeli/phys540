
import sys # for user input
import math # for arctan funct and square root


# arctan(x) = x[((((... + 1/9)x^2 - 1/7)x^2 + 1/5)x^2 - 1/3)x^2 + 1]

def atan_series(x, N): 

   x2 = x*x
   val = 0.0
   m = 2*N + 1
   for n in range(N, -1, -1): #
      val = val*x2 + ((-1)**n)/m 
      m -= 2
   return val*x



# arctan(x) = x[((((...+1)6/9y +1)4/7y +1)2/5y +1)-1/3y +1]

def atan_series2(x, N): 

   # in this for loop, the pattern is y*(2N)/(2N+3) + 1. However this pattern deviates
   # in the last iteration (N=0), where we have y(-1/3) + 1. 
   # To navigate this, I changed the loop to decrement until N=1 and start at N-1, then I stored 
   # its result as output and multiplied it by the final term. This is "result", which is 
   # the value of everything within the brackets, so I return that times x. 
   
   x2 = x*x
   val = 0.0 
   y = x2/(1+x2)
   m = 2*N + 3


   for n in range(N-1, 0, -1): # for n in range (start, end (NON INCLUSIVE), increment)
      val = val*y*(m-3)/m + 1
      m -= 2
   result = val*y*(-1/3) + 1
   return result*x


# arctan(x) = y/x * [((((.. + 1)8y/9 + 1)6y/7 + 1)4y/5 + 1)2/3y + 1]

def atan_series3(x, N): 

   x2 = x*x
   val = 0.0 
   y = x2/(1+x2)
   m = 2*N + 1 

   for n in range(N-1, -1, -1):
      val = val*y*((m+1)/(m+2)) + 1
      m -= 2
   return val*(y/x)



if len(sys.argv) != 2:
    
   print("Calculates the sequence of partial series expansions\n\n"
         "            x\n"
         "            x - x^3/3\n"
         "            x - x^3/3 + x^5/5\n"
         "            x - x^3/3 + x^5/5 - x^7/7\n"
         "            etc.\n\n"
         "approximating atan(x) = x - x^3/3 + x^5/5 - x^7/7 + ...\n\n"
         "Usage: python3 series.py x-value")
   sys.exit(1)

x = float(sys.argv[1])
print("\nFor x =", x, ", the successive partial expansions have the following values:\n")
for n in range(1, 31):
   print("{:>6d} {:>12.10e} {:>12.10e} {:>12.10e}".format(n, float(atan_series(x,n)), float(atan_series2(x,n)), float(atan_series3(x,n)))) # 2nd-4th f string converts arguments to 10-decimal precision float in scientific notation
print("{:>6} {:>12.10e} \n".format("inf", float(math.atan(x))))




