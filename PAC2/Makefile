# general vars

# targets

all : countersA counters2A counters_ww_seq counters_ww_par

.PHONY: all

countersA : countersA.c
	gcc -I/export/apps/papi/include/ $(@).c /export/apps/papi/lib/libpapi.a -o $(@)

counters2A : counters2A.c
	gcc -I/export/apps/papi/include/ $(@).c /export/apps/papi/lib/libpapi.a -o $(@)

counters_ww_seq : counters_ww_seq.c
	gcc -I/export/apps/papi/include/ $(@).c /export/apps/papi/lib/libpapi.a -o $(@)

counters_ww_par : counters_ww_par.c
	gcc -I/export/apps/papi/include/ -fopenmp $(@).c /export/apps/papi/lib/libpapi.a -o $(@)

