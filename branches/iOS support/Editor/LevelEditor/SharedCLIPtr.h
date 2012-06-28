#pragma once

#include <boost/shared_ptr.hpp>

template <typename T>
class SharedCLIPtr
{
public:
	boost::shared_ptr<T> Value;

	SharedCLIPtr(boost::shared_ptr<T> value)
	{
		Value = value;
	}

	~SharedCLIPtr()
	{
		Value.reset();
	}
};