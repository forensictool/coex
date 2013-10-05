if [ -f "coex" ]; then
  rm coex
fi

if [ -f "computer_examination/computer_examination" ]; then
  rm computer_examination/computer_examination
fi

if [ -f "computer_examination/Makefile" ]; then
  rm computer_examination/Makefile
fi

rm computer_examination/*.o
