#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <vector>

class Hashtable
{
   private:
        struct Node {
                int key;
                int value;
                bool isActive;

                Node(int k = int{}, int v = int{}) : key{k}, value{v}, isActive{true} {}
        };

      std::vector<Node> array;
      int currentSize;
      double loadFactorThreshold;  
        
      int hash(int v) const;
public:
	Hashtable();
	Hashtable(int);
	Hashtable(int, double);
	Hashtable(const Hashtable& other);
	Hashtable& operator=(const Hashtable& other);
	~Hashtable();

        int size() const;
        int capacity() const;
        double getLoadFactorThreshold() const;
        bool empty() const;
	void insert(const int);
        void remove(int);
        bool contains(int) const;
        int indexOf(int) const;
        void clear();
        static bool isPrime(int n);
        static int nextPrime(int n);
        void resize(int);
        void insertWithoutResizing(int value, bool isResizing = false);
};
#endif 
