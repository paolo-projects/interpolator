# Interpolator
This is a software made to import X,Y data from different types of files, into a table, displaying a plot of the data you imported and with the ability to interpolate data against linear or polynomial curves.
It is modular, so support for a new file type can be added by including a plugin in the plugins folder.

**Main features:**
* Import comma separated CSV, semi-colon separated CSV, Peaks text file, SPA file through included plugins
* Plot loaded data
* Regression up to 4th order polynomial
* Plot interpolated curve vs loaded data
* Plot residuals
* Evaluate numerical expression with uncertainty propagation through Python and GTC package.
* Find peaks in a spectrum plot

**To-do:**
* *(DONE)* Support multiple locales (decimal separator)
* *(DONE)* Drop GSL dependency
* *(Work in progress...)* Support plugins for data manipulation and visualization

**Compile, Build**

To run the software you first need to compile it.
Virtually it can be compiled on any operating system, including Windows, Linux, Mac. I only tested it on Windows and Linux succesfully, I don't know if it works on mac but I think it does.
To compile it you need Qt and qmake. You also need to compile individually each plugin (they are in the subfolders of the project directory) and copy the compiled library in a folder named "plugins" in the same directory as the main executable.

**Dependencies**

~~To compile the software you need to run qmake first. Make sure to install the dependent Qt add-ons such as QtCharts.
You also need GSL library (GNU Scientific Library). On linux you will probably find built packages in your package manager (e.g. sudo apt install libgslX libgslcblas0 -- X is the version number, remember to update dependencies to the right version/name in .pro file). On windows you need to search for a built GSL package or build it yourself and change the path in the .pro file.~~
GSL dependency is no longer needed as I have coded an estimator from scratch. It could still come back in the future if more complex features will be added.

For the expression evaluation to work, you need to have a working python distribution placed in a folder named 'python-3.7.2.amd64', with GTC package installed, placed in the same path as the executable is. Made this choice to make distribution simple, but I plan to add support for a system-wide python distribution in the future *(you may do this yourself if you change a few lines in the code)*

Steps:
- **$** *qmake*
- **$** *make*

**License**

This work is licensed under GNU GPLv3 license. See LICENSE file for more info.
