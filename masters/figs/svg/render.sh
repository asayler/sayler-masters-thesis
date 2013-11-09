#!/usr/bin/env bash

shopt -s nullglob
srcdir="./"
srcext=".svg"
sources=( "${srcdir}"*"${srcext}" )
tmpdir="./"
tmpext=".eps"
dstdir="../pdf/"
dstext=".pdf"

for src in "${sources[@]}"
do
    base=$(basename "${src}" "${srcext}")
    dst="${dstdir}${base}${dstext}"
    tmp="${tmpdir}${base}${tmpext}"
    echo "Converting $src to $dst..."
    inkscape --export-area-drawing --export-eps="${tmp}" --file="${src}"
    epstopdf "${tmp}" --outfile="${dst}"
    rm "${tmp}"
done
