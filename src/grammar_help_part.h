#ifndef GRAMMAR_HELP_PART_H
#define GRAMMAR_HELP_PART_H

#define HELP_SEE(name)	"Type `help " << name << "' for more details."

switch(command)
{
	case 0:
		std::cout << "Global help" << std::endl;
		std::cout << "\t\"target\"\tConfigure targets." << HELP_SEE("target") << std::endl;
		std::cout << "\t\"config\"\tSpecify global configuration options." << HELP_SEE("config") << std::endl;
		std::cout << "\t\"exit\"\tExit configuration and build makefile." << std::endl;
		break;
	case T_TARGET:
		break;
	case T_CONFIG:
		break;
}

#endif /* GRAMMAR_HELP_PART_H */

