/*
	This file is part of Task-Aware ACL and is licensed under the terms contained in the COPYING and COPYING.LESSER files.

	Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
*/

#ifndef TACL_H
#define TACL_H

#include <acl/acl.h>
#include <acl/ops/acl_cblas.h>

#include <stddef.h>
#include <stdint.h>

#pragma GCC visibility push(default)

#ifdef __cplusplus
extern "C" {
#endif

typedef void *taclRequest;

static const taclRequest TACL_REQUEST_NULL = NULL;
static const size_t TACL_STREAMS_AUTO = 0;

aclError
taclInit(const char *configPath);

aclError
taclFinalize();

aclError
taclrtCreateStreams(size_t count);

aclError
taclrtDestroyStreams();

aclError
taclrtGetStream(aclrtStream *stream);

aclError
taclrtReturnStream(aclrtStream stream);

aclError
taclrtSynchronizeStreamAsync(aclrtStream stream);

aclError
taclrtMemcpyAsync(
	void *dst, size_t destMax, const void *src, size_t count,
	aclrtMemcpyKind kind, aclrtStream stream,
	taclRequest *request);

aclError
taclrtMemsetAsync(
	void *devPtr, size_t maxCount, int32_t value, size_t count,
	aclrtStream stream,
	taclRequest *request);

aclError
taclopExecute(
	const char *opType, int numInputs, const aclTensorDesc *const inputDesc[],
	const aclDataBuffer *const inputs[], int numOutputs,
	const aclTensorDesc *const outputDesc[], aclDataBuffer *const outputs[],
	const aclopAttr *attr, aclrtStream stream,
	taclRequest *request);

aclError
taclblasGemmEx(
	aclTransType transA, aclTransType transB, aclTransType transC,
	int m, int n, int k, const void *alpha, const void *matrixA,
	int lda, aclDataType dataTypeA, const void *matrixB, int ldb,
	aclDataType dataTypeB, const void *beta, void *matrixC, int ldc,
	aclDataType dataTypeC, aclComputeType type, aclrtStream stream,
	taclRequest *request);

aclError
taclWaitRequestAsync(taclRequest *request);

aclError
taclWaitallRequestsAsync(size_t count, taclRequest requests[]);

#ifdef __cplusplus
}
#endif

#pragma GCC visibility pop

#endif /* TACL_H */
