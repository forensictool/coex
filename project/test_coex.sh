
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


echo ">>> test win xp sp3 pro"
if [ -d "../gpo-testdata.git/WindowsXP_SP3_Pro" ]; then
  mkdir "WinXPSP3Pro"
  ./coex :all "../gpo-testdata.git/WindowsXP_SP3_Pro" "WinXPSP3Pro"
fi

echo ">>> test win 7 ult"
if [ -d "../gpo-testdata.git/Windows7_Ult" ]; then
  mkdir "Win7Ult"
  ./coex :all "../gpo-testdata.git/Windows7_Ult" "Win7Ult"
fi

echo ">>> test win 8 pro";
if [ -d "../gpo-testdata.git/Windows8_Pro" ]; then
  mkdir Win8Pro
  ./coex :all "../gpo-testdata.git/Windows8_Pro" "Win8Pro"
fi
