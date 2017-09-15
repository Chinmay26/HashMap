# HashMap
This is C++ implementation of generic Hash table which uses linear probing to resolve collisions. This solution is inspired the standard C++ unordered_map & Boost unordered_map implmentation. This was a side-project. Obviously, this is not even close to being production ready.

## Example Usage

Declare your custom hash function based on input data type

```
struct MyHashCompute {
	size_t operator()(const string &key, const int  &hashSize=1000) const
	{
		return std::hash<std::string>() (key) % hashSize;
	}
};
```

Declare your custom hash function

```
MyHashMap<std::string,int,MyHashCompute> hmap(5);
```

Use customary hash functions

```
res =  hmap.set("coursera",2012);
res = hmap.set("airware",2011);

val = hmap.get("coursera");
val = hmap.get("flipboard"); \\ raises exception

val = hmap.delete_key("coursera");
```

For more documentation, refer [here.](https://github.com/Chinmay26/HashMap/blob/master/tests/Documentation)
