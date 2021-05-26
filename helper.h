#pragma once

#include <map>
#include <string>
#include <functional>
#include <optional>
#include <iostream>

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


const auto argFromString =  std::map<Arg, ArgType>{
	  {{"help", 'h', helpDesription}, ArgType::Help}
	, {{"testing", 't', TestingDesription}, ArgType::Testing}
	, {{"functions", 'f', FunctionsDesription}, ArgType::Functions}
};

template <typename Func, typename ...Args>
struct ArgInfo
{
	std::optional<Arg> info;
	std::optional<ArgType> type;
	std::optional<SubArgType> subType;
	std::optional<Func> func;

	void run(Args&& ...args) {
		if (!type || !func) {
			std::cout << "ERROR";
			return;
		}

		func.value()(args...);
	}
};

}

namespace parser {


}
