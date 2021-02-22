#ifndef _DEBUG_APP
#define _DEBUG_APP

#include <iostream>
#include <sstream>

namespace hashcode_debug {

#ifdef _DEBUG

	enum class LEVEL
	{
		VERBOSE,
		INFO
	};

	inline void printBlankLines(const int n)
	{
		std::ostringstream ss;
		for (int i = 0; i < n; ++i)
		{
			ss << "\n";
		}

		std::cout << ss.str();
	}

	inline void dbgprint(std::ostringstream& msg)
	{
		std::cout
			<< "[DEBUG] "
			<< msg.str()
			<< "\n";
	}

	inline void dbgprint(std::ostringstream msg, LEVEL l)
	{
		if (l == LEVEL::INFO)
		{
			#if defined(_DEBUGINFO) || defined(_DEBUGVERBOSE)
			dbgprint(msg);
			#endif
		}
		else if (l == LEVEL::VERBOSE)
		{
			#if defined(_DEBUGVERBOSE)
			dbgprint(msg);
			#endif
		}
	}

	inline void errprint(std::ostringstream err)
	{
		std::cout
			<< "[ERROR] "
			<< err.str()
			<< "\n";
	}

#else

	inline void dbgprint(std::ostringstream msg) {}
	inline void errprint(std::ostringstream err) {}
	inline void dbgprint(std::ostringstream msg, LEVEL l) {}
	inline void printBlankLines(const int n) {}

#endif

}

#endif