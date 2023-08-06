=====
FIXME
=====

Provisions the alternative test index `./include/FIXME.c++`,
used in place of `./include/xtal.cc` if `[ -f ./include/FIXME.c++ ]`.

The following commands index `./include/xtal`:

	sh FIXME        #include `**/*.cc` containing `FIXME`
	sh FIXME ++     #include `*/*.cc` except `all.cc`
	sh FIXME +      #include `*/all.cc`
	sh FIXME .      # `rm ../include/FIXME.c++`
	sh FIXME        # `rm ../include/FIXME.c++` only if the resulting index is empty
	sh FIXME --help # `echo ./FIXME.md`
