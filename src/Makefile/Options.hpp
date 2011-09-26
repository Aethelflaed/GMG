#ifndef MAKEFILE_OPTIONS_HPP
#define MAKEFILE_OPTIONS_HPP

#include <ostream>

namespace Makefile
{
	class Options
	{
	public:
		Options();
		~Options() = default;

		bool getDebug() const;
		void setDebug(bool debug);

		bool getVerbose() const;
		void setVerbose(bool verbose);

		friend std::ostream& operator<< (std::ostream& stream, Options& options)
		{
			stream << "Options :" << std::endl;
			stream << " - debug   : " << options.getDebug() << std::endl;
			stream << " - verbose : " << options.getVerbose() << std::endl;
			return stream;
		}

	private:
		bool debug;
		bool verbose;
	};
}

#endif /* MAKEFILE_OPTIONS_HPP */

