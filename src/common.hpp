#ifndef COMMON_HPP_
#define COMMON_HPP_


#include <stdint.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;


#define ASSERT(C,MSG) \
  if (!(C)) { \
    cout << MSG << endl; \
    assert(C); \
  }


typedef uint32_t uint;
namespace CoreIR {

typedef enum {AINT=0,ASTRING=1,ATYPE=2,ABOOL=3} Param;

//other
class Namespace;
class Context;
struct Error;
class Arg;
class ArgInt;
class ArgString;
class ArgType;
class ArgBool;
typedef unordered_map<string,Param> Params;
typedef unordered_map<string,Arg*> Args;


// This is so I do not overload the std::hash<std::pair<T1,T2>> class.
// Use myPair for hashing
template<class T1, class T2>
struct myPair {
  T1 first;
  T2 second;
  myPair(T1 first, T2 second) : first(first), second(second) {}
  friend bool operator==(const myPair& l,const myPair& r) {
    return l.first==r.first && l.second==r.second;
  }
};

class Type;
class TypeGen;
class NamedType;
typedef Type* (*TypeGenFun)(Context* c, Args args);
typedef vector<myPair<string,Type*>> RecordParams ;
typedef myPair<uint,Type*> ArrayParams ;
class TypeCache;
struct Metadata;


//instantiable.hpp
class Instantiable;
class Generator;
class Module;
class ModuleDef;
typedef void (*ModuleDefGenFun)(ModuleDef*,Context*, Type*, Args);

class SelCache;
class Wireable;
class Interface;
class Instance;
class Select;

typedef vector<string> SelectPath;
typedef vector<std::reference_wrapper<const string>> ConstSelectPath;
typedef myPair<Wireable*,Wireable*> Connection;


//TODO This stuff is super fragile. 
// Magic hash function I found online
template <class T> 
inline void hash_combine(size_t& seed, const T& v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

//These are defined in helpers
bool isNumber(string s);
string Param2Str(Param);
string Params2Str(Params);
string Args2Str(Args);
//Will call assertions
void checkArgsAreParams(Args args, Params params);

Param Str2Param(string s);
string SelectPath2Str(SelectPath s);
vector<std::string> splitString(const string &s, char delim);
bool hasChar(const std::string s, char c);



} //CoreIR namespace

namespace std {
  //slow
  template <class T1, class T2>
  struct hash<CoreIR::myPair<T1,T2>> {
    //template <class T1, class T2>
    size_t operator() (const CoreIR::myPair<T1,T2>& p) const {
      auto h1 = std::hash<T1>{}(p.first);
      auto h2 = std::hash<T2>{}(p.second);
      return h1 ^ (h2<<1);
    }
  };

  template <>
  struct hash<CoreIR::Args> {
    size_t operator() (const CoreIR::Args& args) const;
  };

}

#endif //COMMON_HPP_
