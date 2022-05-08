# tspain(t)

## Zadání z progtestu
Naprogramujte jednoduchý nástroj pro zobrazení obrázků definovaných v textovém souboru.

Program musí splňovat následující funkcionality:

Načíst ze souboru a z konzole definici jednotlivých objektů v prostoru (velikost obrázku, pozice a parametry objektů, ...).
- Program podporuje minimálně čáru, polyline, kruh, elipsu, obdélník a skupinu objektů.
- Objektům se dají nastavovat různé barvy (v případě ASCII styl vykreslování) a výplně.
- Obrázek je nutné reprezentovat jako graf scény - stromovou strukturu (případně DAG)
- Skupina objektů funguje jako vzor, tudíž po vytvoření skupiny objektů můžu tuto skupinu vložit několikrát do obrázku na různá místa.
- Implementujte alespoň 2 různé výstupní formáty (ASCII, BMP, SVG, ..., SDL, OpenGL, ...)

Kde lze využít polymorfismus?

- objekty k vykreslení: kruh, trojúhelník, obdélník,...
- dekodér vstupních dat: příkazová řádka, (vlastní) textový formát, XML, ...
- enkodér výstupních dat: ASCII (různé druhy), BMP, SVG, ..., SDL, OpenGL, (výstup můžete zobrazit přímo na obrazovku) ...
- nástroje k vykreslení: stínování, vyplnění objektu barvou, ...

Další informace:

- https://www.root.cz/clanky/graficky-format-bmp-pouzivany-a-pritom-neoblibeny/
- http://www.vzhurudolu.cz/prirucka/svg
- http://www.onicos.com/staff/iz/formats/gif.html

Možno implementovat i sekvenci obrázků (video)

## Rozšíření zadání

Jen málokdo se nesetkal se "starým dobrým" malováním, MSPAINT. 

Toto "rozšíření" populárního programu cílí na studenty BI-PA2, kteří již mají za sebou (mnozí dokonce vícekrát) krásné 
chvilky strávené laděním kódu, který z nějakého důvodu padá a oni netuší proč. Z populárního prostředí Progtestu si program
tspain(t) bere jen to nejlepší - striktní uživatelský vstup, který pakliže neodpovídá specifikaci, vede k ukončení programu. 
Mimo jiné nabízí jenom omezené množství barev, které studentům pojmenovaných příhodně podle jejich oblíbeného programu na 
nedělní odpoledne, výčtem 

- Progtestí šeď (#aaaaaa)
- Tam, kde oko nedohlédne (#828272)
- V hloubi duše (#000000)
- Brain overflow - barva zkoušky (#ff00ff)
- Jako doma - standardní barva progtestu (#00ff00)
- Zkompilováno s chybami (#c04000)
- Zábava na víkend - barva zadání ulohy (#0099cb)
- Zelená "Už tam skoro jsme" (#80c000)
- Zelená Vítězství (#00c000)
- Načítání - bílá (#ffffff)


Kde bychom ale byli, kdyby se zde neobjevila nějaká všeobsažná zároveň absolutně nicneříkající chybová hláška, či jejich
kombinace? V blíže nespecifikovaných okamžicích je uživatel potěšen starou známou hláškou 
"Program provedl neplatnou operaci a byl ukončen (Segmentation fault/Bus error/Memory limit exceeded/Stack limit exceeded)",
či její variací. 

Program (nejspíše) bude mít k dispozici minimalistické grafické uživatelské rozhraní umožňující přinejmenším zobrazení 
vygenerovaného obrazu scény a bude umožňovat export do formátu, ve kterém si jej uživatelé s menší představivostí budou 
moci zobrazit mimo tspain(t), kde to nebude takový pain. 

Polymorfismus plánuji využít u vykreslování objektů, případně u enkodéru výstupních dat. 

===================
This iS PAIN by Tom