/*
	This file is part of Task-Aware ACL and is licensed under the terms contained in the COPYING and COPYING.LESSER files.

	Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
*/

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "Allocator.hpp"
#include "TaskingModel.hpp"
#include "RequestManager.hpp"
#include "StreamPool.hpp"


namespace tacl {

//! Class that represents the environment
class Environment {
private:
	//! The handle to the polling instance that periodically checks
	//! the completion of the TACL requests and events
	static TaskingModel::polling_handle_t _pollingHandle;

	//! Determine the polling frequency when the TACL polling is
	//! implemented with tasks that are paused periodically. That is
	//! the frequency in time (microseconds) at which the in-flight
	//! TACL requests and events are checked in TACL. This environment
	//! variable is called TACL_POLLING_FREQUENCY and the default value
	//! is 500 microseconds
	static EnvironmentVariable<uint64_t> _pollingFrequency;

public:
	Environment() = delete;
	Environment(const Environment &) = delete;
	const Environment& operator= (const Environment &) = delete;

	//! \brief Initialize the environment of TACL
	//!
	//! This function should be called after a successful call to
	//! the original aclInit function
	static void initialize()
	{
		TaskingModel::initialize();

		Allocator<Request>::initialize();

		StreamPool::initialize(TaskingModel::getNumCPUs());

		assert(!_pollingHandle);
		_pollingHandle = TaskingModel::registerPolling("TACL", Environment::polling, nullptr, _pollingFrequency);
	}

	//! \brief Finalize the environment of TACL
	//!
	//! This function should be called before the call to the
	//! original aclFinalize function. After that call, the TACL
	//! library cannot call any ACL function
	static void finalize()
	{
		TaskingModel::unregisterPolling(_pollingHandle);

		StreamPool::finalize();

		Allocator<Request>::finalize();
	}

private:
	//! \brief Polling function that checks the requests and events
	//!
	//! This function is periodically called by the tasking runtime
	//! system and should check for the TACL requests and events
	//!
	//! \param args An opaque pointer to the arguments
	static void polling(void *)
	{
		RequestManager::checkRequests();
	}
};

} // namespace tacl

#endif // ENVIRONMENT_HPP
