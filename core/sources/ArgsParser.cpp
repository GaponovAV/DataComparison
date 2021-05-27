#include "../headers/ArgsParser.h"

namespace parser {

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

void subArgType(helper::parser::ArgType type, int argIndex, const char *argv[])
{
	if (type == helper::parser::ArgType::Invalid) {
		return;
	}

	
}

}

namespace helper::parser {

template<typename T>
std::shared_ptr<BaseFunction> BaseFunction::create(const DataSetContainer<T> &dataSet)
{
	return std::make_shared<BaseFunction>(dataSet);
}


helper::parser::FuncContainer helper::parser::BaseFunction::function()
{
	return m_function;
}

template<typename T>
helper::parser::BaseFunction::BaseFunction(const DataSetContainer<T> &data)
{
	m_function.emplace(ArgType::Functions, [&data]{
		data.calculateFDR();
	});
}
}
