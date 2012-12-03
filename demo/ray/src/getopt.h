#ifndef RAY_GETOPT_H_
#define RAY_GETOPT_H_

#ifdef _WIN32
extern int getopt(int argc, char **argv, char *optstring);
#else
extern int getopt(int argc, char* const* argv, char *optstring);
#endif

#endif
