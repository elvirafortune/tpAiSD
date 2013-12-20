#include <iostream>
#include<stdio.h>
#include <vector>
#include <string>
using namespace std;

enum state_t { empty = 0, used, deleted};

typedef string key_t;

struct Hash {
    key_t key;
    state_t state;
};



int H1(const key_t &key) {
    int k;
    size_t c = 12343;
    size_t a = 31247;
    size_t b = 42589;

    size_t value = c;
    size_t multiplier = 1;
    for (size_t i = 0; i < key.size(); ++i) {
        value += key[i] * multiplier;
        value = value % b;
        multiplier = (multiplier * a) % b;
     }

  return value % b;
}


int H2(const key_t &key) {
    size_t c = 14344;
    size_t a = 32823;
    size_t b = 42589;

    size_t value = c;
    size_t multiplier = 1;
    for (size_t i = 0; i < key.size(); ++i) {
        value += key[i] * multiplier;
        value = value % b;
        multiplier = (multiplier * a) % b;
  }

  return value % b;
}


int H(key_t k, int i, int M)
{
    return ((H1(k) + i*H2(k))%M);
}


class HashTable {
   
public:
    vector <Hash>* vec;
    HashTable()  {
        vec = new vector<Hash>(2);
    }
   

    
void Resize() {
    vector<Hash> *newvec = new vector<Hash>(vec->size() * 2);
    for (unsigned int i = 0; i < vec->size(); ++i) {
        if ((*vec)[i].state == used)
            insert_hash(newvec, &(*vec)[i]);
    }
    delete vec;
    vec = newvec;
}


    int insert_hash(vector<Hash> *&vec, Hash *hash) {
        for(int i = 0; i < vec->size(); ++i) {
            int j = H(hash->key, i, vec->size());
            if( (*vec)[j].state == empty || (*vec)[j].state == deleted) {
                (*vec)[j] = *hash; 
                (*vec)[j].state = used;
                return j;      // poziciya vstavlennogo elementa   
            }
            if((*vec)[j].key == hash->key)
                return -1;
        }

       // return -1; // -1 
        Resize(); //esli nekuda vstavlyat', to rasshirim
       insert_hash(vec, hash);
    } 

    int find(Hash *hash) {    
        for(int i = 0; i < vec->size(); ++i) {
            int j = H(hash->key,i,vec->size());
            if( (*vec)[j].state == empty )
                    return -1; // <=> ne nashli
            if( (*vec)[j].state == used && (*vec)[j].key == hash->key) 
                    return j;  
        }
        return -1;
    }

    int remove(Hash *hash) {
  
        int j = find(hash);
        if(j == -1)
            return -1;
        (*vec)[j].state = deleted;
        return 0;
    }

};




int main()
{
Hash hs;
HashTable ht;
hs.state=empty;

char command;

 while(cin>>command) {
   
   cin>>hs.key;

    if(command=='+') {
        if(ht.insert_hash(ht.vec, &hs) != -1)
               printf("OK\n");
           else printf("FAIL\n");
    
        } else if (command=='-') {
            if(ht.remove(&hs) != -1)
                printf("OK\n");
           else printf("FAIL\n");
        } else if (command=='?') {
    
           if ( ht.find(&hs) != -1)
               printf("OK\n");
           else printf("FAIL\n");
        } 
    }
//system("pause");
return 0;
}