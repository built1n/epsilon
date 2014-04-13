#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <cstdlib>
#include "room.h"
#include "object.h"
using namespace std;
extern map<int, Room> rooms;
extern double maxWeight;
void readMap(const char* file) // this function is VERY slow, but only needs to be called once
{
  ifstream ifs(file);
  if(!ifs.good())
    {
      cout << " " << file << " does not exist, or is not readable!" << endl;
      exit(1);
    }
  string line, currentObjectName;
  bool inWorld=false, inRoom=false, inObject=false;
  int currentRoom=-1, lineNumber=1;
  while(ifs)
    {
      getline(ifs,line); 
      stringstream ss(line);
      string firstWord;
      ss >> firstWord;
      if(firstWord=="World")
	{
	  double version;
	  ss >> version;
	  if(version!=1)
	    {
	      cout << "Warn: WoRLD file version appears to be mismatched." << endl;
	    }
	  inWorld=true;
	}
      else if(line=="EndWorld")
	{
	  inWorld=false;
	}
      else if(line=="EndObject")
	{
	  inObject=false;
	}
      else if(firstWord=="MaxWeight")
	{
	  if(inWorld)
	    ss >> maxWeight;
	}
      else if(firstWord=="Room")
	{
	  inRoom=true;
	  ss >> currentRoom;
	  string currentRoomName, currentRoomDesc;
	  while(ss.peek()!='\"')
	    ss.ignore(1);
	  ss.ignore(1);
	  getline(ss, currentRoomName, '\"');
	  while(ss.peek()!='\"')
	    ss.ignore(1);
	  ss.ignore(1);
	  getline(ss, currentRoomDesc, '\"');
	  Room temp;
	  temp.shortName=currentRoomName;
	  temp.description=currentRoomDesc;
	  temp.occupied=false;
	  rooms[currentRoom]=temp;  
	}
      if(inRoom)
	{
	  if(firstWord=="Object")
	    {
	      if(inRoom)
		{
		  string currentObjectDesc;
		  inObject=true;
		  ss >> currentObjectName;
		  while(ss.peek()!='\"')
		    ss.ignore(1);
		  ss.ignore(1);
		  getline(ss, currentObjectDesc,'"');
		  Object temp;
		  temp.name=currentObjectName;
		  temp.exists=true;
		  temp.takeable=false;
		  temp.weight=0;
		  temp.description=currentObjectDesc;
		  rooms[currentRoom].objects[currentObjectName]=temp;
		}
	    }
	  if(firstWord=="Require")
	    {
	      rooms[currentRoom].haveReqs=true;
	      while(ss.good())
		{
		  string obj;
		  ss >> obj;
		  rooms[currentRoom].requiredObjects.push_back(obj);
		}
	    }
	  if(firstWord=="RequireMessage")
	    {
	      string str;
	      ss.ignore(1);
	      while(ss.good())
		{
		  char c;
		  ss.get(c);
		  str+=c;
		}
	      str.erase(str.end());
	      rooms[currentRoom].reqMsg=str;
	      rooms[currentRoom].haveReqMsg=true;
	    }
	  if(firstWord=="Adjacent")
	    {
	      string direction;
	      ss >> direction;
	      int roomNumber;
	      ss >> roomNumber;
	      if(direction=="east")
		direction="e";
	      if(direction=="west")
		direction="w";
	      if(direction=="north")
		direction="n";
	      if(direction=="south")
		direction="s";
	      if(direction=="up")
		direction="u";
	      if(direction=="o")
		direction="out";
	      if(direction=="i")
		direction="in";
	      if(direction=="down")
		{
		  direction="d";
		}
	      if(direction=="n")
		{
		  rooms[currentRoom].toN=roomNumber;
		}
	      else if(direction=="s")
		{
		  rooms[currentRoom].toS=roomNumber;
		}
	      else if(direction=="e")
		{
		  rooms[currentRoom].toE=roomNumber;
		}
	      else if(direction=="w")
		{
		  rooms[currentRoom].toW=roomNumber;
		}
	      else if(direction=="ne")
		{
		  rooms[currentRoom].toNE=roomNumber;
		}
	      else if(direction=="se")
		{
		  rooms[currentRoom].toSE=roomNumber;
		}
	      else if(direction=="sw")
		{
		  rooms[currentRoom].toSW=roomNumber;
		}
	      else if(direction=="nw")
		{
		  rooms[currentRoom].toNW=roomNumber;
		}
	      else if(direction=="d")
		{
		  rooms[currentRoom].toD=roomNumber;
		}
	      else if(direction=="u")
		{
		  rooms[currentRoom].toU=roomNumber;
		}
	      else if(direction=="out")
		{
		  rooms[currentRoom].toOut=roomNumber;
		}
	      else if(direction=="in")
		{
		  rooms[currentRoom].toIn=roomNumber;
		}
	      else
		cout << "Expected direction on line " << lineNumber << endl;
	    }
	  if(firstWord=="Die") // kill the player
	    {
	      rooms[currentRoom].death=true;
	    }
	  if(firstWord=="DeathMessage")
	    {
	      string msg;
	      ss.ignore(1);
	      while(ss)
		{
		  char c;
		  ss.get(c);
		  msg+=c;
		}
	      msg.erase(msg.end());
	      rooms[currentRoom].deathMsg=msg;
	      rooms[currentRoom].haveDeathMsg=true;
	    }
	  if(firstWord=="NoReqDie")
	    {
	      rooms[currentRoom].noReqDie=true;
	    }
	  if(inObject)
	    {
	      if(firstWord=="Takeable")
		{
		  rooms[currentRoom].objects[currentObjectName].takeable=true;
		}
	      else if(firstWord=="Untakeable")
		{
		  rooms[currentRoom].objects[currentObjectName].takeable=false;
		}
	      else if(firstWord=="Alias")
		{
		  string alias;
		  ss >> alias;
		  rooms[currentRoom].objects[currentObjectName].aliases.push_back(alias);
		}
	      else if(firstWord=="Weight")
		{
		  double weight;
		  ss >> weight;
		  rooms[currentRoom].objects[currentObjectName].weight=weight;
		}
	      else if(firstWord=="Printable")
		{
		  rooms[currentRoom].objects[currentObjectName].printable=true;
		}
	      else if(firstWord=="Unprintable")
		{
		  rooms[currentRoom].objects[currentObjectName].printable=false;
		}
	    } // if(inObject)
	} // if(inRoom)
      ++lineNumber;
    } // while()
}
		
