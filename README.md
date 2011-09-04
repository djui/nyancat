[Nyan cat](http://www.youtube.com/watch?v=QH2-TGUlwu4) ASCII animation in C for
terminal with music. Have fun.

# Background

The cross-plattform compatible C program compiles down to a single file
including the animation, music and libraries. It is mainly one function with a
loop that draws a frame, sleeps and clears the area. No extra libraries are
needed to display it. The music is composed using
[MilkyTracker](http://milkytracker.org/?about), an open-source multi-plattform
clone of the old and famous
[Fasttracker II](http://en.wikipedia.org/wiki/Fast_Tracker).
[MikMod](http://mikmod.raphnet.net/) library is use for playback of the module,
which is almost the only module playing library freely available with complete
source code and cross-plattform compatibility (Linux, Mac, BSD, Windows). Many
other libraries like [BassMod](http://www.un4seen.com/bassmod.html),
[Mini FMOD](http://www.fmod.org/index.php/download#FMODMini),
[μFMOD](http://ufmod.sourceforge.net/), or
[ModPlug Plugin](http://www.roncli.com/modplug/download.asp?FileID=7) are either
not open source, or don't support all major plattforms.

# Credits

 * [Nick Baugh (niftylettuce)](https://github.com/niftylettuce/nyancat.js) for
   ASCII cat and initial idea
 * [Original song](http://www.nicomimi.net/play/sm13455867)
 * [Brandon Carrita](http://www.2shared.com/file/HnuKON25/Nyan_Cat_Sheet_Music.html)
   for the music sheets

    ,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`
    .,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,
    *.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^         ,---/V\
    `*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.    ~|__(o.o)
    ^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'^`*.,*'  UU  UU
