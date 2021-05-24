#pragma once

#include <vector>

template <typename T, typename Alloc = std::allocator<T>>
struct DataContainer : public std::vector<T, Alloc>
{
	DataContainer(const size_t &size = 0) : std::vector<T, Alloc>(size) {};
	DataContainer(const std::vector<T, Alloc> &vector)
	    : std::vector<T, Alloc> (vector.size()) {
		std::copy(vector.begin(), vector.end(), this->begin());
	};
	DataContainer(const DataContainer &dataContainer)
	    : std::vector<T, Alloc>(dataContainer.size()) {
		std::copy(dataContainer.begin(), dataContainer.end(), this->begin());
	};

	const DataContainer &operator<<(const DataContainer &dataContainer) {
		const auto prevEndIt = this->end();
		const auto newSize = this->size() + dataContainer.size();
		this->resize(newSize);
		std::copy(dataContainer.begin(), dataContainer.end(), prevEndIt);
		return *this;
	};
	const DataContainer &operator<<(const std::vector<T, Alloc> &vector) {
		this << DataContainer(vector);
		return *this;
	};
	const DataContainer &operator<<(const T &number) {
		this->push_back(number);
		return *this;
	};
};
