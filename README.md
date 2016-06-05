# Hue
Home automation applications to support the complete customization of Philips Hue

## Compiling
Currently supported is Windows and Linux

### Windows
Use the Visual Studio solution and compile everything. Ensure the correct configuration is set, and that's it

### Linux
Need to ensure that libcurl and JsonCpp are both compiled and available. Ensure that both are compiled and installed with the following commands
	
	./configure
	make
	make install