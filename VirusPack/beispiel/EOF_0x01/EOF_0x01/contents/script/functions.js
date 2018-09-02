//Powered by Microsoft® Office FrontPage® 2003
//Functions for EOF viewer

//Swap Image function
function si()
 {
  var doc=document,args=arguments,elm,n;
  doc.$imgSwaps=new Array();
  for(n=2;
  n<args.length;n+=2)
  {
   elm=gobi(args[n]);
   if(elm)
   {
    doc.$imgSwaps[doc.$imgSwaps.length]=elm;
    elm.$src=elm.src;
    elm.src=args[n+1];
   }
  }
 }

//Get Element By ID function
function gobi(id,o)
 {
  var c,el,els,f,m,n;
  if(!o)o=document;
  if(o.getElementById) el=o.getElementById(id);
  else if(o.layers) c=o.layers;
  else if(o.all) el=o.all[id]; 
  if(el) return el;
  if(o.id==id || o.name==id) return o;
  if(o.childNodes) c=o.childNodes;
  if(c)
  for(n=0;
  n<c.length; n++)
  {
   el=gobi(id,c[n]);
   if(el) return el;
  }
   f=o.forms;
   if(f) for(n=0;
   n<f.length; n++) 
   { 
    els=f[n].elements;
    for(m=0;
    m<els.length;
    m++)
    {
     el=gobi(id,els[n]);
     if(el) return el;
    }
   }
    return null;
  }

//Swap Image Restore function
function sir() 
 {
  var doc=document,i; 
  if(doc.$imgSwaps)
  { 
   for(i=0;
   i<doc.$imgSwaps.length;
   i++)
   {
    var elm=doc.$imgSwaps[i];
    if(elm)
    {
     elm.src=elm.$src; 
     elm.$src=null;
    }
   }
    doc.$imgSwaps=null;
  }
 }

//Open New Window function
function onw(w,h,nav,loc,sts,menu,scroll,resize,name,url)
 {
 var windowProperties='';

 if(nav==false) windowProperties+='toolbar=no,';else
 windowProperties+='toolbar=yes,';

 if(loc==false) windowProperties+='location=no,';else
 windowProperties+='location=yes,';

 if(sts==false) windowProperties+='status=no,';else
 windowProperties+='status=yes,';

 if(menu==false) windowProperties+='menubar=no,';else
 windowProperties+='menubar=yes,';

 if(scroll==false) windowProperties+='scrollbars=no,';else
 windowProperties+='scrollbars=yes,';

 if(resize==false) windowProperties+='resizable=no,';else
 windowProperties+='resizable=yes,';

 if(w!="") windowProperties+='width='+w+',';
 if(h!="") windowProperties+='height='+h;
 if(windowProperties!="")
  { 
   if( windowProperties.charAt(windowProperties.length-1)==',') 
   windowProperties=windowProperties.substring(0,windowProperties.length-1);
 } 
  window.open(url,name,windowProperties);
}

//End of functions