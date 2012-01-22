GMG : GMG Makefile Generator
============================

A makefile generator for developer needs, permitting to configure multiple tools (even of the same type), add multiple target, support multiple target platform (cross compiling).

### Requirements

* GCC 4.7 or another compiler supporting C++11 (including non-static data member initialization)
* The GNU GCC set to run the Makefile generated

### Current status

The project is currently under active development, and not all features are implemented.

Functional features includes:

* Working lex/yacc parser
* Customization of tools and default settings to enable fast-use
* Current configuration is saved in a file

Features under development:

* Help command, which is updated all the time
* Makefile generation

Next features to be developed:

* Take control over terminal concerning character input

