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

To compile the software you need to run qmake first. Make sure to install the dependent Qt add-ons such as QtCharts.
GSL dependency is no longer needed as I have coded a regression algorithm from scratch. It could still come back in the future if more complex features will be added.

For linux users, you simply run:

`./buildall.sh`

You'll find the compiled files in the `build` folder.
Or you can do it the standard way:

`qmake`

`make`

And then copy all the libraries in a folder named `./plugins` relative to the main program directory.

For the expression evaluation to work, you need to have a working python distribution installed globally with GTC package installed ( ~~pip install GTC~~ ) or (included with Windows release) a local python distribution placed in a folder named 'python-3.7.2.amd64', with GTC package installed, placed in the same path as the executable is.

Steps:
- **$** *qmake*
- **$** *make*

**License**

This work is licensed under GNU GPLv3 license. See LICENSE file for more info.
