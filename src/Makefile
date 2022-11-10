CC := gcc
CFLAGS := -ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
C_LIBS :=
TST_LIBS := -lgtest -lgmock -pthread

all: rebuild

rebuild: clean build

build:
	qmake -o QMakefile && make -f QMakefile

install: build
	mv PhotoLab.app ../build

uninstall:
	rm -rf ../build/PhotoLab.app

dist: install
	cd ../build && tar -zcf PhotoLab.tar.gz PhotoLab.app

dvi:
	open dvi.html

clean: clean_o clean_build clean_test
	rm -rf QMakefile

clean_test:
	rm -rf test/*.o
	rm -rf test/test
	rm -rf test/QMakefile
	rm -rf test/googletest

clean_o:
	rm -rf *.o

clean_build:
	rm -rf PhotoLab.app
	rm -rf ../build/PhotoLab.app
	rm -rf *.a
	rm -rf docs/*.aux
	rm -rf docs/*.dvi
	rm -rf docs/*.log
	rm -rf docs/*.out
	rm -rf docs/*.pdf
	rm -rf moc_*
	rm -rf .qmake.stash
	rm -rf ui_*.h

open:
	@cd test && open googletest.zip && sleep 3[s]


tests: clean open
	cd test && qmake -o QMakefile && make -f QMakefile && ./test

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./*.cc ./*/*.cc ./*/*.h
