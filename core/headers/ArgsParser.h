#pragma once

#include "../../lib/headers/DataSetContainer.h"

#include <unordered_map>
#include <string>
#include <functional>
#include <optional>
#include <iostream>
#include <tuple>
#include <memory>

namespace helper {

struct Arg {
	std::string name;
	char symbol;
	std::string description;
};

const std::string helpDesription;
const std::string TestingDesription;
const std::string FunctionsDesription;

}
namespace std {

template <> struct hash<helper::Arg>
{
	size_t operator()(const helper::Arg &arg) const
	{
		return std::hash<std::string>{}(arg.name);
	}
};

bool operator==(const helper::Arg &second, const helper::Arg &first) {
	return second.name == first.name || second.symbol == first.symbol;
};

}

namespace helper::parser {

enum class ArgType
{
	Invalid = -1,
	Help,
	Testing,
	Functions,
};

enum class SubArgType
{
	Invalid = -1,
	ResultFile,
	InputFile,
	Function1
};


const auto argFromString =  std::unordered_map<Arg, ArgType> {
	  {{"help", 'h', helpDesription}, ArgType::Help}
	, {{"testing", 't', TestingDesription}, ArgType::Testing}
	, {{"functions", 'f', FunctionsDesription}, ArgType::Functions}
};

struct ArgInfo
{
	std::optional<Arg> info;
	std::optional<ArgType> type;
	std::optional<SubArgType> subType;

	template <typename Func, typename ...Args>
	void run(Func &&func, Args&& ...args) {
		if (!type || !func) {
			std::cout << "ERROR";
			return;
		}

		func.value()(args...);
	}
};

using FuncContainer = std::unordered_map<ArgType, std::function<void()>>;

class BaseFunction
{
public:
	template<typename T>
	static std::shared_ptr<BaseFunction> create(const DataSetContainer<T> &dataSet);

	FuncContainer function();
private:
	template<typename T>
	BaseFunction(const DataSetContainer<T> &dataSet);

	FuncContainer m_function;
};

}

namespace parser {

const auto cShortSymbol = '-';
void core_parser(int argc, const char *argv[]);
void subArgType(helper::parser::ArgType type, int argIndex, const char *argv[]);


}
