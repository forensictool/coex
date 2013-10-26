# cp -R gpo.pdf gpo_backup.pdf
rm gpo.pdf
# find . -type f -name "*.png" -printf "convert %p && sh %p && rm %p \n" | sh
convert images-arch/alg_main.png images-arch/alg_main.eps
# sam2p images-arch/alg_main.png images-arch/alg_main.eps

latex gpo.tex
# повторяем что бы сгенерировалось Оглавление
latex gpo.tex
# создаем pdf
dvipdf gpo.dvi 



# еще раз что бы оглавление встало как надо
# pdflatex gpo.tex

rm gpo.log
rm gpo.toc
rm gpo.aux
rm gpo.dvi


