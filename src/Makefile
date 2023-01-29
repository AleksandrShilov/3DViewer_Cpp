TESTCOVERAGE = -fprofile-arcs -ftest-coverage
CPP = --suppress=missingIncludeSystem --suppress=unmatchedSuppression --suppress=unusedFunction --suppress=useStlAlgorithm
STD = g++ --std=c++17
WASH=rm -rf *.o *.a *.out *.log *.aux *.dvi *.toc *css *gcno *gcda CPPLINT.cfg *tgz *.html man_ru report .clang-format
OS=$(shell uname)

ifeq ($(OS), Linux)
	LEAKS=CK_FORK=no valgrind --leak-check=full --track-origins=yes -s
	TEST =  -lgtest -pthread --coverage
else
	LEAKS=CK_FORK=no leaks --atExit --
	TEST =  -lgtest -fsanitize=address -pthread --coverage
endif


all: clean test check install


install: build clean


build:
	mkdir build
	cd build; cmake ..
	make -C build


uninstall:
	rm -rf $(HOME)/Desktop/3DViewer/
	rm -rf build


dvi:
	makeinfo --html --no-warn --no-validate --force ./man_ru.texi


dist:
	rm -rf 3DViewer
	mkdir 3DViewer
	cp Makefile model/* view/* controller/* *.txt *.texi *.cc *.txt 3DViewer/
	tar -zcvf ./3DViewer.tar.tgz ./3DViewer
	rm -rf 3DViewer/


gcov_report: test
	./test.out
	mkdir report
	gcovr -r ../ -e ../googletest-1.10.x --html --html-details -o report/result.html
	open report/result.html


test: model.o
	g++ test.cc $^ -o test.out $(TEST)
	./test.out


test.o: test.cc
	g++ $(STD) $(TESTCOVERAGE) -c $^ -o $@ 


model.o: model/model.cc
	$(STD) $(TESTCOVERAGE) -c $^


leaks:
	$(LEAKS) ./test.out


clang:
	cp ../materials/linters/.clang-format ./
	#clang-format -i controller/* model/* view/*.cc view/*.h test.cc main.cc
	clang-format -n controller/* model/* view/*.cc view/*.h test.cc main.cc


cppcheck:
	-cppcheck --language=c++ --enable=all --std=c++17 model/* controller/* view/*.cc *.h test.cc $(CPP)

check: leaks clang cppcheck

clean:
	$(WASH)
