OUTDIR=dist
CFLAGS= -O2

.PHONY: default clean

default: test clean

$(OUTDIR):
	@mkdir -p $(OUTDIR)

test: $(OUTDIR) $(OUTDIR)/levenstein.o $(OUTDIR)/main.o
	gcc $(CFLAGS) $(OUTDIR)/levenstein.o $(OUTDIR)/main.o -o test
	./test

$(OUTDIR)/levenstein.o: levenstein.c
	gcc $(CFLAGS) -o $(OUTDIR)/levenstein.o -c $^

$(OUTDIR)/main.o: main.c
	gcc $(CFLAGS) -o $(OUTDIR)/main.o -c $^ 

clean:
	@rm -f test
	@rm -rf $(OUTDIR)
