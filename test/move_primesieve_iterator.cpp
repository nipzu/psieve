///
/// @file   move_primesieve_iterator.cpp
/// @brief  Test the move constructor and move assignment operators
///         of the primesieve::iterator class.
///
/// Copyright (C) 2018 Kim Walisch, <kim.walisch@gmail.com>
///
/// This file is distributed under the BSD License. See the COPYING
/// file in the top level directory.
///

#include <primesieve.hpp>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void check(bool OK)
{
  cout << "   " << (OK ? "OK" : "ERROR") << "\n";
  if (!OK)
    exit(1);
}

int main()
{
  // test1 ///////////////////////////////////////////////////////////

  primesieve::iterator it;
  uint64_t prime = it.next_prime();
  uint64_t sum = 0;

  // use 1st iterator up to 5e8
  for (; prime < 500000000ull; prime = it.next_prime())
    sum += prime;

  // move constructor
  primesieve::iterator it2(std::move(it));

  // use 2nd iterator up to 1e9
  for (; prime < 1000000000ull; prime = it2.next_prime())
    sum += prime;

  cout << "Sum of the primes below 10^9 = " << sum;
  check(sum == 24739512092254535ull);

  // test2 ///////////////////////////////////////////////////////////

  // moved from objects can be reused
  // but they need to be reset
  it.skipto(0);
  prime = it.next_prime();
  sum = 0;

  // use 1st iterator up to 6e8
  for (; prime < 600000000ull; prime = it.next_prime())
    sum += prime;

  // move assignment operator
  primesieve::iterator it3;
  it3 = std::move(it);

  // use 3rd iterator up to 1e9
  for (; prime < 1000000000ull; prime = it3.next_prime())
    sum += prime;

  cout << "Sum of the primes below 10^9 = " << sum;
  check(sum == 24739512092254535ull);

  // test3 ///////////////////////////////////////////////////////////

  vector<primesieve::iterator> vect;
  vect.emplace_back(1000);
  prime = vect.back().prev_prime();
  cout << "1st prime < 1000 = " << prime;
  check(prime == 997);

  vect.emplace_back(std::move(it3));
  prime = vect.back().prev_prime();
  cout << "1st prime < 10^9 = " << prime;
  check(prime == 999999937);

  return 0;
}
