#ifndef GRAMMAR_HELP_PART_H
#define GRAMMAR_HELP_PART_H

#define HELP_SEE(name)	"Type `help " << name << "' for more details."

switch(command)
{
	case 0:
		std::cout << "Global help" << std::endl;
		std::cout << "\t\"target\"\tConfigure targets." << HELP_SEE("target") << std::endl;
		std::cout << "\t\"option\"\tSet global option." << HELP_SEE("option") << std::endl;
		std::cout << "\t\"exit\"\tExit configuration and build makefile." << std::endl;
		break;
	case T_OPTION:
		break;
	case T_TARGET:
		break;
}

#endif /* GRAMMAR_HELP_PART_H */

