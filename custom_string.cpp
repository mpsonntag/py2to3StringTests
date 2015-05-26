// according to sources
// https://misspent.wordpress.com/2009/09/27/how-to-write-boost-python-converters/
// https://wiki.python.org/moin/boost.python/EmbeddingPython
// http://www.boost.org/doc/libs/1_56_0/libs/python/doc/v2/faq.html#custom_string

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/to_python_converter.hpp>

struct String_from_python_str {
	String_from_python_str() {
		boost::python::converter::registry::push_back(
			&convertible,
			&construct,
			boost::python::type_id<String>());
	}

    static void* convertible(PyObject* obj) {
		return
			(PyString_Check(obj) || PyUnicode_Check(obj)) 
			? obj
			: 0
			;
	}

	static void construct( PyObject* obj,
		boost::python::converter::rvalue_from_python_stage1_data* data) {
			namespace py = boost::python;
			if(PyString_Check(obj)) {
				const char* value = PyString_AsString(obj);
				MY_CHECK(value,translate("Received null string pointer from Python"));
				void* storage = ((py::converter::rvalue_from_python_storage<String>*)data)->storage.bytes;
				new (storage) String(value);
				data->convertible = storage;
			}
			else if(PyUnicode_Check(obj)) {
				py::handle<> utf8(py::allow_null(PyUnicode_AsUTF8String(obj)));
				MY_CHECK(utf8,translate("Could not convert Python unicode object to UTF8 string"));
				void* storage = ((py::converter::rvalue_from_python_storage<String>*)data)->storage.bytes;
				const char* utf8v = PyString_AsString(utf8.get());
				MY_CHECK(utf8v,translate("Received null string from utf8 string"));
				new(storage) String(utf8v);
				data->convertible = storage;
      		}
			else {
				error(translate("Unexpected type for string conversion"));
			}
		}
	};
}


