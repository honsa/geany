const char ctagsCommonPrelude []=
"%\n"
"% Copyright (c) 2021, Masatake YAMATO\n"
"% Copyright (c) 2021, Red Hat, Inc.\n"
"%\n"
"% This source code is released for free distribution under the terms of the\n"
"% GNU General Public License version 2 or (at your option) any later version.\n"
"%\n"
"\n"
"%\n"
"% The documentation table\n"
"%\n"
"\n"
"% __PROCDOCS:dict<proc:name, doc:string>\n"
"/__procdocs 30 dict def\n"
"\n"
"% name value __BDEF -\n"
"/__bdef { bind def }  bind def\n"
"\n"
"% doc:string key:name any:val __DOCDEF -\n"
"/__bddef {\n"
"    1 index exch __bdef\n"
"    exch __procdocs 3 1 roll put\n"
"} __bdef\n"
"\n"
"\n"
"%\n"
"% procedures\n"
"%\n"
"(any n:int _NDUP any1 ... anyn)\n"
"/_ndup { { dup } repeat } __bddef\n"
"\n"
"(x:any x:any _DEDUP x:any\n"
" x:any y:any _DEDUP x:any y:any)\n"
"/_dedup {\n"
"    count 1 gt {\n"
"        2 copy eq {\n"
"            pop\n"
"        } if\n"
"    } if\n"
"} __bddef\n"
"\n"
"(space:int space:int _DEDUP_SPACES space:int\n"
" otherthanspace:int space:int _DEDUP_SPACES otherthanspace:int space:int)\n"
"/_dedup_spaces {\n"
"    count 0 gt {\n"
"        dup ?\\_ eq {\n"
"            _dedup\n"
"        } if\n"
"    } if\n"
"} __bddef\n"
"\n"
"% 32 32 _dedup_spaces pstack clear (---) ==\n"
"% 32 41 _dedup_spaces pstack clear (---) ==\n"
"% 41 32 _dedup_spaces pstack clear (---) ==\n"
"% 32 _dedup_spaces pstack clear (---) ==\n"
"% 41 _dedup_spaces pstack clear (---) ==\n"
"% quit\n"
"\n"
"/__buildstring {\n"
"    {\n"
"	    counttomark dup 1 eq {\n"
"	        pop exch pop\n"
"	        exit\n"
"	    } {\n"
"	        -1 roll 1 index exch _putlast!\n"
"	    } ifelse\n"
"    } loop\n"
"} __bdef\n"
"\n"
"(mark char:int|substring:string... _BUILDSTRING string)\n"
"/_buildstring {\n"
"    0 string __buildstring\n"
"} __bddef\n"
"\n"
"(string char:int|string _PUTLAST! -)\n"
"/_putlast!  {\n"
"    1 index length exch\n"
"    dup type /integertype eq {\n"
"	    put\n"
"    } {\n"
"	    putinterval\n"
"    } ifelse\n"
"} __bddef\n"
"\n"
"(target:string fromto:str _TR! -)\n"
"/_tr! {\n"
"    %\n"
"    % () is not allowed.\n"
"    % The reason must be be documented.\n"
"    %\n"
"    0 string\n"
"    % str [int<from> int<to>] str'\n"
"    2 index {\n"
"	% str [int<from> int<to>] str' int<chr>\n"
"	    dup 3 index 0 get\n"
"	% str [int<from> int<to>] str' int<chr> int<chr> int<from>\n"
"	    eq {% str [int<from> int<to>] str' int<chr>\n"
"	        pop\n"
"	        dup 2 index 1 get _putlast!\n"
"	    } {% str [int<from> int<to>] str' int<chr>\n"
"	        1 index exch _putlast!\n"
"	    } ifelse\n"
"    } forall\n"
"    % str [int<from> int<to>] str'\n"
"    exch pop\n"
"    0 exch putinterval\n"
"} __bddef\n"
"\n"
"(string _NORMALIZE_SPACES! -)\n"
"/_normalize_spaces! {\n"
"    dup\n"
"    dup (\\n ) _tr!\n"
"    dup (\\t ) _tr!\n"
"    dup (\\r ) _tr!\n"
"    dup (\\f ) _tr!\n"
"    dup (\\v ) _tr!\n"
"    mark exch { _dedup_spaces } forall _buildstring\n"
"    exch copy pop\n"
"} __bddef\n"
"\n"
"(string _CHOP string)\n"
"/_chop {\n"
"    mark exch {} forall pop _buildstring\n"
"} __bddef\n"
"\n"
"(string _CHOP_SPACE string)\n"
"/_chop_space {\n"
"    dup length dup 0 gt {\n"
"        % string length\n"
"        1 sub\n"
"        % string `length - 1`\n"
"        1 index exch\n"
"        % string string `length - 1`\n"
"        get (\\n\\t\\r\\f\\v ) exch _amember {\n"
"            _chop\n"
"        } if\n"
"    } {\n"
"        pop                     % pop the length\n"
"    } ifelse\n"
"} __bddef\n"
"\n"
"% /x mark 40 (a) 32 32 10 (b) 10 10 9 9 (xyz) 9 9 41 _buildstring def\n"
"% x _normalize_spaces! x pstack\n"
"\n"
"(tag:int _SCOPEREF -)\n"
"/_scoperef {\n"
"    _scopetop not { 0 } if scope:\n"
"} __bddef\n"
"\n"
"(tag:int _SCOPEPUSH -)\n"
"/_scopepush {\n"
"    dup _scoperef _scopeset\n"
"} __bddef\n"
"\n"
"(string _ISSTRING string true\n"
" any:!string _ISSTRING false)\n"
"/_isstring {\n"
"    dup type /stringtype eq {\n"
"        true\n"
"    } {\n"
"        pop false\n"
"    } ifelse\n"
"} __bddef\n"
"\n"
"(array key _AMEMBER true|fales)\n"
"/_amember {\n"
"    false 3 1 roll\n"
"    % false array key\n"
"    exch {\n"
"        % false key elt\n"
"        1 index\n"
"        % false key elt key\n"
"        eq {\n"
"            % false key\n"
"            exch pop true exch\n"
"            exit\n"
"        } if\n"
"        % false key\n"
"    } forall\n"
"    pop\n"
"} __bddef\n"
"\n"
"(array key _AINDEX nth:int true\n"
" array key _AINDEX false)\n"
"/_aindex {\n"
"    0 3 1 roll\n"
"    % idx array key\n"
"    exch {\n"
"        % idx key elt\n"
"        1 index\n"
"        eq {\n"
"            % idx key\n"
"            pop true exit\n"
"        } {\n"
"            % idx key\n"
"            exch 1 add exch\n"
"        } ifelse\n"
"    } forall\n"
"    dup true ne { pop pop false } if\n"
"} __bddef\n"
"\n"
"% define @1 ~ @9.\n"
"1 1 9 {\n"
"    dup\n"
"    mark (- @) 3 -1 roll ?0 add ( start:matchloc) _buildstring\n"
"    exch dup\n"
"    mark (@) 3 -1 roll ?0 add _buildstring cvn\n"
"    exch\n"
"    [ exch /start /_matchloc cvx ] cvx __bddef\n"
"} for\n"
"\n"
"% define 1@ ~ 9@.\n"
"1 1 9 {\n"
"    dup\n"
"    mark (- ) 3 -1 roll ?0 add (@ end:matchloc) _buildstring\n"
"    exch dup\n"
"    mark exch ?0 add (@) _buildstring cvn\n"
"    exch\n"
"    [ exch /end /_matchloc cvx ] cvx __bddef\n"
"} for\n"
"\n"
"(name:str kind:name matchloc _TAG tag\n"
" name:str kind:name _TAG tag)\n"
"/_tag {\n"
"    dup type /nametype eq {\n"
"        % name:str kind:name\n"
"        null exch null\n"
"        % name:str null kind:name null\n"
"    } {\n"
"        % name:str kind:name matchloc\n"
"        null 3 1 roll null exch\n"
"        % name:str null kind:name matchloc null\n"
"    } ifelse\n"
"    _foreignreftag\n"
"} __bddef\n"
"\n"
"(name:str kind:name role:name matchloc _REFTAG tag\n"
" name:str kind:name role:name _REFTAG tag)\n"
"/_reftag {\n"
"    dup type /nametype eq {\n"
"        % name:str kind:name role:name\n"
"        null 3 1 roll\n"
"        % name:str null kind:name role:name\n"
"    } {\n"
"        % name:str kind:name role:name matchloc\n"
"        null 4 1 roll\n"
"        % name:str null kind:name role:name matchloc\n"
"    } ifelse\n"
"    _foreignreftag\n"
"} __bddef\n"
"\n"
"(name:str language:name kind:name matchloc _FOREIGNTAG tag\n"
" name:str lang:name kind:name _FOREIGNTAG tag)\n"
"/_foreigntag {\n"
"    null _foreignreftag\n"
"} __bddef\n"
;
