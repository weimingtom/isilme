#ifndef ZOMBIELAND_ACTION_CONTROL_H
#define ZOMBIELAND_ACTION_CONTROL_H

#include "../Definitions.h"

namespace action
{
	/// ���������� ���������� ����������� ��������� � ����
	class Control : public Action
	{
	public:
		Control();
		virtual ~Control();

		virtual void OnStart();

		virtual void OnDone();

		virtual void OnUpdate(float elapsedTime);

		virtual void OnForceStop();

		virtual bool DoneCondition();
	protected:
	private:
		behaviour::CreaturePtr mCreature;
	};
};

#endif