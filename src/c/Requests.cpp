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
taclWaitRequestAsync(taclRequest *request)
{
	assert(request != nullptr);

	if (*request != TACL_REQUEST_NULL)
		RequestManager::processRequest((Request *) *request);

	*request = TACL_REQUEST_NULL;

	return ACL_ERROR_NONE;
}

aclError
taclWaitallRequestsAsync(size_t count, taclRequest requests[])
{
	if (count == 0)
		return ACL_ERROR_NONE;

	assert(requests != nullptr);

	RequestManager::processRequests(count, (Request * const *) requests);

	for (size_t r = 0; r < count; ++r) {
		requests[r] = TACL_REQUEST_NULL;
	}

	return ACL_ERROR_NONE;
}

} // extern C

#pragma GCC visibility pop
