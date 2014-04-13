#include "read.h"
#include "room.h"
#include "object.h"
#include <map>
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
using namespace std;
map<int, Room> rooms;
map<string, Object> inventory;
double maxWeight=-1, currentWeight;
string mapName="default.world";
int main(int argc, char* argv[])
{
  if(argc==1)
    {
      cout << "Loading from default.world..." << flush;
      readMap("default.world");
      cout << " Done." << endl;
    }
  else
    {
      cout << "Loading from " << argv[1] << "...";
      readMap(argv[1]);
      mapName=argv[1];
      cout << " Done." << endl;
    }
  if(maxWeight>=0)
    cout << "You can carry a maximum of " << maxWeight << " kg." << endl;
  int currentRoom=1;
  string input="help";
  while(input!="exit")
    {
      int oldRoom=currentRoom;
      cout << rooms[currentRoom].shortName << endl;
      if(!rooms[currentRoom].occupied) // we have never been here
	{
	  cout << rooms[currentRoom].description << endl;
	  rooms[currentRoom].occupied=true;
	}
      // print all visible objects
      
      cout << "> " << flush;
      getline(cin, input);
      stringstream ss(input);
      string str;
      ss>>str;
      if(str=="e")
	{
	  if(rooms[currentRoom].toE!=-1)
	    {
	      currentRoom=rooms[currentRoom].toE;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="s")
	{
	  if(rooms[currentRoom].toS!=-1)
	    {
	      currentRoom=rooms[currentRoom].toS;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="w")
	{
	  if(rooms[currentRoom].toW!=-1)
	    {
	      currentRoom=rooms[currentRoom].toW;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="n")
	{
	  if(rooms[currentRoom].toN!=-1)
	    {
	      currentRoom=rooms[currentRoom].toN;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="ne")
	{
	  if(rooms[currentRoom].toNE!=-1)
	    {
	      currentRoom=rooms[currentRoom].toNE;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="se")
	{
	  if(rooms[currentRoom].toSE!=-1)
	    {
	      currentRoom=rooms[currentRoom].toSE;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="nw")
	{
	  if(rooms[currentRoom].toNW!=-1)
	    {
	      currentRoom=rooms[currentRoom].toNW;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="sw")
	{
	  if(rooms[currentRoom].toSW!=-1)
	    {
	      currentRoom=rooms[currentRoom].toSW;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="u")
	{
	  if(rooms[currentRoom].toU!=-1)
	    {
	      currentRoom=rooms[currentRoom].toU;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="d")
	{
	  if(rooms[currentRoom].toD!=-1)
	    {
	      currentRoom=rooms[currentRoom].toD;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="in")
	{
	  if(rooms[currentRoom].toIn!=-1)
	    {
	      currentRoom=rooms[currentRoom].toIn;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="out")
	{
	  if(rooms[currentRoom].toOut!=-1)
	    {
	      currentRoom=rooms[currentRoom].toOut;
	    }
	  else
	    cout << "You can't go that way!"<< endl;
	}
      else if(str=="l")
	{
	  if(!ss.good())
	    cout << rooms[currentRoom].description << endl;
	  else
	    {
	      string obj;
	      ss >> obj;
	      if(rooms[currentRoom].objects[obj].exists)
		cout << rooms[currentRoom].objects[obj].description << endl;
	      else if(inventory[obj].exists)
		cout << inventory[obj].description << endl;
	      else
		cout << "I don't know what that is." << endl;
	    }
	}
      else if(str=="take")
	{
	  string obj;
	  ss >> obj;
	  if(rooms[currentRoom].objects[obj].takeable && rooms[currentRoom].objects[obj].exists)
	    {
		if(currentWeight+rooms[currentRoom].objects[obj].weight<=maxWeight or maxWeight<0)
		  {
		    inventory[obj]=rooms[currentRoom].objects[obj];
		    currentWeight+=rooms[currentRoom].objects[obj].weight;
		    rooms[currentRoom].objects[obj].exists=false;
		    cout << "Taken." << endl << "You are carrying " << currentWeight << " kg. of items." << endl;
		  }
		else
		  cout << "Your load would be too heavy.";
	    }
	  else
	    cout << "I don't know what that is." << endl;
	}
      else if(str=="drop")
	{
	  string obj;
	  ss >> obj;
	  if(inventory[obj].exists)
	    {
	      rooms[currentRoom].objects[obj]=inventory[obj];
	      currentWeight-=inventory[obj].weight;
	      inventory[obj].exists=false;
	    }
	  else
	    cout << "I don't know what that is." << endl;
	}
      else if(str=="loadmap")
	{
	  string map;
	  ss >> map;
	  rooms.clear();
	  readMap(map.c_str());
	  currentRoom=1;
	  currentWeight=0;
	  inventory.clear();
	}
      else
	cout << "I do not understand that." << endl;
      if(rooms[currentRoom].death)
	{
	  if(rooms[currentRoom].haveDeathMsg)
	    cout << rooms[currentRoom].deathMsg << endl;
	  cout << "You are dead." << endl;
	  goto gameOver;
	}
      if(rooms[currentRoom].haveReqs and currentRoom!=oldRoom)
	{
	  bool good=true;
	  for(int i=0;i<rooms[currentRoom].requiredObjects.size();++i)
	    {
	      if(!inventory[rooms[currentRoom].requiredObjects[i]].exists)
		{
		  good=false;
		}
	    }
	  if(!good and str!="drop")
	    {
	      if(!rooms[currentRoom].noReqDie)
		{
		  if(rooms[currentRoom].haveReqMsg)
		    cout << rooms[currentRoom].reqMsg << endl;
		  else
		    cout << "You cannot go there." << endl;
		  currentRoom=oldRoom;
		}
	      else
		{
		  cout << rooms[currentRoom].deathMsg << endl;
		  cout << "You are dead." << endl;
		  goto gameOver;
		}
	    }
	}
    }
 gameOver:
  return 0;
}
