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
		~TargetTool = default;

		void output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel = 0) const override;

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

	private:
		Tool& tool;

		bool debugMode {false};
		bool verboseMode {false};
		bool optimizationMode {false};
	};
}

#endif /* MAKEFILE_TARGETOOL_HPP */

