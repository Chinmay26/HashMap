/*
 * HashMap.h
 *
 *  Created on: Sep 10, 2017
 *      Author: chinmay
 */
#include <functional>
#include <cstddef>

#ifndef HASHMAP_H_
#define HASHMAP_H_

// Uses std::hash as default hash function
template <typename T>
struct HashCompute {
	size_t operator()(const T &key, const int &hashSize=1000) const
	{
		return std::hash<T>() (key) % hashSize;
	}
};

template <class K, class V>
struct Bucket
{
	K key;
	V value;
	Bucket(const K &key, const V &value){
		this->key = key;
		this->value = value;
	}
};

template<class K, class V, class F = HashCompute<K>>
class MyHashMap{
public:
	MyHashMap(size_t sz){
		size = sz;
		Hashtable = new Bucket<K,V> *[size];
		for(size_t t = 0; t < size; t++){
			Hashtable[t] = nullptr;
			std::cout << "address of " << t << " :" << &Hashtable[t] << std::endl;
		}
		used_buckets = 0;
	}
	~MyHashMap(){
		for(size_t t = 0; t < size; t++){
			delete Hashtable[t];
		}
		delete[] Hashtable;
	}

	bool set(const K &key,const V &value){
		if(used_buckets + 1 > size ) return false;
		size_t val = hashCompute(key, this->size);
		size_t start = val;
		size_t end = (start>0) ? ((start-1) % size): size-1;

		while(start != end){
			if(Hashtable[start] == nullptr) break;
			else if (Hashtable[start] != nullptr && Hashtable[start]->key == key) return false;
			start = (start+1) % size;
		}
		if(start == end) return false;
		Hashtable[start] = new Bucket<K,V>(key, value);
		used_buckets += 1;
		return true;
	}

	V get(const K &key){
		if( used_buckets == 0){
			throw std::invalid_argument( "Key not found" );
		}
		size_t val = hashCompute(key, this->size);
		size_t start = val;
		size_t end = (start>0) ? ((start-1) % size): size-1;
		while(start != end){
			if( Hashtable[start] == nullptr){
				throw std::invalid_argument( "Key not found" );
			}
			else if (Hashtable[start] != nullptr && Hashtable[start]->key == key) {
				return Hashtable[start]->value;
			}
			start = (start+1)% size;
		}
		throw std::invalid_argument( "Key not found" );
	}

	V delete_key(const K &key){
		if( used_buckets == 0){
			throw std::invalid_argument( "Key not found" );
		}
		size_t val = hashCompute(key, this->size);
		size_t start = val;
		size_t end = (start>0) ? ((start-1) % size): size-1;
		while(start != end){
			if(Hashtable[start] == nullptr){
				throw std::invalid_argument( "Key not found" );
			}
			else if (Hashtable[start] != nullptr && Hashtable[start]->key == key){
				V val = Hashtable[start]->value;
				delete Hashtable[start];
				Hashtable[start] = nullptr;
				used_buckets -= 1;
				return val;
			}
			start = (start+1)% size;
		}
		throw std::invalid_argument( "Key not found" );
	}

	float load(){
		return (!size) ? 0 : (float(used_buckets) / size);
	}

private:
	Bucket<K,V> **Hashtable;
	size_t used_buckets;
	size_t size;
	F hashCompute;
};

#endif /* HASHMAP_H_ */
