/*
Maciej Kapuscinski - Tablica mieszajaca AAL
*/
#ifndef AAL_HASHMAP
#define AAL_HASHMAP

#include<stdexcept>
#include<list>
#include<string>
#define MAXSIZE 10000


class HashMap
{
public:

  HashMap()
  {
    hashTab = new std::list<std::string>[SIZE];
    hash_used = 0;
  }

  HashMap(int HashUsed)
  {
    if(HashUsed<0 || HashUsed>1)
        throw std::invalid_argument("trying to use nonexistent hash function");
    hashTab = new std::list<std::string>[SIZE];
    hash_used = HashUsed;
  }

  ~HashMap()
  {
    clear();
    delete[] hashTab;
  }

  bool isEmpty() const
  {
    for(std::size_t i=0; i<SIZE; ++i)
    {
        if(!hashTab[i].empty())
            return false;
    }
    return true;
  }

  void add(const std::string& key)                  //dodanie słowa do tablicy mieszającej
  {
      std::size_t n = hashKey(key);
      for(auto &i: hashTab[n])
      {
          if(i==key)
          {
              throw std::overflow_error("key already in map");
          }
      }
      hashTab[n].push_back(key);
  }

  bool exists(const std::string& key) const         //sprawdzanie czy słowo już jest w tablicy
  {
    std::size_t n = hashKey(key);
    for(auto &i: hashTab[n])
    {
        if(i==key)
        {
            return true;
        }
    }
    return false;
  }

  void remove(const std::string key)                //usuwanie słowa z tablicy
  {
    if (isEmpty())
      throw std::out_of_range("trying to remove from empty map");
    std::size_t n = hashKey(key);
    for(auto i=hashTab[n].begin(); i!=hashTab[n].end(); ++i)
    {
        if ((*i)==key)
        {
            hashTab[n].erase(i);
            return;
        }
    }
    throw std::out_of_range("key not in map");
  }

  std::size_t getSize() const
  {
    std::size_t n = 0;
    for (std::size_t i=0; i<SIZE; ++i)
    {
        n += hashTab[i].size();
    }
    return n;
  }

private:

    std::list<std::string>* hashTab;
    static const std::size_t SIZE = MAXSIZE;
    size_t hash_used;

    void clear()                            //czyszczenie tablicy
    {
        for(std::size_t i=0; i<SIZE; ++i)
        {
            hashTab[i].clear();
        }
    }

    size_t hashKey(const std::string key) const     //funkcja mieszająca
    {
        std::size_t hash = 0;
        switch(hash_used)
        {
        case 0:                                     //wersja 1: wartość * miejsce modulo SIZE
            char c;
            for(std::size_t i=0; i<key.size(); ++i)
            {
                c = key[i];
                if(c>96&&c<123) c -= 71;   //male litery
                else if(c>64&&c<91) c -= 65;       //duze litery
                else throw std::invalid_argument("string contains forbidden characters");
                hash += c*(i+1) % SIZE;
            }
            hash %= SIZE;
            break;
        case 1:                                 //wersja 2: długość * wartość ascii pierwszej litery modula SIZE
            hash = (key.size() * key[0]) % SIZE;
            break;
        default:
            throw std::logic_error("nonexistent hash function picked");
            break;
        }
        return hash;
    }



};
#endif /* AAL_HASHMAP */

