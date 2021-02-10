#pragma once
#include <atomic>

template<typename Type>
class CDummyPointer {
	using reference = Type&;
	using pointer = Type*;
public:
	CDummyPointer() : pointer_(nullptr), counter_(nullptr) {}
	CDummyPointer(const CDummyPointer& copy) : CDummyPointer(copy.pointer_) {
		counter_ = copy.counter_;
		++*counter_;
	}
	CDummyPointer(CDummyPointer&& move) noexcept
		: pointer_(std::move(move.pointer_)), counter_(std::move(move.counter_))
	{}
	explicit CDummyPointer(pointer pointer)
		: pointer_(pointer), counter_(new std::atomic_uint(1u)) {}

	CDummyPointer& operator=(const CDummyPointer& copy) {
		if (pointer_ != copy.pointer_) {
			TryToDelete();
			counter_ = copy.counter_;
			pointer_ = copy.pointer_;
			++*counter_;
		}
		return *this;
	}

	CDummyPointer& operator=(CDummyPointer&& move) noexcept {
		pointer_ = std::move(move.pointer_);
		counter_ = std::move(move.counter_);
		move.pointer_ = nullptr;
		move.counter_ = nullptr;
		return *this;
	}

	~CDummyPointer() {
		TryToDelete();
	}

	[[nodiscard]] pointer GetPointer() const {
		return pointer_;
	}

	[[nodiscard]] unsigned GetCount() const {
		return counter_ == nullptr ? 0u : counter_->load();
	}

	[[nodiscard]] bool IsUnique() const {
		return counter_ == nullptr ? false : 1u == counter_->load();
	}

	reference operator*() const {
		return *pointer_;
	}

	pointer operator->() const {
		return pointer_;
	}

private:
	pointer pointer_;
	std::atomic_uint* counter_;

	bool TryToDelete() {
		if (nullptr != counter_ && 0u == --*counter_) {
			delete counter_;
			counter_ = nullptr;
			// That's legal stuff
			//delete pointer_;
			//pointer_ = nullptr;
			return true;
		}
		return false;
	}
};
