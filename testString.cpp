//Code mixture from sources
//http://en.wikibooks.org/wiki/Python_Programming/Extending_with_C%2B%2B
//http://stackoverflow.com/questions/18995063/convert-const-wchar-t-to-python-string-in-boost-python

#include <iostream>
#include <string>
#include <boost/function_types/parameter_types.hpp>
#include <boost/python.hpp>

using namespace std;

/// @brief ResultConverterGenerator used to transform wchar_t to PyObject.
struct wchar_result_converter
{
	template <class T> struct apply
	{
		struct type
		{
			/// @brief Convert wchar_t to PyObject.
			PyObject* operator()(const wchar_t* str) const
			{
				// Using the Python/C API may be slighly cleaner.
				return PyUnicode_FromWideChar(str, wcslen(str));

				// Alternatively, Boost.Python's object type can be used.  While
				// Boost.Python does not know how to convert wchar_t to an object,
				// it does know how to convert std::wstring, so construct
				// a temporary to help in the conversion.
				//   return boost::python::incref(
				//     boost::python::object(std::wstring(str)).ptr());
			}

			/// @brief Used for documentation.
			const PyTypeObject* get_pytype() const { return 0; }
    	}; // struct type
	};   // struct apply
};

/// @brief Modify the return type of a function using supplied CallPolicies.
template <typename ReturnType, typename Fn, typename Policy>
boost::python::object return_as(Fn fn, const Policy& policy)
{
  	// Build MPL type representing signature of function, injecting the
  	// explicitly provided return type.
	typedef typename boost::mpl::push_front<
		typename boost::function_types::parameter_types<Fn>::type,
			ReturnType
		>::type signature_type;

	return boost::python::make_function(fn, policy, signature_type());
}

/// @brief Modify the return type of a function using default_call_policies.
template <typename ReturnType, typename Fn>
boost::python::object return_as(Fn fn)
{
	return return_as<ReturnType>(fn, boost::python::default_call_policies());
}

// Test char from c++ -> python functions
const char* myChar() { return "test string"; }
const wchar_t* myWChar() { return L"test wide string ä"; }

// Test string from c++ -> python functions
const std::string myStr() { return "test string"; }
const std::wstring myWStr() { return L"test wide string ä"; }

// Test print in c++ from python
void testPrint() { cout << "(C++)\tI called from python and printed in c++!" << endl << endl; }

// Test text from python -> c++ functions
void testPrintText(const std::string printString) { cout << "\t(C++)\tstring: " << printString << endl << endl; }
void testPrintWText(const std::wstring printString) { wcout << "\t(C++)\twstring: " << printString << endl << endl; }

BOOST_PYTHON_MODULE(stringTest)
{
	namespace python = boost::python;

	//Expose test print in c++ from python
	python::def("testPrint", testPrint);
	
	//Expose overloaded print in c++ from python function
	python::def("printText", testPrintWText);	
	python::def("printText", testPrintText);

	// Expose non-wide test char support.
	python::def("myChar", myChar);

	// Expose wide char support by:
	// - providing a policy to convert the return value.
	// - manipulating the return type.
	python::def("myWChar1", &myWChar,
              python::return_value_policy<wchar_result_converter>());
	python::def("myWChar2", return_as<std::wstring>(&myWChar));

	//Expose non-wide string support
	python::def("myStr", myStr);
	//Expose wide string support
	python::def("myWStr", myWStr);
}


