#!/bin/bash

pdflatex report.tex
bibexu report.aux
pdflatex report.tex
