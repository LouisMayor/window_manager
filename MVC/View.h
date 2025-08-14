#pragma once

template <typename TController>
class View
{
public:
	virtual ~View() = default;
	virtual void Init(TController&) {}
};
