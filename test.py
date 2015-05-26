from __future__ import unicode_literals

# custom cpp module
import stringTest

# test export of strings from python to c++
# stringTest.testPrint()


# print individual strings from python in c++
print('(py)...Test handing over strings from python to c++')
expString = "test"
print('\t(py)\tunspecified string: '+ type(expString).__name__ +': '+ expString)
stringTest.printText(expString)

expString = u"test"
print('\t(py)\tunicode: '+ type(expString).__name__ +': '+ expString)
stringTest.printText(expString)

# everything here works with both py2 and 3 BUT:
# decode is required, otherwise the string concatenation will crash in 
# python 3
expString = b"test"
print('\t(py)\tbyte: '+ type(expString).__name__ +': '+ expString.decode())
stringTest.printText(expString)



# test import of strings from c++ to python
print('(py)...Test handing over strings from c++ to python')
descCStr = "c++ string"
descCWStr = "c++ wstring"
descCChar = "c++ char"
descCWChar = "c++ wchar_t"

a = stringTest.myStr()
b = stringTest.myWStr()
c = stringTest.myChar()
d = stringTest.myWChar1()

print('\t'+ descCStr +',\tPyType:\t'+ type(a).__name__+':\t\t'+a)
print('\t'+ descCWStr +',\tPyType:\t'+ type(b).__name__+':\t'+b)
print('\t'+ descCChar +',\tPyType:\t'+ type(c).__name__+':\t\t'+c)
print('\t'+ descCWChar +',\tPyType:\t'+ type(d).__name__+':\t'+d)


