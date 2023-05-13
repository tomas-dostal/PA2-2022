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


## Assignment from progtest
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

### Polymorphism


- objects to draw: circle, ellipse, rectangle, polyline, group of objects, line
- output data encoder: BMP, SVG, tspaint


Polymorphism is used for rendering and exporting objects. Across the code we can see a `Draw` method.
This is used to prepare objects for export. All objects inheriting from `Shape` can actually be rendered using `PolyLine`,
so the conversion to `PolyLine` is used in the export. The `Draw` method is also used to prepare the ShapeGroup objects for export,
so any child of `SuperShape` can actually be drawn using the `Draw` method.

The modification with `PolyLine` was based on a previous submit last year, where the `SuperShape`'s `Draw` method was used to draw any object, 
however for every sigle one the implementation differed. Besides, it used shape-specific commands, thus required exporters
to support multiple shapes which could be substitued with single universal `PolyLine` object. 
This comes for a price of unability of usage of more advanced shapes for example in SVG, but makes the code 
easier to maintain.
The different exporters only define the minimum number of different objects - Polylines. 
Literally any object or group of objects can be converted to PolyLine, but it is sufficient to implement any of the exporters
actually only one method.

Inheritance is used for some shapes, for example, a square is a special case of a rectangle and basically they are just
four lines that are given some perpendicularity or parallelism, so they can be rendered with PolyLine.
With a little imagination, this can also be applied to an ellipse, or a circle, which is a special case of an ellipse.

By cleverly designing the interface, one can then use the input and output streams to make the interface work interactively. 
But not only that, it is also possible to use the same interface to work with files, which is a great advantage.
Basically that's the `.tspaint` "format".


### Class diagram of SuperShape and its children

![SuperShape class diagram](img/class_super_shape.png)

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


## TODO
- Forward declarations
- Dynamic cast (avoid if possible)
- Files I/O + file already exists 
- progtesterrors I/O!
