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
taclopExecute(
	const char *opType, int numInputs, const aclTensorDesc *const inputDesc[],
	const aclDataBuffer *const inputs[], int numOutputs,
	const aclTensorDesc *const outputDesc[], aclDataBuffer *const outputs[],
	const aclopAttr *attr, aclrtStream stream,
	taclRequest *requestPtr)
{
	aclError eret;
	eret = aclopExecute(opType, numInputs, inputDesc, inputs,
		numOutputs, outputDesc, outputs, attr, stream);
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
