#!/usr/bin/env bash

shopt -s nullglob
srcext=".svg"
sources=( ./*"${srcext}" )
dstdir="../pdf/"
dstext=".pdf"

for src in "${sources[@]}"
do
    base=$(basename "${src}" "${srcext}")
    dst="${dstdir}${base}${dstext}"
    echo "Converting $src to $dst..."
    inkscape --export-area-drawing --export-pdf="${dst}" --file="${src}"
done
