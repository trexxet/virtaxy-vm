mkdir -p bin
echo Cleaning...
make -sC common clean
make -sC assembler clean
make -sC machine clean
echo Building...
make -sC assembler
make -sC machine
echo Done!
