mkdir -p bin
echo Cleaning...
make -sC common clean
make -sC assembler clean
make -sC machine clean
echo Building Assembler...
make -sC assembler
echo Building Machine...
make -sC machine
echo Done!
