cd computer_examination
QMAKE=""

# usr/bin/qmake-qt4
if [ -f "/usr/bin/qmake-qt4" ]; then
  QMAKE="qmake-qt4"
fi

# bin/qmake-qt4
if [ -f "/bin/qmake-qt4" ]; then
  QMAKE="qmake-qt4"
fi

# bin/qmake 
if [ -f "/bin/qmake" ]; then
  QMAKE="qmake"
fi

# usr/bin/qmake 
if [ -f "/usr/bin/qmake" ]; then
  QMAKE="qmake"
fi

$QMAKE && make
cp computer_examination ../coex
chmod +x ../coex
cd ..