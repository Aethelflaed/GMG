#ifndef MAKEFILE_BUILDER_HPP
#define MAKEFILE_BUILDER_HPP

#include <stdexcept>
#include <string>
#include <unordered_map>
#include "Options.hpp"
#include "Target.hpp"

namespace Makefile
{
	class Builder
	{
	public:
		typedef std::unordered_map<std::string, Target> targets_map;

		Builder();
		~Builder() = default;

		const Options& getOptions() const;
		Options& getOptions();

		const targets_map& getTargets() const;
		Target& addTarget(const std::string& name) throw (std::invalid_argument);
		Target& getTarget(const std::string& name) throw (std::out_of_range);
		void removeTarget(const std::string& name) throw (std::out_of_range);

	private:
		targets_map targets;

		Options options;
	};
}

#endif /* MAKEFILE_BUILDER_HPP */

