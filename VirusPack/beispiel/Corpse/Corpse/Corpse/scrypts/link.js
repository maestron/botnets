document.onmouseover = domouseover;
document.onmouseout = domouseout;
function domouseover() {
if(document.all){
srcElement = window.event.srcElement;
if (srcElement.className.indexOf("fade") > -1) {
var linkName = srcElement.name;
fadein(linkName);
}}}
function domouseout() {
if (document.all){
srcElement = window.event.srcElement;
if (srcElement.className.indexOf("fade") > -1) {
var linkName = srcElement.name;
fadeout(linkName);
}}}
function makearray(n) {
this.length = n;
for(var i = 1; i <= n; i++)
this[i] = 0;
return this;}
hexa = new makearray(16);
for(var i = 0; i < 10; i++)
hexa[i] = i;
hexa[10]="a"; hexa[11]="b"; hexa[12]="c";
hexa[13]="d"; hexa[14]="e"; hexa[15]="f";
function hex(i) {
if (i < 0)
return "00";
else if (i > 255)
return "ff";
else
return "" + hexa[Math.floor(i/16)] + hexa[i%16];}
function setbgColor(r, g, b, element) {
var hr = hex(r); var hg = hex(g); var hb = hex(b);
element.style.color = "#"+hr+hg+hb;}
function fade(sr, sg, sb, er, eg, eb, step, direction, element){
for(var i = 0; i <= step; i++) {
setTimeout("setbgColor(Math.floor(" +sr+ " *(( " +step+ " - " +i+ " )/ " +step+ " ) + " +er+ " * (" +i+ "/" +step+ ")),Math.floor(" +sg+ " * (( " +step+ " - " +i+ " )/ " +step+ " ) + " +eg+ " * (" +i+ "/" +step+ ")),Math.floor(" +sb+ " * ((" +step+ "-" +i+ ")/" +step+ ") + " +eb+ " * (" +i+ "/" +step+ ")),"+element+");",i*step);
}}
function fadeout(element) {        
fade(80,150,190, 140,175,200, 30, 1, element);}
function fadein(element) {
fade(140,175,200, 60,140,200, 23, 1, element);}