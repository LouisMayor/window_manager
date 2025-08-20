#pragma once

#include <memory>
#include <type_traits>

#include "StorableCallback.h"

template<typename T>
concept is_ptr = requires
{
	std::is_pointer_v<T>;
};

template<typename T>
concept is_member_function_type = requires
{
	std::is_member_function_pointer_v<T>;
};

template<typename TOwnerPtr, typename TCallback>
requires
	is_ptr<TOwnerPtr> &&
	is_member_function_type<TCallback>
struct NonStaticCallbackData
{
	TOwnerPtr _owner = nullptr;
	TCallback _callback;
};

template<typename TOwnerPtr, typename TCallback>
requires
	is_ptr<TOwnerPtr> &&
	is_member_function_type<TCallback>
struct RawMemberMethod : IStorableCallback
{
	RawMemberMethod(TOwnerPtr in_owner, TCallback in_callback)
		: _data{ in_owner, in_callback }
	{}

	void Invoke() override
	{
		std::invoke(_data._callback, _data._owner);
	}

	NonStaticCallbackData<TOwnerPtr, TCallback> _data;
};

struct NonStaticCallbackContainer
{
	template<typename TOwnerPtr, typename TCallback>
	requires
		is_ptr<TOwnerPtr> &&
		is_member_function_type<TCallback>
	static NonStaticCallbackContainer sMake(TOwnerPtr in_owner, TCallback in_callback)
	{
		return NonStaticCallbackContainer{new RawMemberMethod<TOwnerPtr, TCallback>{ in_owner, in_callback }};
	}

	NonStaticCallbackContainer(IStorableCallback* in_callback)
	{
		_callback =  std::unique_ptr<IStorableCallback>{in_callback};
	}

	NonStaticCallbackContainer(const NonStaticCallbackContainer& other) {}

	NonStaticCallbackContainer(NonStaticCallbackContainer&& other) noexcept
	{
		_callback = std::move(other._callback);
	}

	NonStaticCallbackContainer& operator=(const NonStaticCallbackContainer& other)
	{
		if (this == &other)
		{
			return *this;
		}
		return *this;
	}

	NonStaticCallbackContainer& operator=(NonStaticCallbackContainer&& other) noexcept
	{
		return *this;
	}

	void Invoke() const
	{
		_callback->Invoke();
	}

private:

	// todo: move to shared base class
	std::unique_ptr<IStorableCallback> _callback = nullptr;
};
