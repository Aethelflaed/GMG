#ifndef MAKEFILE_GENERATOR_HPP
#define MAKEFILE_GENERATOR_HPP

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <memory>

#include "define.hpp"

#include "Config.hpp"

namespace Makefile
{
	class Generator
	{
	public:
		typedef std::shared_ptr<Target> target_type;
		typedef std::unordered_map<std::string, target_type> targets_map;


		Generator();
		~Generator() = default;

		void generate();
		void save();

		const targets_map& getTargets() const;
		Target& getTarget(const std::string& name) throw (std::out_of_range);
		target_type getTargetPointer(const std::string& name) throw (std::out_of_range);
		Target& addTarget(const std::string& name) throw (std::invalid_argument);
		void removeTarget(const std::string& name) throw (std::out_of_range);

		Config& getConfig();
	private:
		targets_map targets;
		Config config;
	};
}

#endif /* MAKEFILE_GENERATOR_HPP */

