=====
FIXME
=====

`FIXME` provisions the alternative test index `./include/xtal.cxx` (which is `.gitignore`d). This is used in place of `include/xtal.c++` when it exists (and is otherwise `.gitignore`d).

To test specific `include/**/*.c++` files, add `FIXME` anywhere in the body and run `source FIXME`.

To restore the original index, either `rm ./include/xtal.cxx`, or run `source FIXME` once again after removing all occurences.
