#ifndef APPLICATION_RUNNER_HPP
#define APPLICATION_RUNNER_HPP

#include <iosfwd>

int runApplication(int argc, char *argv[], std::istream &input,
                   std::ostream &output, std::ostream &errors);

#endif