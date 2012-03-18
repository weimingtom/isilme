#ifndef ISILME_AI_UTILITYFUNCTION_H
#define ISILME_AI_UTILITYFUNCTION_H

#include "Definitions.h"
#include "AITypes.h"

/// @class UtilityFunction
class ISILME_API UtilityFunction
{
public:
	virtual ~UtilityFunction();

	/// Calculates utility value
	virtual float Calculate(BehaviourPtr behaviour) const = 0;

private:

};


class ISILME_API WeightUtilityFunction : public UtilityFunction
{
public:
	WeightUtilityFunction();
	virtual ~WeightUtilityFunction();

	virtual float Calculate(BehaviourPtr behaviour) const override;

	/// Adds perception to utility-function
	void AddPerception(PerceptionPtr perception, float weight);
private:
	/// @struct PerceptionInfo
	/// Internal container for weights of perceptions
	struct PerceptionInfo
	{
		/// Perception
		PerceptionPtr perception;

		/// Weight
		float weight;
	};

	typedef std::vector<PerceptionInfo> PIVector;

	/// Perceptions
	PIVector mPerceptions;

};
#endif