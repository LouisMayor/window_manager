#pragma once

template <typename TModel, typename TView>
class Controller
{
public:
	virtual ~Controller() = default;
	virtual void Init(TModel& in_model, TView& in_view)
	{
		_model = &in_model;
		_view = &in_view;
	}

protected:
	TModel* _model = nullptr;
	TView* _view = nullptr;
};
