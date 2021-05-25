#pragma once

#include <vector>

template <typename T>
struct DataContainer : public std::vector<T>
{
	DataContainer(const size_t &size = 0) : std::vector<T>(size) {};
	DataContainer(const std::vector<T> &vector)
	    : std::vector<T> (vector.size()) {
		std::copy(vector.begin(), vector.end(), this->begin());
	};
	DataContainer(const DataContainer &dataContainer)
	    : std::vector<T>(dataContainer.size()) {
		std::copy(dataContainer.begin(), dataContainer.end(), this->begin());
	};

	const DataContainer &operator<<(const DataContainer &dataContainer) {
		const auto prevEndIt = std::back_inserter(this);
		const auto newSize = this->size() + dataContainer.size();
		this->resize(newSize);
		std::copy(dataContainer.begin(), dataContainer.end(), prevEndIt);
		return *this;
	};
	const DataContainer &operator<<(const std::vector<T> &vector) {
		auto currentVector = static_cast<std::vector<T>>(*this);
		auto prevEndIt = std::back_inserter(currentVector);
		const auto newSize = this->size() + vector.size();
		std::copy(vector.begin(), vector.end(), prevEndIt);
		*this = DataContainer(currentVector);
		return *this;
	};
	const DataContainer &operator<<(const T &number) {
		this->push_back(number);
		return *this;
	};
};
