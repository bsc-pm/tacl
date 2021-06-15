/*
	This file is part of Task-Aware ACL and is licensed under the terms contained in the COPYING and COPYING.LESSER files.

	Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
*/

#ifndef STREAM_POOL_HPP
#define STREAM_POOL_HPP

#include <acl/acl.h>

#include <cassert>
#include <vector>

#include "TaskingModel.hpp"
#include "util/ErrorHandler.hpp"


namespace tacl {

//! Class that manages the TACL streams
class StreamPool {
private:
	//! Array of streams
	static std::vector<aclrtStream> _streams;

	//! Context of the streams
	static aclrtContext _context;

public:
	//! \brief Initialize the pool of streams
	//!
	//! \param nstreams The number of streams to create
	static inline void initialize(size_t nstreams)
	{
		assert(nstreams > 0);

		aclError eret = aclrtGetCurrentContext(&_context);
		if (eret != ACL_ERROR_NONE)
			ErrorHandler::fail("Failed in aclrtGetContext: ", eret);

		_streams.resize(nstreams);
		for (size_t s = 0; s < nstreams; ++s) {
			eret = aclrtCreateStream(&_streams[s]);
			if (eret != ACL_ERROR_NONE)
				ErrorHandler::fail("Failed in aclrtCreateStream: ", eret);
		}
	}

	//! \brief Finalize the pool of streams
	static inline void finalize()
	{
		for (size_t s = 0; s < _streams.size(); ++s) {
			aclError eret = aclrtDestroyStream(_streams[s]);
			if (eret != ACL_ERROR_NONE)
				ErrorHandler::fail("Failed in aclrtDestroyStream: ", eret);
		}
	}

	//! \brief Get stream within pool
	//!
	//! \param streamId The stream identifier within the pool
	static inline aclrtStream getStream(size_t streamId)
	{
		assert(streamId < _streams.size());

		aclError eret = aclrtSetCurrentContext(_context);
		if (eret != ACL_ERROR_NONE)
			ErrorHandler::fail("Failed in aclrtSetContext: ", eret);

		return _streams[streamId];
	}
};

} // namespace tacl

#endif // STREAM_POOL_HPP
