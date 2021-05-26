#pragma once

#include <unordered_map>
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

const auto cShortSymbol = '-';
void core_parser(int argc, const char *argv[]) {
	helper::Arg cmdInfo;

	for (int argIndex = 0; argIndex < argc; ++argIndex) {
		const auto cmd = argv[argIndex];
		if (!cmd) {
			std::cout << "ERROR! " << __LINE__ << " cmad is nullptr";
			continue;
		}

		if (cmd[0] == cShortSymbol) {
			cmdInfo.symbol = cmd[1];
		} else {
			cmdInfo.name = cmd;
		}

		const auto argType = helper::parser::argFromString.at(cmdInfo);
	}
}


}
