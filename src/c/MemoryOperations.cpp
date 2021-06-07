/*
	This file is part of Task-Aware ACL and is licensed under the terms contained in the COPYING and COPYING.LESSER files.

	Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
*/

#include <acl/acl.h>
#include <TACL.h>

#include "common/Environment.hpp"
#include "common/TaskingModel.hpp"
#include "common/util/ErrorHandler.hpp"

using namespace tacl;

#pragma GCC visibility push(default)

extern "C" {

aclError
taclrtMemcpyAsync(
	void *dst, size_t destMax, const void *src, size_t count,
	aclrtMemcpyKind kind, aclrtStream stream,
	taclRequest *requestPtr)
{
	aclError eret;
	eret = aclrtMemcpyAsync(dst, destMax, src, count, kind, stream);
	if (eret != ACL_ERROR_NONE)
		return eret;

	Request *request = RequestManager::generateRequest(stream, (requestPtr == nullptr));
	assert(request != nullptr);

	if (requestPtr != nullptr)
		*requestPtr = request;

	return ACL_ERROR_NONE;
}

aclError
taclrtMemsetAsync(
	void *devPtr, size_t maxCount, int32_t value, size_t count, aclrtStream stream,
	taclRequest *requestPtr)
{
	aclError eret;
	eret = aclrtMemsetAsync(devPtr, maxCount, value, count, stream);
	if (eret != ACL_ERROR_NONE)
		return eret;

	Request *request = RequestManager::generateRequest(stream, (requestPtr == nullptr));
	assert(request != nullptr);

	if (requestPtr != nullptr)
		*requestPtr = request;

	return ACL_ERROR_NONE;
}

} // extern C

#pragma GCC visibility pop
