#pragma once

template <typename TController>
class View
{
public:
	virtual ~View() = default;
	virtual void Init(TController& in_controller)
	{
		_controller = &in_controller;
	}

protected:
	TController* _controller = nullptr;
};
