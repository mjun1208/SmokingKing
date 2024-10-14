#include "DXUT.h"
#include "cThreadPoolManager.h"


cThreadPoolManager::cThreadPoolManager() 
	: stop_all(false) 
{
	//Init();
}


cThreadPoolManager::~cThreadPoolManager()
{
	stop_all = true;
	cv_job_q_.notify_all();

	for (auto& t : worker_threads_) {
		t.join();
	}
}

void cThreadPoolManager::Init()
{
	num_threads_ = thread::hardware_concurrency() * 2 + 1;
	worker_threads_.reserve(num_threads_);
	for (size_t i = 0; i < num_threads_; ++i) {
		worker_threads_.emplace_back([this]() { this->WorkerThread(); });
		DEBUG_LOG(to_string(i + 1) << "번 쓰레드 할당완료");
	}

	DEBUG_LOG("하드웨어 컨텍스트 수 : " << to_string(thread::hardware_concurrency()) << "개");
	DEBUG_LOG("총 할당된 쓰레드 개수 : " << to_string(num_threads_) << "개");
}

void cThreadPoolManager::WorkerThread()
{
	while (true) {
		std::unique_lock<std::mutex> lock(m_job_q_);
		cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all; });
		if (stop_all && this->jobs_.empty()) {
			return;
		}

		// 맨 앞의 job 을 뺀다.
		std::function<void()> job = std::move(jobs_.front());
		jobs_.pop();
		lock.unlock();

		// 해당 job 을 수행한다 :)
		job();
	}
}