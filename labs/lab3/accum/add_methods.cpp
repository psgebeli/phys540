#include <cassert>

#include <vector>
using std::vector;

#include <algorithm>
using std::sort;

#include <numeric>
using std::accumulate;

float add_pairwise(const vector<float> &v)
{
	// add your code here
  if (v.size() == 0) return 0.0F;
  vector<float> sorted(v);
  sort(sorted.begin(), sorted.end());
  float sum = sorted.back();
  for (size_t i = 1; i < sorted.size(); i +=2)
    sum += sorted[i] + sorted[i-1];
  return sum;

  // return 0 if v has no elements (obvously)
  // create a new vector sorted(v) which we populate with the sorted version of v
  // set sum equal to last element of this sorted vector
  // we loop over size_t, which is unsigned, and commonly used for the "size" ofd something.
  // anyways, we loop over the size of the vector, adding the ith element and the previous element to the sum.
  // we increment i by 2 rather than 1, as this is pairwise 
}

float add_increasing(const vector<float> &v)
{
	// add your code here
  float sum = v[0];
  for (size_t i = 1; i < v.size(); ++i)
    {
      if (v[i] > 0 && sum > std::numeric_limits<float>::max() - v[i])
	{
	  // handle overflow
	  sum = std::numeric_limits<float>::infinity();
	  break;
	}
      sum += v[i];
    }
  return sum;

  // initialize the sum to be the 0th element of v, then incremenet i = 1 over the size of the vector, adding the ith element to the sum
  // however, an if statement handles overflow by stopping at the first instance of infinity
}


   

float add_decreasing(const vector<float> &v)
{
	// add your code here
  float sum = v[0];
  for (size_t i = v.size() -1; i > 0; --i)
    {
      if (v[i] < 0 && sum < std::numeric_limits<float>::lowest()-v[i])
	{
	  // handle underflow
	  sum = -std::numeric_limits<float>::infinity();
	  break;
	}
      sum += v[i];

    }
  return sum;
  // pretty much the same as the previous function, just incrementing in the opposite direction and handling underflow rather than overflow
}	

float add_conventional(const vector<float> &v)
{
	return accumulate(v.begin(),v.end(),0.0F);
	// last line is equivalent to the following:
	// float sum = v[0];
	// for (int i = 1; i < v.size(); ++i)
	//    sum += v[i];
	// return sum;

	// unchanged
}

float add_compensated(const vector<float> &v)
{
	// add your code here

  float sum = v[0];
  float c = 0.0F;
  for (size_t i = 1; i < v.size(); ++i)
    {
      float y = v[i] -c;
      float t = sum + y;
      c = (t - sum) -y;
      sum = t;
    }
  return sum;

  // implementation of kahan summation compensation -- c stores any floating point addition errors.
}


float add_high_precision(const vector<float> &v)
{
	// add your code here
  long double sum = static_cast<long double>(v[0]);
  for (size_t i = 1; i < v.size(); ++i)
    sum += v[i];
  return static_cast<float>(sum);

  // same as add increasing but doesnt account for overflow, assuming long double is enough to handle the floating arithmetic 
}

