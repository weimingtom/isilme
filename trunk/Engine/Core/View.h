#ifndef ISILME_VIEW_H
#define ISILME_VIEW_H

#include "Definitions.h"

/// @class View
/// Represents graphics model of the entity
/// View contains at least one graphics object
/// 
class ISILME_API View
{
public:
	View();
	virtual ~View();

	/// Sets view state
	///
	/// @param		state new state
	void SetState(std::string state);

	/// Draws view model
	void Draw(float x, float y, float angle) const;

	/// Adds graphics as effect
	void AddEffect(GraphicsPtr effect);
};
#endif