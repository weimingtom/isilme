#ifndef ISILME_ACTION_TACTICS_H
#define ISILME_ACTION_TACTICS_H

#include "Definitions.h"
#include "Action.h"
#include "Strategy.h"

namespace action
{
	/// ����������� ���������� ��������
	class IsilmeExport Tactics : public IAction, public IStrategy
	{	
	public:
		Tactics();
		virtual ~Tactics();

		/// �������� ��������� �������
		virtual bool Update(float elapsedTime);

		/// �������������� ��������� �������
		virtual void Stop();

		/// ���������� ��������� ������������ ��������
		virtual action::ActionState GetState();

		/// @depricated
		virtual unsigned long GetMask();

		/// ��������� ������� �� ��������
		virtual bool IsActive();

		/// ������� ��������� ���������� ��������
		virtual bool	DoneCondition();

		/// ������� ������� �������
		virtual bool	FailCondition();

		///
		virtual void	OnThink(float elapsedTime);

		/// ����������� � ������ ������ ��������
		virtual void	OnStart();

		/// ����������� � ������ ���������� ��������
		virtual void	OnDone();

		/// �������� ���������� ��������� ��������
		virtual void	StartAction(ActionPtr action);

		virtual ActionPtr	GetParent();
	protected:
		virtual void	SetParent(ActionPtr parent);
		/// ���������� �� Behaviour ���������
		virtual void	OnStart(BehaviourPtr behaviour);
		BehaviourWPtr mBehaviour;
	private:
		action::ActionState mState;
		ActionWPtr mParent;
	};
};

#endif