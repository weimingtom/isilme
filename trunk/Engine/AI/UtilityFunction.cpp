#include "IsilmePCH.h"
#include "UtilityFunction.h"
#include "Perception.h"

UtilityFunction::~UtilityFunction()
{

}

WeightUtilityFunction::WeightUtilityFunction()
{

}

WeightUtilityFunction::~WeightUtilityFunction()
{

}

float WeightUtilityFunction::Calculate( BehaviourPtr behaviour ) const 
{
	float result = 0.0f;

	for (PIVector::const_iterator it = mPerceptions.cbegin(); it != mPerceptions.cend(); ++it)
		result += it->weight * it->perception->GetValue(behaviour);

	return result;
}

void WeightUtilityFunction::AddPerception( PerceptionPtr perception, float weight )
{
	PerceptionInfo pi;
	pi.perception = perception;
	pi.weight = weight;
	mPerceptions.push_back(pi);
}
