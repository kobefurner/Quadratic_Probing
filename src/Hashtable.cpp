#include "Hashtable.h"

int Hashtable::hash(int v) const{
   return v % capacity();
}
 
Hashtable::Hashtable()
{
}

Hashtable::Hashtable(int capacity)
{
}

Hashtable::Hashtable(int capacity, double threshold)
{
}

Hashtable::Hashtable(const Hashtable& other)
{
}

Hashtable& Hashtable::operator=(const Hashtable& other)
{
return *this;
}

Hashtable::~Hashtable()
{
}

int Hashtable::size() const
{
return -1;
}

int Hashtable::capacity() const
{
return -1;
}
double Hashtable::getLoadFactorThreshold() const
{
   return 0;
}

bool Hashtable::empty() const
{
return -1;
}

void Hashtable::insert(int value)
{
}

void Hashtable::remove(int value)
{
}

bool Hashtable::contains(int value) const{
return false;
}

int Hashtable::indexOf(int) const
{
   return -2;
}

void Hashtable::clear()
{
}

bool Hashtable::isPrime(int n){
   return false;
}

int Hashtable::nextPrime(int n){
   if(n > 73){ return 79; }
   if(n > 31){ return 37; }
   if(n > 13){ return 17; }
   return 2;
}
