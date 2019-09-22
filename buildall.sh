#!/bin/sh
qmake
make $*
mkdir build
mkdir build/plugins
if [ "$(uname)" == "Darwin" ]; then
        cp -r ./src/Interpolator/Interpolator.app ./build/
        LIB_EXT=dylib
else
        cp ./src/Interpolator/Interpolator ./build/Interpolator
        LIB_EXT=so
fi
cp ./src/CsvFilePlugin/libCsvFilePlugin.$LIB_EXT ./build/plugins/
cp ./src/CsvFilePluginSemiColon/libCsvFilePluginSemiColon.$LIB_EXT ./build/plugins/
cp ./src/PeaksChooser/libPeaksChooser.$LIB_EXT ./build/plugins/
cp ./src/PeaksTextFilePlugin/libPeaksTextFilePlugin.$LIB_EXT ./build/plugins/
cp ./src/SpaFilePlugin/libSpaFilePlugin.$LIB_EXT ./build/plugins/
cp ./src/TabSeparatedPlugin/libTabSeparatedPlugin.$LIB_EXT ./build/plugins/

echo 'Build completed. All built files are in build directory'
