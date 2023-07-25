=====
FIXME
=====

Provisions the alternative test index `./include/FIXME.cxx`,
used in place of `./include/xtal.c++` if `[ -f ./include/FIXME.cxx ]`.

The following commands index `./include/xtal`:

	sh FIXME        #include `**/*.c++` containing `FIXME`
	sh FIXME ++     #include `*/*.c++` except `all.c++`
	sh FIXME +      #include `*/all.c++`
	sh FIXME .      # `rm ../include/FIXME.cxx`
	sh FIXME        # `rm ../include/FIXME.cxx` only if the resulting index is empty
	sh FIXME --help # `echo ./FIXME.md`
