// according to sources
// https://misspent.wordpress.com/2009/09/27/how-to-write-boost-python-converters/
// https://wiki.python.org/moin/boost.python/EmbeddingPython

#include <boost/python.hpp>

PY_THREE = true;
#if PY_VERSION < 0x03000000
	PY_THREE = false;
#endif

/** to-python convert to python version dependent string */
struct String_to_python_str{
	static PyObject* convert()
}
