/*
	This file is part of Task-Aware ACL and is licensed under the terms contained in the COPYING and COPYING.LESSER files.

	Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
*/

#include <acl/acl.h>
#include <TACL.h>

#include "common/StreamPool.hpp"
#include "common/Environment.hpp"
#include "common/TaskingModel.hpp"
#include "common/util/ErrorHandler.hpp"

using namespace tacl;

#pragma GCC visibility push(default)

extern "C" {

aclError
taclrtCreateStreams(size_t count)
{
	if (count == TACL_STREAMS_AUTO)
		count = TaskingModel::getNumCPUs();
	assert(count > 0);

	StreamPool::initialize(count);

	return ACL_ERROR_NONE;
}

aclError
taclrtDestroyStreams()
{
	StreamPool::finalize();

	return ACL_ERROR_NONE;
}

aclError
taclrtGetStream(aclrtStream *stream)
{
	assert(stream != nullptr);

	*stream = StreamPool::getStream(TaskingModel::getCurrentCPU());

	return ACL_ERROR_NONE;
}

aclError
taclrtReturnStream(aclrtStream)
{
	return ACL_ERROR_NONE;
}

aclError
taclrtSynchronizeStreamAsync(aclrtStream stream)
{
	RequestManager::generateRequest(stream, true);

	return ACL_ERROR_NONE;
}

} // extern C

#pragma GCC visibility pop
