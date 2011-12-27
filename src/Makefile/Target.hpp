#ifndef MAKEFILE_TARGET_HPP
#define MAKEFILE_TARGET_HPP

#include <ostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>
#include <memory>

#include "Util/Output.hpp"

#include "define.hpp"
#include "Config.hpp"
#include "Generator.hpp"
#include "Tool.hpp"

namespace Makefile
{
	enum class TargetType : unsigned short int
	{
		/* Don't change ordering, to enable values count */
		Application = 0,
		Library,
		UnitTest,

		/* Keep that value in the end */
		_trailing
	};

	class Target : public Util::Output
	{
	public:
		typedef std::weak_ptr<Target> dependency_type;
		typedef std::vector<dependency_type> dependencies_vector;

		Target(Generator& generator, const std::string& name);
		~Target() = default;

		void clean();

		void setName(const std::string& name);
		const std::string& getName() const;

		void setVersion(const std::string& version);
		const std::string& getVersion() const;

		void addModule(const std::string& module);
		void removeModule(const std::string& module);
		const std::unordered_set<std::string>& getModules() const;

		void setType(TargetType type);
		TargetType getType() const;

		void setConfig(const Config& config);
		Config& getConfig();
		const Config& getConfig() const;

		Tool& addTool(const std::string& name);
		void removeTool(const std::string& name);
		Tool& getTool(const std::string& name);

		void addDependency(const std::string& name);
		void removeDependency(const std::string& name);
		const dependencies_vector& getDependencies() const;

		void output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel = 0) const override;

		friend std::ostream& operator<< (std::ostream& stream, Target& target)
		{
			target.list(stream);
			return stream;
		}

	private:
		std::string name;
		std::string version {"1.0"};
		std::unordered_set<std::string> modules {};

		Generator& generator;
		TargetType type {TargetType::Application};
		Config config;

		std::unordered_map<std::string, Tool> tools {};
		dependencies_vector dependencies {};
	};
}

#endif /* MAKEFILE_TARGET_HPP */

