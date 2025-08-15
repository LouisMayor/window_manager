#pragma once

#include <type_traits>

#include "Controller.h"
#include "Model.h"
#include "View.h"

template<typename T, typename M, typename V>
concept is_controller_type = requires
{
	std::is_base_of_v<Controller<M, V>, T>;
};

template<typename T, typename C>
concept is_view_type = requires
{
	std::is_base_of_v<View<C>, T>;
};

template<typename T>
concept is_model_type = requires
{
	std::is_base_of_v<Model, T>;
};

template <typename TController, typename TView, typename TModel>
requires
	is_controller_type<TController, TModel, TView> &&
	is_view_type<TView, TController> &&
	is_model_type<TModel>
class MVC
{
public:
	virtual void Init()
	{
		_controller.Init(_model, _view);
		_view.Init(_controller);
	}

	virtual ~MVC() = default;

protected:
	TController _controller;
	TView _view;
	TModel _model;
};
