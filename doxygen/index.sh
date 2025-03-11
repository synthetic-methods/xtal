#!/usr/bin/env sh

git fetch --all
git checkout origin/main -- include
git reset include

mkdir -p exclude/xtal
clang -std=c++20 -E -C -P -DXTAL_DOC include/xtal/all.hh | perl -pe "s|/[*]/|/***/|g" | perl -pe 's|^////+||g' > exclude/xtal/all.hh

doxygen doxygen/Doxyfile
find exclude/xtal/html -name "*.html" -type f -print0 | xargs -0 perl -0777 -i -pe 's/(Documentation|Reference)//g'
find exclude/xtal/html -name "*.html" -type f -print0 | xargs -0 perl -0777 -i -pe 's/(Struct) (?:Template)/\1/g'
find exclude/xtal/html -name "*.html" -type f -print0 | xargs -0 perl -0777 -i -pe 's/([^<>]*?) Class/<span class="soft">class<\/span> <a href="https:\/\/github.com\/synthetic-methods\/xtal" target="_blank">\1<\/a>/g'
find exclude/xtal/html -name "*.html" -type f -print0 | xargs -0 perl -0777 -i -pe 's/([^<>]*?) Struct/<span class="soft">struct<\/span> <a href="https:\/\/github.com\/synthetic-methods\/xtal" target="_blank">\1<\/a>/g'
find exclude/xtal/html -name "*.html" -type f -print0 | xargs -0 perl -0777 -i -pe 's/([^<>]*?) Concept/<span class="soft">concept<\/span> <a href="https:\/\/github.com\/synthetic-methods\/xtal" target="_blank">\1<\/a>/g'
find exclude/xtal/html -name "*.html" -type f -print0 | xargs -0 perl -0777 -i -pe 's/([^<>]*?) Namespace/<span class="soft">namespace<\/span> <a href="https:\/\/github.com\/synthetic-methods\/xtal" target="_blank">\1<\/a>/g'
find exclude/xtal/html -name "*.html" -type f -print0 | xargs -0 perl -0777 -i -pe 's/>[\n\r]\b/>/gm'
find exclude/xtal/html -name "*.html" -type f -print0 | xargs -0 perl -0777 -i -pe 's/&lt; ([A-Z_][a-z_]*) &gt;/&lt;\1&gt;/g'
find exclude/xtal/html -name "*.html" -type f -print0 | xargs -0 perl -0777 -i -pe 's/&lt;([A-Z_]s)&gt;/&lt;...\1&gt;/g'
