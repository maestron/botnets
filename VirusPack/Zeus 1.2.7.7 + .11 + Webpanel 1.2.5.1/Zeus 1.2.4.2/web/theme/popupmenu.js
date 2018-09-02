var jsmLastMenu = -1,
    jsmPrevMenu = -1;

function jsmHideLastMenu()
{
  if(jsmPrevMenu != -1)jsmSetDisplayStyle('popupmenu' + jsmPrevMenu, 'none');
  jsmPrevMenu = jsmLastMenu;
}

function jsmShowMenu(id, MenuData, values1, values2)
{
  jsmHideLastMenu();
  
  jsmPrevMenu = -1;
  jsmLastMenu = id;
  var slideHTML = '<div style="position:absolute; z-index:99' + id + '" class="popupmenu"><table cellpadding="0" cellspacing="0">';
  var ids = new Array();

  for(i = 0; i <= MenuData.length; i++)if(MenuData[i])
  {
    if(MenuData[i][0] == 0)slideHTML += '<tr><td><hr /></td></tr>';
    else
    {
      slideHTML += '<tr><td><a href="'+ jsmFormatSting(MenuData[i][1], values2) + '" onclick="this.target=\'_blank\'">' + jsmFormatSting(MenuData[i][0], values1) + '</a></td></tr>';
      ids.push(i);
    }
  }
  
  document.getElementById('popupmenu' + id).innerHTML = slideHTML + '</table></div>';
  jsmSetDisplayStyle('popupmenu' + id, 'inline');

  return false;
}

function jsmSetDisplayStyle(block, style)
{
  document.getElementById(block).style.display = style;
}

function jsmFormatSting(str, values)
{
  for(var j = 0; j < values.length; j++)str = str.replace(RegExp('\\$' + j +'\\$', 'g'), values[j]);
  return str;
}
