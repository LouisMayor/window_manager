#pragma once

struct IStorableCallback
{
	virtual ~IStorableCallback() = default;
	virtual void Invoke() = 0;
};