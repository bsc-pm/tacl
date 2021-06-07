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
taclblasGemmEx(
	aclTransType transA, aclTransType transB, aclTransType transC,
	int m, int n, int k, const void *alpha, const void *matrixA,
	int lda, aclDataType dataTypeA, const void *matrixB, int ldb,
	aclDataType dataTypeB, const void *beta, void *matrixC, int ldc,
	aclDataType dataTypeC, aclComputeType type, aclrtStream stream,
	taclRequest *requestPtr)
{
	aclError eret;
	eret = aclblasGemmEx(transA, transB, transC,
		m, n, k, alpha, matrixA, lda, dataTypeA,
		matrixB, ldb, dataTypeB, beta, matrixC,
		ldc, dataTypeC, type, stream);
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
