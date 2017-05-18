/* ARGoS-related headers */
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/loop_functions.h>

#include "crossroad_loop_footbot/crossroad_loop_footbot.h"

/****************************************/
/****************************************/

/*
 * Launch ARGoS to evaluate a set of weights.
 */
//decide on type for set of weights
float LaunchARGoS(cWeights) {
  // creating the ARGoS experiment instance
  static argos::CSimulator& cSimulator = argos::CSimulator::GetInstance();
  // get ref to loop functions
  static CCrossroadFunctionsFb& cLoopFunctions = dynamic_cast<CCrossroadFunctionsFb&>(cSimulator.GetLoopFunctions());
  // run one trial to get performance
  // vehicles can only change speed. Primary aim: no collisions. Secondary aim: go faster. 1: nb coll. 2: speed of each vehicle or average speed. Tuple. Int for now.
  std::int fCollisions = 0;
  cLoopFunctions.SetTrial();
  cSimulator.Reset();//useful?
  // set the weights
  cLoopFunctions.ConfigureFromList(cWeights);
  // run the experiment
  cSimulator.Execute();
  // update perf
  fCollisions = cLoopFunctions.Performance();
  return fCollisions;
}

/****************************************/
/****************************************/

int main(int argc, char** argv) {
  // in

}

