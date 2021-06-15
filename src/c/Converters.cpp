/*
	This file is part of Task-Aware ACL and is licensed under the terms contained in the COPYING and COPYING.LESSER files.

	Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
*/

#include <acl/acl.h>
#include <TACL.h>

#include <cassert>

#pragma GCC visibility push(default)

extern "C" {

aclError
taclDoubleToFloat16Buffer(aclFloat16 *dst, const double *src, size_t count)
{
	if (count == 0)
		return ACL_ERROR_NONE;

	assert(dst != NULL);
	assert(src != NULL);

	for (size_t e = 0; e < count; ++e) {
		dst[e] = aclFloatToFloat16((float) src[e]);
	}

	return ACL_ERROR_NONE;
}

aclError
taclFloatToFloat16Buffer(aclFloat16 *dst, const float *src, size_t count)
{
	if (count == 0)
		return ACL_ERROR_NONE;

	assert(dst != NULL);
	assert(src != NULL);

	for (size_t e = 0; e < count; ++e) {
		dst[e] = aclFloatToFloat16(src[e]);
	}

	return ACL_ERROR_NONE;
}

aclError
taclFloat16ToDoubleBuffer(double *dst, const aclFloat16 *src, size_t count)
{
	if (count == 0)
		return ACL_ERROR_NONE;

	assert(dst != NULL);
	assert(src != NULL);

	for (size_t e = 0; e < count; ++e) {
		dst[e] = (double) aclFloat16ToFloat(src[e]);
	}

	return ACL_ERROR_NONE;
}

aclError
taclFloat16ToFloatBuffer(float *dst, const aclFloat16 *src, size_t count)
{
	if (count == 0)
		return ACL_ERROR_NONE;

	assert(dst != NULL);
	assert(src != NULL);

	for (size_t e = 0; e < count; ++e) {
		dst[e] = aclFloat16ToFloat(src[e]);
	}

	return ACL_ERROR_NONE;
}

} // extern C

#pragma GCC visibility pop
