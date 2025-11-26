#!/bin/bash
set -e
mkdir -p build/finlite
pushd build
pushd finlite

cmake ../.. --fresh 
cmake --build . --config Debug --verbose

if [[ "$OSTYPE" == "msys"* ]]; then
./Debug/finlite 
else
./finlite
fi

popd
popd


exit
