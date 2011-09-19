#ifndef MAKEFILE_OPTIONS_HPP
#define MAKEFILE_OPTIONS_HPP

namespace Makefile
{
	class Options
	{
	public:
		static Options& currentOptions();

		bool getDebug() const;
		void setDebug(bool debug);

		bool getVerbose() const;
		void setVerbose(bool verbose);
	private:
		Options();

		static Options* instance;

		bool debug;
		bool verbose;
	};
}

#endif /* MAKEFILE_OPTIONS_HPP */

