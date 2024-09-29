all: make

make:
	(cd src/; make; cd ..)
	cp src/Chess bin/

test:
	(cd src/; make testboarddisplay; ./testboarddisplay;cd ..)
	(cd src/; make testrulecheck;./rulecheck; cd ..)

tar:
	gtar cvzf Chess_V1.0_src.tar.gz README.txt LICENSE.txt INSTALL.txt Makefile bin/ doc/ src/
	gtar cvzf Chess_V1.0.tar.gz README.txt LICENSE.txt INSTALL.txt bin/ doc/Chess_UserManual.pdf
	
clean:
	(cd src/; make clean; cd ..)
	rm *.tar.gz
