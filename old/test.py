
import sys

if sys.version < '3':
	print("version not 3")
	import codecs
	import stringTest
	def u(x):
		if type(x).__name__ == 'unicode':
			return x
		else:
			return codecs.unicode_escape_decode(x)[0]
else:
	print("version 3")
	import stringTest.cpython-34m as stringTest
	def u(x):
		return x

# test export of strings from python to c++
stringTest.testPrint()

# print individual strings from python in c++
expString = "test"
print('Py:string: '+ type(expString).__name__ +': '+ expString)
stringTest.printText(expString)

expString = u"test"
print('Py:unicode: '+ type(expString).__name__ +': '+expString)
stringTest.printText(expString)

expString = b"test"
print('Py:byte: '+ type(expString).__name__ +': '+expString)
stringTest.printText(expString)

descCStr = "c++ char"
descCWStr = "c++ wchar_t"
descCUnesc = "c++ unescaped char"

# test import of strings from c++ to python
a = u(stringTest.myStr())
b = u(stringTest.myWStr1())
c = u(stringTest.myUnescStr())

print(descCStr +': '+ type(a).__name__+': '+a)
print(descCWStr +': '+ type(b).__name__+': '+b)
print(descCUnesc +'1: '+ type(c).__name__)
print(descCUnesc +'2: '+ c)
print(descCUnesc +'3: '+ type(c).__name__+': '+c)



