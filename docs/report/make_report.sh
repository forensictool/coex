#!/bin/bash

pdflatex report.tex
bibtexu report.aux
pdflatex report.tex
