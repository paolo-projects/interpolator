!/bin/sh
qmake
make
mkdir build
mkdir build/plugins
cp ./src/Interpolator/Interpolator ./build/Interpolator
cp ./src/CsvFilePlugin/libCsvFilePlugin.so ./build/plugins/libCsvFilePlugin.so
cp ./src/CsvFilePluginSemiColon/libCsvFilePluginSemiColon.so ./build/plugins/libCsvFilePluginSemiColon.so
cp ./src/PeaksChooser/libPeaksChooser.so ./build/plugins/libPeaksChooser.so
cp ./src/PeaksTextFilePlugin/libPeaksTextFilePlugin.so ./build/plugins/libPeaksTextFilePlugin.so
cp ./src/SpaFilePlugin/libSpaFilePlugin.so ./build/plugins/libSpaFilePlugin.so
cp ./src/TabSeparatedPlugin/libTabSeparatedPlugin.so ./build/plugins/libTabSeparatedPlugin.so

echo 'Build completed. All built files are in build directory'