# tspain(t)

## Zadání z progtestu
Naprogramujte jednoduchý nástroj pro zobrazení obrázků definovaných v textovém souboru.

Program musí splňovat následující funkcionality:

Načíst ze souboru a z konzole definici jednotlivých objektů v prostoru (velikost obrázku, pozice a parametry objektů, ...).
- Program podporuje minimálně čáru, polyline, kruh, elipsu, obdélník a skupinu objektů.
- Objektům se dají nastavovat různé barvy (v případě ASCII styl vykreslování) a výplně.
- ***Obrázek je nutné reprezentovat jako graf scény - stromovou strukturu (případně DAG)***
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


## Input from progtest
Program a simple tool to display images defined in a text file.

The program must meet the following functionalities:

Load from the file and from the console the definition of each object in the space (image size, position and parameters of the objects, ...).
- The program supports at least line, polyline, circle, ellipse, rectangle and group of objects.
- Different colors (in case of ASCII style of rendering) and fills can be set for objects.
- ***The image must be represented as a scene graph - a tree structure (or DAG)***
- A group of objects acts as a pattern, so after creating a group of objects I can insert this group several times in the image in different places.
- Implement at least 2 different output formats (ASCII, BMP, SVG, ..., SDL, OpenGL, ...)

Where can I use polymorphism?

- objects to render: circle, triangle, rectangle,...
- input data decoder: command line, (custom) text format, XML, ...
- output data encoder: ASCII (various types), BMP, SVG, ..., SDL, OpenGL, (you can display the output directly on the screen) ...
- rendering tools: shading, filling the object with color, ...

Additional information:

- https://www.root.cz/clanky/graficky-format-bmp-pouzivany-a-pritom-neoblibeny/
- http://www.vzhurudolu.cz/prirucka/svg
- http://www.onicos.com/staff/iz/formats/gif.html

Image sequence can be implemented (video)

## Extending the assignment

Few people have not encountered the "good old" painting, MSPAINT.

This "extension" of the popular program targets BI-PA2 students who have already completed (many even multiple times) 
the beautiful moments spent debugging code that for some reason crashes, and they have no idea why. 
From the popular Progtest environment, the program tspain(t) takes only the best - strict user input, which, 
if it does not match the specification, leads to program termination.
Among other things, it offers only a limited number of colors, which students, aptly named after their favorite program on
Sunday afternoons, by listing

- Progtest grey `GRAY__PROGTEST` (#aaaaaa)
- Where the eye cannot see `GRAY__OUT_OF_SIGHT` (#828272)
- In the depths of the soul `BLACK__INSIDE_OF_MY_SOUL` (#000000)
- Brain overflow - `MAGENTA__BRAIN_OVERFLOW` color test (#ff00ff)
- At home - standard progtest color `GREEN__PROGTEST_HOME` (#00ff00)
- Compiled with errors `RED__COMPILED_WITH_ERRORS` (#c04000)
- Fun for the Weekend - task assignment color `BLUE__FUN_FOR_A_WEEKEND` (#0099cb)
- Green "We're almost there" `GREEN__ALMOST_THERE` (#80c000)
- Green Victory `GREEN__IM_DONE` (#00c000)
- Loading - white `WHITE__LOADING` (#ffffff)
- FIT yellow `YELLOW__FIT` (#f0ab00)


But where would we be if there wasn't some all-encompassing and at the same time absolutely unspoken error message, 
or their combination? At random moments, the user is delighted with the old familiar message
`"The program performed an invalid operation and was terminated (Segmentation fault/Bus error/Memory limit exceeded/Stack limit exceeded)"`,
or it's variation. 

The program has a minimalist CLI user interface that allows everything a PA2 student could wish for - a strict
user interface that has nothing extra.
The program allows export to a format in which even users with less imagination will be able to view it 
outside tspain(t), where it won't be such a pain.

### Polymorfismus 


- objekty k vykreslení: kruh, trojúhelník, obdélník,...
- dekodér vstupních dat: příkazová řádka, (vlastní) textový formát, XML, ...
- enkodér výstupních dat: ASCII (různé druhy), BMP, SVG, ..., SDL, OpenGL, (výstup můžete zobrazit přímo na obrazovku) ...
- nástroje k vykreslení: stínování, vyplnění objektu barvou, ...

> todo ne uplne v kazde tride, snazim se to protlacit co nejvys 
Polymorfismus je silně využit u vykreslování objektů, kde se pro libovolný objekt dědící z `SuperShape` volá metoda `Draw()`, 
která je přetížena v každé třídě, která dědí z `SuperShape`. Téměř každý objekt je popsatelný pomocí PolyLine, 
tudíž se při exportu využívá výpisu PolyLine.
Dále například čtverec je speciálním případem obdélníku a v podstatě jsou to jenom čtyři čáry, u kterých je daná nějaká
kolmost, či rovnoběžnost, mohou tedy sdílet metodu Draw() od předka PolyLine, naopak třeba kruh, či elipsa budou mít 
oproti PolyLine metodu Draw() rozdílnou (přestože by teoreticky nic nebránilo tomu všechny objekty vykreslovat jako 
PolyLine, u kruhu a elipsy by toto řešení při exportu do SVG způsobovalo nedokonalosti)


Ačkoliv tento přístup kupříkladu u SVG není ideální (jelikož zde existují speciální tvary kupříkladu pro čtverec)

Toto se nejspíše může ještě změnit i v závislosti na výstupním formátu, kde 
se například u SVG docela hodí využít basic shapes, které jsou v podstatě identické s těmi z tspain(t), naopak například 
formátu BMP by zjednodušený přístup "prostě to poskládat z úseček" ušetřil nemálo práce. 

Šikovným návrhem rozhraní se pak dá pomocí vstupních a výstupních streamů udělat rozhraní pracující např. jak interaktivně
s std::cin a std::cout, tak například se soubory (vlastní "formát", který je definovaný jako set instrukcí, které by jinak 
byly zadané do terminálu)


## Tspaint standard 

This is a specification for tspaint input/output format. Format is matching interactive command line input, however 
for a purpose of this work there needs to be a strict format specified.

Tspaint is a plaintext file with instructions/command calls. Only non-system commands are allowed in this standard, 
thus it is not allowed to import file with commands like 'load', 'save', 'quit' etc. 

Set command is a modifier, similary to old good mspaint, it changes the color/fill/thickness/..., which is applied to 
any shape created since that. 

[[TODO]]

Allowed commands are:
- set
  - color
    - id <size_t>
    - rgb <unsigned_char:r> <unsigned_char:g> <unsigned_char:b> <std::string name> 
  - fill
    - id <size_t> 
    - rgb <unsigned_char:r> <unsigned_char:g> <unsigned_char:b> <std::string name>
- draw
  - circle <size_t:center_x> <size_t:center_y> 
  - ...
- list

> Note: Range of {color,fill} id may differ depending on available colors stored in ColorPallete. 

Recommended separators are whitespaces. It is advised, however not required to write one command per line. 
If invalid input is detected (e.g. string where integer is expected), the rest of line is ignored.


# TODO
Forward deklarace
Konstatny koreluji s polymofrmini třídami // napriklad     exporter.Process(SHAPE_RECTANGLE, { // to lines!!!
Dynamic cast
Osestreni souboru zapis/cteni
Osetri progtesterrors I/O! 
Elipsa export neprizpusobi velikost obrazku
