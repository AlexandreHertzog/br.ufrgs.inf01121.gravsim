if [ ! -d "bin" ]; then
  mkdir bin
fi

cd bin
cmake ../src/
cd ..
