
#include "Agents.h"


Agent::Agent()
{
}


std::vector<DetectedSheepRow> Agent::get_DetectedSheep()
{
	return DetectedSheep;
}
void Agent::UpdateDetectedSheepLocation(int i, int timestep, Vector2f location)
{
	DetectedSheep[i].sheepLastSeenTimeStep = timestep;
	DetectedSheep[i].sheepLastSeenLocation = location;
}


void Agent::add_DetectedSheep(DetectedSheepRow newRow)
{
	DetectedSheep.push_back(newRow);
}

