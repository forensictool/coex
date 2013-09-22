
echo ">>> build coex";
chmod +x build_coex.sh
./build_coex.sh

echo ">>> clone or pull 'gpo-testdata.git'";
cd ../../
if [ ! -d "gpo-testdata.git" ]; then
  git clone git@git.keva.su:gpo-testdata.git gpo-testdata.git
else
  cd gpo-testdata.git
  # git checkout .
  git pull
  cd ..
fi

echo ">>> check folder gpo-tests";

if [ ! -d "gpo-testdata.git" ]; then
  echo "folder 'gpo-testdata.git' - not found"
  exit
fi

echo ">>> clean 'gpo-tests'";
if [ ! -d "gpo-tests" ]; then
  mkdir "gpo-tests";
else
  rm -rf "gpo-tests";
  mkdir "gpo-tests";
fi

echo ">>> check folder gpo-tests";
if [ ! -d "gpo-tests" ]; then
  echo "folder 'gpo-tests' - not found"
  exit;
else
  cd "gpo-tests";
fi

echo ">>> copy coex";
cp ../gpo.git/project/coex ./

echo ">>> test win 8 pro";
if [ -d "../gpo-testdata.git/Windows8_Pro" ]; then
  mkdir Win8Pro
  ./coex "../gpo-testdata.git/Windows8_Pro" "Win8Pro"
fi
