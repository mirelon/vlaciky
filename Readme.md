Povodne som chcel mat len dva thready - jeden rata pravdepodobnosti, druhy vykrasluje. No lenze grafika je blokujuca a trva velmi dlho, preto som musel pridat treti thread, ktory je akasi "medzivrstva": pre simulaciu sa tvari, ze vykresluje, a posliela nejake veci na vykreslenie. Takze neposiela vsetko, iba nieco.

# Thread 1 #

## main.cpp ##
  * spusti aplikaciu

## metro.cpp ##
  * inicializuje grafiku
  * inicializuje simulaciu
  * stara sa o shortcuty, rozdeluje pracu, spusta thready

## graphics.cpp ##
  * loadne mapu, udrzuje si graficke objekty na poziciach
  * updatuje im opacity vzdy ked dojde event



# Thread 2 #

## simulation.cpp ##
  * inicializuje rail
  * inicializuje myThread
  * hlavny cyklus, na ktorom zavisi casovanie
  * v jednom kole:
    * updatne pravdepodobnosti (~0.1 - 7ms)
    * posliela spravy myThreadu (~1 - 16ms)
    * zaspi (50ms)

## rail.cpp ##
  * stara sa o topologiu, prepaja vytvara stavy, prepaja ich, pridava senzory
  * vie odpovedat na lubovolne query tykajuce sa pravdepodobnosti


# Thread 3 #

## mythread.cpp ##
  * dostava spravy, ktore treba vykreslit
  * aby nespomaloval graficky thread, tak da vykreslit len tie najdolezitejsie
  * pouziva haldu, prida event, ze na danom policku sa ma zmenit opacita na x
  * pre dane policko vie opacitu, aka tam bola doteraz (y), priorita je |x-y|
  * hlavny cyklus mythreadu robi toto:
    * pozrie vrch haldy, je tam event policka p
    * porovna kolo, v ktorom sa predtym updatlo p, ak je novy event naozaj novsi, da ho vykreslit
      * lebo niekedy moze novsi event na tom istom policku v halde predbehnut starsi a menej dolezity event
    * zaspi na 2ms
  * halda by takto rastla do nekonecna. Preto by sa tam nemali davat eventy s malou prioritou (rozdiel v opacite +-2 ani nezbadame)
  * Udrziava sa priemerna priorita haldy a do haldy sa prida novy event, len ak ma prioritu vacsiu ako polovica tohto priemeru