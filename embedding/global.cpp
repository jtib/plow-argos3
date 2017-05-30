#include <vector>

/* ARGoS-related headers */
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/loop_functions.h>

#include "../crossroad_loop_footbot/crossroad_loop_footbot.h"

#include "global.h"

/****************************************/
/****************************************/

/*
 * Launch ARGoS to evaluate a set of weights.
 */
//decide on type for set of weights
float LaunchARGoS() {
  // creating the ARGoS experiment instance
  static argos::CSimulator& cSimulator = argos::CSimulator::GetInstance();
  // get ref to loop functions
  //static CCrossroadFunctionsFb& cLoopFunctions = dynamic_cast<CCrossroadFunctionsFb&>(cSimulator.GetLoopFunctions());
  // run one trial to get performance
  // vehicles can only change speed. Primary aim: no collisions. Secondary aim: go faster. 1: nb coll. 2: speed of each vehicle or average speed. Tuple. Int for now.
  int fCollisions = 0;
  //cLoopFunctions.SetTrial();
  cSimulator.Reset();//useful?
  // set the weights
  //cLoopFunctions.ConfigureFromList(cWeights);
  // run the experiment
  cSimulator.Execute();
  // update perf
  //fCollisions = cLoopFunctions.Performance();
  return fCollisions;
}

/****************************************/
/****************************************/

int main() {
  // create socket
  Sockets soc = Sockets::Sockets();
  // create environment
  Environment env = Environment::Environment();
  // link the two
  soc.setEnvironment(&env);
  // initialize the footbot ids dictionary
  std::map<std::string, int> fb_ids = {
                { "fu0", 0 },
                { "fu1", 1 },
                { "fd0", 2 },
                { "fd1", 3 },
                { "fl0", 4 },
                { "fl1", 5 },
                { "fr0", 6 },
                { "fr1", 7 } };    
  
  return 0;
}

