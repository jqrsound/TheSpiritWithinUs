all: spirit src.zip map.png

C = object.c misc.c match.c noun.c toggle.c location.c move.c reach.c inventory.c inventory2.c openclose.c onoff.c expand.c parsexec.c turn.c damage.c attack.c manual.c clear.c flashback.c end.c fire.c health.c fox.c main.c
H = object.h misc.h match.h noun.h toggle.h location.h move.h reach.h inventory.h inventory2.h openclose.h onoff.h expand.h parsexec.h turn.h damage.h attack.h manual.h clear.h flashback.h end.h fire.h health.h fox.h


spirit: $(C) $(H)
	gcc -Wall -Wextra -Wpedantic -Werror $(C) -o $@

object.h: object.awk object.txt
	awk -v pass=h -f object.awk object.txt > $@

object.c: object.awk object.txt
	awk -v pass=c1 -f object.awk object.txt > $@
	awk -v pass=c2 -f object.awk object.txt >> $@

src.zip: $(C) $(H) object.txt makefile
	zip -rq $@ $^

clean:
	$(RM) object.c object.h spirit sop.testable *.gcda *.gcno *.gcov  map.gv map.png src.zip

map.png:
	awk -f map.awk object.txt >map.gv && dot -Tpng -o map.png map.gv
