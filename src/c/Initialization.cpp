/*
	This file is part of Task-Aware ACL and is licensed under the terms contained in the COPYING and COPYING.LESSER files.

	Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
*/

#include <acl/acl.h>

#include "common/Environment.hpp"

using namespace tacl;

#pragma GCC visibility push(default)

extern "C" {

aclError
taclInit(const char *configPath)
{
	aclError eret = aclInit(configPath);
	if (eret == ACL_ERROR_NONE) {
		Environment::initialize();
	}
	return eret;
}

aclError
taclFinalize()
{
	Environment::finalize();
	return aclFinalize();
}

} // extern C

#pragma GCC visibility pop
