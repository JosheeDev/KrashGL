echo "Cleaning everything..."

# Engine
make -f "Makefile.engine.linux.mak" clean
if [ $? -ne 0 ]; then
    echo "Error: $?"
    exit 1
fi

# Testbed
make -f "Makefile.testbed.linux.mak" clean
if [ $? -ne 0 ]; then
    echo "Error: $?"
    exit 1
fi

# Tests
make -f "Makefile.tests.linux.mak" clean
if [ $? -ne 0 ]; then
    echo "Error: $?"
    exit 1
fi

echo "All assemblies cleaned successfully."