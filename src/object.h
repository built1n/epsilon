#pragma once
#include <vector>
#include <string>
using namespace std;
struct Object {
  vector<string> aliases;
  bool takeable=false, exists=false, printable=false;
  string name, description;
  double weight=0; // in kg
};
