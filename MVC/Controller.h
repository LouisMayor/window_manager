#pragma once

template <typename TModel, typename TView>
class Controller
{
public:
	virtual ~Controller() = default;
	virtual void Init(TModel&, TView&) {}
};
