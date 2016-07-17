SRCSVG = $(wildcard *.svg)
SRCFIG = $(wildcard *.fig)

TARGET1 = $(SRCSVG:%.svg=%.pdf)
TARGET2 = $(SRCFIG:%.fig=%.pdf)
.SUFFIXES: .svg .fig .pdf

.svg.pdf:
	inkscape -D $^ -A $@
.fig.pdf:
	fig2dev -Lpdf $^ > $@

all: $(TARGET1) $(TARGET2)

clean:
	$(RM) $(TARGET1) $(TARGET2)
