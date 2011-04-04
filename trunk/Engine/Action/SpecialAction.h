#ifndef ISILME_ACTION_SPECIALACTION_H
#define ISILME_ACTION_SPECIALACTION_H

#include "Definitions.h"
#include "Action.h"

namespace action
{
	/// ��������, ������� ����� ��������� ������ 
	/// ������� � ������������ ����� ���������
	template <class T>
	class SpecialAction : public Action
	{
	public:
		virtual ~SpecialAction() {}

		boost::shared_ptr<T>	GetBehaviour()
		{
			return boost::shared_dynamic_cast<T, Behaviour>(mBehaviour.lock());
		}
	};
};

#endif