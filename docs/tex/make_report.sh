# cp -R gpo.pdf gpo_backup.pdf
rm gpo.pdf
# convert images-arch/alg_main.png images-arch/alg_main.eps
# sam2p images-arch/alg_main.png images-arch/alg_main.eps

pdflatex gpo.tex

# еще раз что бы оглавление встало как надо
pdflatex gpo.tex

rm gpo.log
rm gpo.toc
rm gpo.aux


