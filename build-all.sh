set echo on

echo "Building everything..."

echo "Adding doxygen..."
# Run the header script
bash "$(dirname "$0")/rename.sh"
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]; then
    echo "Error: $ERRORLEVEL"
    exit $ERRORLEVEL
fi

# pushd engine
# source build.sh
# popd

make -f Makefile.engine.linux.mak all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

# pushd testbed
# source build.sh
# popd

make -f Makefile.testbed.linux.mak all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

# pushd tests
# source build.sh
# popd

make -f Makefile.tests.linux.mak all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "All assemblies built successfully."