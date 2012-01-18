#ifndef MAKEFILE_TARGETOOL_HPP
#define MAKEFILE_TARGETOOL_HPP

#include "Util/Output.hpp"
#include "Tool.hpp"

namespace Makefile
{
	class TargetTool : public Util::Output
	{
	public:
		explicit TargetTool(const std::string& name);
		~TargetTool() = default;

		Tool& getTool();
		unsigned short getToolId() const;

		const std::string& getName() const;

		bool isDebugMode() const;
		void setDebugMode(bool debugMode);

		bool isVerboseMode() const;
		void setVerboseMode(bool verboseMode);

		bool isOptimizationMode() const;
		void setOptimizationMode(bool optimizationMode);

		std::unordered_set<std::string>&& getAllFlags() const;

		void output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel = 0) const override;
		void help(std::ostream& stream, int command = 0) const override;

	private:
		Tool& tool;

		std::string name;

		bool debugMode {false};
		bool verboseMode {false};
		bool optimizationMode {false};
	};

	inline bool operator==(const std::shared_ptr<TargetTool> tool, const std::string& name)
	{
		return tool->getName() == name;
	}

}

#endif /* MAKEFILE_TARGETOOL_HPP */

