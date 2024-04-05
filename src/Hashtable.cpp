#include "Hashtable.h"

int Hashtable::hash(int v) const{
   return v % capacity();
}
 
Hashtable::Hashtable() {
    array = std::vector<Node>(17);
    currentSize = 0;
    loadFactorThreshold = 0.65;

    // Initialize all elements to inactive
    for (auto &entry : array) {
        entry.isActive = false;
    }
}

Hashtable::Hashtable(int capacity)
{
   currentSize = 0;
   loadFactorThreshold = 0.65;
   array.resize(capacity);
}

Hashtable::Hashtable(int capacity, double threshold)
{
   currentSize = 0;
   loadFactorThreshold = threshold;
   array.resize(capacity);
}

Hashtable::Hashtable(const Hashtable& other)
{
   currentSize = other.currentSize;
   loadFactorThreshold = other.loadFactorThreshold;
   array = other.array;
}

Hashtable& Hashtable::operator=(const Hashtable& other)
{
   if (this != &other) {
      currentSize = other.currentSize;
      loadFactorThreshold = other.loadFactorThreshold;
      array = other.array;
   }
   return *this;
}

Hashtable::~Hashtable()
{
   clear();
}

int Hashtable::size() const
{
   return currentSize;
}

int Hashtable::capacity() const
{
   return array.size();
}

double Hashtable::getLoadFactorThreshold() const
{
   return loadFactorThreshold;
}

bool Hashtable::empty() const
{
   return currentSize == 0;
}

void Hashtable::insert(int value) {
    int initialIndex = hash(value) % array.size();
    int index = initialIndex;
    int i = 0;

    while (array[index].isActive && array[index].value != value) {
        i++;
        index = (initialIndex + i * i) % array.size();
        if (i >= array.size()) {
            resize(nextPrime(2 * array.size()));
            index = hash(value) % array.size();
            initialIndex = index; // Update initialIndex after resizing
            i = 0; // Reset i after resizing
        }
    }

    if (!array[index].isActive || array[index].value != value) {
        array[index] = Node(value, value);
        currentSize++;
    }

    // Check load factor after insertion
    double loadFactor = (double)currentSize / array.size();
    if (loadFactor > loadFactorThreshold) {
        resize(nextPrime(2 * array.size()));
    }
}

void Hashtable::resize(int newSize) {
    std::vector<Node> oldArray = array;
    array.clear();
    array.resize(newSize);

    for (auto &entry : array) {
        entry.isActive = false;
    }

    currentSize = 0;  // Reset currentSize

    for (auto &entry : oldArray) {
        if (entry.isActive) {
            insertWithoutResizing(entry.value, true);
        }
    }

    if (currentSize >= array.size()) {
        throw std::runtime_error("Hashtable is full after resizing");
    }
}

void Hashtable::insertWithoutResizing(int value, bool isResizing)
{
   if (!isResizing && currentSize >= array.size()) {
      throw std::runtime_error("Hashtable is full in insertWithoutResizing");
   }

   int initialIndex = hash(value) % array.size();
   int index = initialIndex;
   int i = 0;

   while (array[index].isActive && array[index].value != value) {
      i++;
      index = (initialIndex + i * i) % array.size();
      if (i >= array.size()) {
         resize(nextPrime(2 * array.size()));
      }
   }

   if (!array[index].isActive || array[index].value != value) {
      array[index] = Node(value, value);
      currentSize++;
   }
}

void Hashtable::remove(int value) {
    int initialIndex = hash(value) % array.size();
    int index = initialIndex;
    int i = 0;

    while (array[index].isActive || array[index].value != value) {
        if (array[index].value == value) {
            break;
        }
        i++;
        index = (initialIndex + i * i) % array.size();
        if (i > array.size()) {
            throw std::runtime_error("Hashtable is full in remove function");
        }
    }

    if (array[index].isActive && array[index].value == value) {
        array[index].isActive = false;
        currentSize--;
    }
}

bool Hashtable::contains(int value) const {
    int initialIndex = hash(value) % array.size();
    int index = initialIndex;
    int i = 0;

    while (array[index].isActive || array[index].value != value) {
        if (array[index].value == value) {
            break;
        }
        i++;
        index = (initialIndex + i * i) % array.size();
        if (i > array.size()) {
            return false;
        }
    }

    return array[index].isActive && array[index].value == value;
}

int Hashtable::indexOf(int value) const
{
   int index = hash(value) % array.size();
   int i = 0;

   while (array[index].isActive && array[index].value != value) {
      i++;
      index = (hash(value) + i * i) % array.size();
      if (i >= array.size()) {
            break;
        }
   }

    if (array[index].isActive && array[index].value == value) {
      return index;
   } else {
      return -1;
   }
}

void Hashtable::clear()
{
   for (auto &entry : array) {
        entry.isActive = false;
    }
    currentSize = 0;
}

bool Hashtable::isPrime(int n) {
   if (n <= 1) {
      return false;
   }
   if (n <= 3) {
      return true;
   }
   if (n % 2 == 0 || n % 3 == 0) {
      return false;
   }
   for (int i = 5; i * i <= n; i += 6) {
      if (n % i == 0 || n % (i + 2) == 0) {
         return false;
      }
   }
   return true;
}

int Hashtable::nextPrime(int n){
   while (!isPrime(n)) {
      n++;
   }
   return n;
}