#ifndef ACTION_MOVETO_H
#define ACTION_MOVETO_H

#include "../include/Definitions.h"

namespace action
{
	/// ��������� � ����
	class MoveTo : public Action
	{
	public:
		MoveTo();
		virtual ~MoveTo();

		/// ���������� ���� - ������
		void	SetTarget(EntityPtr	entity);

		/// ���������� ���� - �����
		void	SetTarget(Vector2 point);

		virtual void	OnStart();
		virtual void	OnUpdate(float elapsedTime);
		virtual void	OnDone();
		virtual void	OnForceStop();
	private:
		EntityPtr	mEntityTarget;
		Vector2		mPointTarget;

		behaviour::CreaturePtr	mCreature;
	};
};

#endif