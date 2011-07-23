#include "Isilme.h"
#include "ActionManager.h"


ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

void	ActionManager::Update(float elapsedTime)
{
	for (ActionSet::iterator it = mAttention.begin(); it != mAttention.end(); ++it)
	{
		ActionPtr	action = *it;
		bool isDone = action->Update(elapsedTime);

		if (isDone)
		{
			// Действие завершено, переклчить внимание на родительское действие
		}
	}
}