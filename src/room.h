#include <vector>
#include "object.h"
#include <string>
#include <map>
using namespace std;
struct Room {
public:
  map<string, Object> objects;
  int number=-1;
  int toN=-1, toNE=-1, toE=-1, toSE=-1, toS=-1, toSW=-1, toW=-1, toNW=-1, toU=-1, toD=-1, toIn=-1, toOut=-1;
  string shortName;
  string description;
  bool occupied, death=false, haveDeathMsg=false, noReqDie=false;
  string deathMsg;
  vector<string> requiredObjects; // what do we need to come here?
  bool haveReqs=false, haveReqMsg=false;
  string reqMsg; // what to say if we do not have the requirements
};
