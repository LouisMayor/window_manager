#pragma once

#include <memory>
#include <type_traits>

#include "StorableCallback.h"

template<typename T>
concept is_member_function_type = requires
{
	std::is_member_function_pointer_v<T>;
};

template<typename T>
concept is_static_function_type = requires
{
	std::is_function_v<T>;
};

template<typename TCallback>
requires
	is_static_function_type<TCallback> ||
	is_member_function_type<TCallback>
struct StaticCallbackData
{
	TCallback _callback;
};

template<typename TCallback>
requires
	is_static_function_type<TCallback> || 
	is_member_function_type<TCallback>
struct RawStaticMethod : IStorableCallback
{
	RawStaticMethod(TCallback in_callback)
		: _data{ in_callback }
	{}

	void Invoke() override
	{
		std::invoke(_data._callback);
	}

	StaticCallbackData<TCallback> _data;
};


struct StaticCallbackContainerView
{
	void Invoke() const
	{
		_callback->Invoke();
	}

	// non-owning callback
	// todo: make it undeletable
	IStorableCallback* _callback = nullptr;
};

struct StaticCallbackContainer
{
	template<typename TCallback>
	requires
		is_static_function_type<TCallback> || 
		is_member_function_type<TCallback>
	static StaticCallbackContainer sMake(TCallback in_callback)
	{
		return StaticCallbackContainer(std::make_unique<RawStaticMethod<TCallback>>(in_callback));
	}

	StaticCallbackContainer(std::unique_ptr<IStorableCallback> in_callback)
	{
		_callback = std::move(in_callback);
	}

	StaticCallbackContainer(StaticCallbackContainer& other)
	{
		_callback = std::unique_ptr<IStorableCallback>(other.GetCallback());
	}

	StaticCallbackContainer(StaticCallbackContainer&& other) noexcept
	{
		_callback = std::move(other._callback);
	}

	StaticCallbackContainerView ToView() const
	{
		return StaticCallbackContainerView{_callback.get()};
	}

	StaticCallbackContainer& operator=(const StaticCallbackContainer& other)
	{
		if (this == &other)
		{
			return *this;
		}
		return *this;
	}

	StaticCallbackContainer& operator=([[maybe_unused]] StaticCallbackContainer&& other) noexcept
	{
		return *this;
	}

	void Invoke() const
	{
		_callback->Invoke();
	}

private:
	// todo: not the best design. considering it releases ownership, it could be a source of a memory leak
	[[nodiscard]] IStorableCallback* GetCallback() 
	{
		return _callback.release();
	}

	// todo: move to shared base class
	std::unique_ptr<IStorableCallback> _callback = nullptr;
};
