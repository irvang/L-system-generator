# L-system-generator.

Uses openFrameworks v. 0.9.8. 

Example of the program as binary files (applications):
  -For Mac : http://irvingangulo.com/assets/l-system-generator-examples/examples-mac-l-system-generator.zip

  -For Windows: http://irvingangulo.com/assets/l-system-generator-examples/exmples-windows-l-system-generator.zip


-In order to run: 

a) Download and install openFrameworks from this page : http://openframeworks.cc/download/ . 

b) Generate project, and use this folder as your source (no addons needed).

-To set new L-system:

a) On LSystem.cpp, line 5, set your starting axiom.

b) Set new rules below line 30 (see alphabet below). Each rule shold consist of a case, followed by a string and a break.

c) Change theta (angle of turn) on ofApp.cpp, line 18.

For more information about L-systems please see

http://algorithmicbotany.org/papers/abop/abop.pdf

or

https://en.wikipedia.org/wiki/L-system. 


====Alphabet used works as follows:

'f' or 'h': move forward and draw

'g': move backwards and draw

'F': move forward without drawing

'G': move backwards without drawing

'|': rotate 180 degrees

'-': turn left

'+': turn right

'u': rotate up

'd': rotate down

'l': roll left

'/': roll right

'[':push matrix

']': pop matrix
