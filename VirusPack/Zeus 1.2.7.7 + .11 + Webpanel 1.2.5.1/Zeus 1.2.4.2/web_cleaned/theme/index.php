<?php if(!defined('__CP__') && !defined('__INSTALL__'))die();

///////////////////////////////////////////////////////////////////////////////
// Данные темы.
///////////////////////////////////////////////////////////////////////////////

//Тип вывода.
define('THEME_CONTENT_TYPE', 'application/xhtml+xml');

//JavaScript.
define('THEME_JAVASCRIPT_BODY',     "<script type=\"text/javascript\"><![CDATA[\r\n{SCRIPT}\r\n]]></script>");
define('THEME_JAVASCRIPT_EXTERNAL', '<script type="text/javascript" src="{PATH}"></script>');

//Главное меню.
define('THEME_MAINMENU_SEPARATOR',    '<div class="menu_sep"></div>');
define('THEME_MAINMENU_SUBHEADER',    THEME_MAINMENU_SEPARATOR.'<div class="menu_hdr">{TITLE}</div>');
define('THEME_MAINMENU_ITEM',         '<a href="{URL}">{TEXT}</a>');
define('THEME_MAINMENU_ITEM_CURRENT', '<a href="{URL}">&#8594;&#160;{TEXT}</a>');

//Разное.
define('THEME_STRING_FORM_ERROR_1_BEGIN',   '<div class="error" style="text-align:center;margin:0 auto"><br/><br/>');
define('THEME_STRING_FORM_ERROR_1_END',     '<br/><br/></div>');
define('THEME_STRING_FORM_SUCCESS_1_BEGIN', '<div class="success" style="text-align:center;margin:0 auto"><br/><br/>');
define('THEME_STRING_FORM_SUCCESS_1_END',   '<br/><br/></div>');
define('THEME_STRING_BOLD_BEGIN',           '<b>');
define('THEME_STRING_BOLD_END',             '</b>');
define('THEME_STRING_NEWLINE',              '<br/>');
define('THEME_STRING_ID_BEGIN',             '<div id="{ID}">');
define('THEME_STRING_ID_END',               '</div>');
define('THEME_STRING_ERROR',                '<strong class="error">{TEXT}</strong>');
define('THEME_STRING_SUCCESS',              '<strong class="success">{TEXT}</strong>');
define('THEME_STRING_HELP_ANCHOR',          '<a href="{URL}" onclick="this.target=\'_blank\'">[?]</a>');
define('THEME_VSPACE',                      '<div><br/><br/></div>');

//Предпросмтор отчета.
define('THEME_STRING_REPORTPREVIEW',     '<a onclick="this.target=\'_blank\'" href="{URL}">[+]</a>&#160;{TEXT}');
define('THEME_STRING_REPORTPREVIEW_FTP', '<a onclick="this.target=\'_blank\'" href="{URL}">{TEXT}</a>');

//Скриншот
define('THEME_SCREENSHOT', '<img class="screenshot" src="{URL}" alt="screenshot" />');

//Картинка ожидания
define('THEME_IMG_WAIT', '<img src="'.THEME_PATH.'/throbber.gif" alt="throbber" />');

//Всплывающие меню.
define('THEME_POPUPMENU_BOT', '<a class="bot_a" href="#" onclick="return jsmShowMenu({ID}, {MENU_NAME}, Array(), Array(\'{BOTID_FOR_URL}\'))">{BOTID}</a><div style="display:none;text-align:left" id="popupmenu{ID}"></div>');

//Работа с формой.
define('THEME_FORMPOST_BEGIN',        '<form method="post" id="{NAME}" action="{URL}"{JS_EVENTS}>');
define('THEME_FORMPOST_TO_NEW_BEGIN', '<form method="post" id="{NAME}" action=";{URL}"{JS_EVENTS}>');
define('THEME_FORMPOST_END',          '</form>');
define('THEME_FORMGET_BEGIN',         '<form method="get" id="{NAME}" action="{URL}"{JS_EVENTS}>');
define('THEME_FORMGET_TO_NEW_BEGIN',  '<form method="get" id="{NAME}" action=";{URL}"{JS_EVENTS}>');
define('THEME_FORMGET_END',           '</form>');
define('THEME_FORM_VALUE',            '<div style="display:none"><input type="hidden" name="{NAME}" value="{VALUE}" /></div>');

//Диалог.
define('THEME_DIALOG_BEGIN',                    '<table class="tbl1" style="width:{WIDTH}">');
define('THEME_DIALOG_END',                      '</table>');
define('THEME_DIALOG_TITLE',                    '<tr><td colspan="{COLUMNS_COUNT}" class="td_hdr" align="left">{TEXT}</td></tr>');
define('THEME_DIALOG_GROUP_BEGIN',              '<td colspan="{COLUMNS_COUNT}" valign="top"><table class="tbl1" width="100%">');
define('THEME_DIALOG_GROUP_END',                '</table></td>');
define('THEME_DIALOG_GROUP_TITLE',              '<tr><td colspan="{COLUMNS_COUNT}" class="td_hdr" align="left">{TEXT}</td></tr>');
define('THEME_DIALOG_ROW_BEGIN',                '<tr>');
define('THEME_DIALOG_ROW_END',                  '</tr>');
define('THEME_DIALOG_ITEM_LISTBOX_BEGIN',       '<select id="{NAME}" name="{NAME}" style="width:{WIDTH}">');
define('THEME_DIALOG_ITEM_LISTBOX_BEGIN_RO',    '<select id="{NAME}" name="{NAME}" style="width:{WIDTH}" disabled="disabled">');
define('THEME_DIALOG_ITEM_LISTBOX_END',         '</select>');
define('THEME_DIALOG_ITEM_LISTBOX_END_RO',      '</select>');
define('THEME_DIALOG_ITEM_LISTBOX_ITEM',        '<option value="{VALUE}">{TEXT}</option>');
define('THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR',    '<option value="{VALUE}" selected="selected">{TEXT}</option>');
define('THEME_DIALOG_ITEM_TEXT',                '<td align="left">{TEXT}</td>');
define('THEME_DIALOG_ITEM_TEXT_TOP',            '<td align="left" valign="top">{TEXT}</td>');
define('THEME_DIALOG_ITEM_WRAPTEXT',            '<td align="left" style="white-space:normal">{TEXT}</td>');
define('THEME_DIALOG_ITEM_MAXSPACE',            '<td align="left" style="width:100%">&#160;</td>');
define('THEME_DIALOG_ITEM_CHILD_BEGIN',         '<td colspan="{COLUMNS_COUNT}" valign="top" align="left">');
define('THEME_DIALOG_ITEM_CHILD_END',           '</td>');
define('THEME_DIALOG_ITEM_ERROR',               '<td align="left" class="error">{TEXT}</td>');
define('THEME_DIALOG_ITEM_SUCCESSED',           '<td align="left" class="success">{TEXT}</td>');
define('THEME_DIALOG_ITEM_EMPTY',               '<td>&#160;</td>');
define('THEME_DIALOG_ITEM_INPUT_PASSWORD',      '<td><input type="password" name="{NAME}" value="{VALUE}" maxlength="{MAX}" style="width:{WIDTH}" /></td>');
define('THEME_DIALOG_ITEM_INPUT_TEXT',          '<td><input type="text" name="{NAME}" value="{VALUE}" maxlength="{MAX}" style="width:{WIDTH}" /></td>');
define('THEME_DIALOG_ITEM_INPUT_TEXT_RO',       '<td><input type="text" name="{NAME}" value="{VALUE}" maxlength="{MAX}" style="width:{WIDTH}" readonly="readonly" /></td>');
define('THEME_DIALOG_ITEM_INPUT_TEXTAREA',      '<td><textarea name="{NAME}" rows="{ROWS}" cols="{COLS}" style="width:{WIDTH}">{TEXT}</textarea></td>');
define('THEME_DIALOG_ITEM_INPUT_TEXTAREA_RO',   '<td><textarea name="{NAME}" rows="{ROWS}" cols="{COLS}" style="width:{WIDTH}" readonly="readonly">{TEXT}</textarea></td>');
define('THEME_DIALOG_ITEM_INPUT_PASS',          '<td><input type="password" name="{NAME}" value="{VALUE}" maxlength="{MAX}" style="width:{WIDTH}" /></td>');
define('THEME_DIALOG_ITEM_INPUT_CHECKBOX_1',    '<td align="left" colspan="{COLUMNS_COUNT}"><input type="checkbox" name="{NAME}" value="{VALUE}"{JS_EVENTS} /></td>');
define('THEME_DIALOG_ITEM_INPUT_CHECKBOX_ON_1', '<td align="left" colspan="{COLUMNS_COUNT}"><input type="checkbox" name="{NAME}" value="{VALUE}" checked="checked" {JS_EVENTS} /></td>');
define('THEME_DIALOG_ITEM_INPUT_CHECKBOX_2',    '<td align="left" colspan="{COLUMNS_COUNT}"><input type="checkbox" name="{NAME}" value="{VALUE}"{JS_EVENTS} />&#160;{TEXT}</td>');
define('THEME_DIALOG_ITEM_INPUT_CHECKBOX_ON_2', '<td align="left" colspan="{COLUMNS_COUNT}"><input type="checkbox" name="{NAME}" value="{VALUE}" checked="checked" {JS_EVENTS} />&#160;{TEXT}</td>');
define('THEME_DIALOG_ITEM_INPUT_CHECKBOX_3',    '<input type="checkbox" name="{NAME}" value="{VALUE}"{JS_EVENTS} />');
define('THEME_DIALOG_ITEM_INPUT_CHECKBOX_ON_3', '<input type="checkbox" name="{NAME}" value="{VALUE}" checked="checked" {JS_EVENTS} />');
define('THEME_DIALOG_ITEM_ACTION_SUBMIT',       '<input type="submit" value="{TEXT}"{JS_EVENTS} />');
define('THEME_DIALOG_ITEM_ACTION_RESET',        '<input type="reset" value="{TEXT}"{JS_EVENTS} />');
define('THEME_DIALOG_ITEM_ACTION',              '<input type="button" value="{TEXT}"{JS_EVENTS} />');
define('THEME_DIALOG_ITEM_ACTION_SEPARATOR',    '&#160;|&#160;');
define('THEME_DIALOG_ACTIONLIST_BEGIN',         '<tr><td colspan="{COLUMNS_COUNT}" align="right">');
define('THEME_DIALOG_ACTIONLIST_END',           '</td></tr>');
define('THEME_DIALOG_ANCHOR',                   '<a href="{URL}">{TEXT}</a>');
define('THEME_DIALOG_ANCHOR_BLANK',             '<a href="{URL}" onclick="this.target=\'_blank\'">{TEXT}</a>');

//Список
define('THEME_LIST_BEGIN',                       '<table class="tbl1" style="width:{WIDTH}">');
define('THEME_LIST_END',                         '</table>');
define('THEME_LIST_TITLE',                       '<tr><td colspan="{COLUMNS_COUNT}" align="left" class="td_hdr">{TEXT}</td></tr>');
define('THEME_LIST_HEADER_L',                    '<td colspan="{COLUMNS_COUNT}" align="left" class="td_hdr" style="width:{WIDTH}">{TEXT}</td>');
define('THEME_LIST_HEADER_L_SORT',               '<td colspan="{COLUMNS_COUNT}" align="left" class="td_hdr" style="width:{WIDTH}"><a href="{URL}"{JS_EVENTS}>{TEXT}</a></td>');
define('THEME_LIST_HEADER_L_SORT_CUR_ASC',       '<td colspan="{COLUMNS_COUNT}" align="left" class="td_hdr" style="width:{WIDTH}">&#160;&#8593;&#160;<a href="{URL}"{JS_EVENTS}>{TEXT}</a></td>');
define('THEME_LIST_HEADER_L_SORT_CUR_DESC',      '<td colspan="{COLUMNS_COUNT}" align="left" class="td_hdr" style="width:{WIDTH}">&#160;&#8595;&#160;<a href="{URL}"{JS_EVENTS}>{TEXT}</a></td>');
define('THEME_LIST_HEADER_R',                    '<td colspan="{COLUMNS_COUNT}" align="right" class="td_hdr" style="width:{WIDTH}">{TEXT}</td>');
define('THEME_LIST_HEADER_R_SORT',               '<td colspan="{COLUMNS_COUNT}" align="right" class="td_hdr" style="width:{WIDTH}"><a href="{URL}"{JS_EVENTS}>{TEXT}</a></td>');
define('THEME_LIST_HEADER_R_SORT_CUR_ASC',       '<td colspan="{COLUMNS_COUNT}" align="right" class="td_hdr" style="width:{WIDTH}">&#8593;&#160;<a href="{URL}"{JS_EVENTS}>{TEXT}</a></td>');
define('THEME_LIST_HEADER_R_SORT_CUR_DESC',      '<td colspan="{COLUMNS_COUNT}" align="right" class="td_hdr" style="width:{WIDTH}">&#8595;&#160;<a href="{URL}"{JS_EVENTS}>{TEXT}</a></td>');
define('THEME_LIST_HEADER_CHECKBOX_1',           '<td colspan="{COLUMNS_COUNT}" align="left" class="td_hdr" style="width:{WIDTH}"><input type="checkbox" name="{NAME}" value="{VALUE}"{JS_EVENTS} /></td>');
define('THEME_LIST_HEADER_CHECKBOX_ON_1',        '<td colspan="{COLUMNS_COUNT}" align="left" class="td_hdr" style="width:{WIDTH}"><input type="checkbox" name="{NAME}" value="{VALUE}" checked="checked" {JS_EVENTS} /></td>');
define('THEME_LIST_ROW_BEGIN',                   '<tr>');
define('THEME_LIST_ROW_END',                     '</tr>');
define('THEME_LIST_ITEM_EMPTY_1',                '<td colspan="{COLUMNS_COUNT}" align="center" class="tdx1"><i>{TEXT}</i></td>');
define('THEME_LIST_ITEM_EMPTY_2',                '<td>&#160;</td>');
define('THEME_LIST_ITEM_PLAIN_U1',               '<td colspan="{COLUMNS_COUNT}" class="tdx1" align="left" style="width:{WIDTH}"><pre>{TEXT}</pre></td>');
define('THEME_LIST_ITEM_PLAIN_U2',               '<td colspan="{COLUMNS_COUNT}" class="tdx2" align="left" style="width:{WIDTH}"><pre>{TEXT}</pre></td>');
define('THEME_LIST_ITEM_LTEXT_U1',               '<td class="tdx1" align="left" style="width:{WIDTH}">{TEXT}</td>');
define('THEME_LIST_ITEM_LTEXT_U2',               '<td class="tdx2" align="left" style="width:{WIDTH}">{TEXT}</td>');
define('THEME_LIST_ITEM_RTEXT_U1',               '<td class="tdx1" align="right" style="width:{WIDTH}">{TEXT}</td>');
define('THEME_LIST_ITEM_RTEXT_U2',               '<td class="tdx2" align="right" style="width:{WIDTH}">{TEXT}</td>');
define('THEME_LIST_ITEM_INPUT_CHECKBOX_1_U1',    '<td class="tdx1" align="left" style="width:1%"><input type="checkbox" name="{NAME}" value="{VALUE}"{JS_EVENTS} /></td>');
define('THEME_LIST_ITEM_INPUT_CHECKBOX_ON_1_U1', '<td class="tdx1" align="left" style="width:1%"><input type="checkbox" name="{NAME}" value="{VALUE}" checked="checked" {JS_EVENTS} /></td>');
define('THEME_LIST_ITEM_INPUT_CHECKBOX_1_U2',    '<td class="tdx2" align="left" style="width:1%"><input type="checkbox" name="{NAME}" value="{VALUE}"{JS_EVENTS} /></td>');
define('THEME_LIST_ITEM_INPUT_CHECKBOX_ON_1_U2', '<td class="tdx2" align="left" style="width:1%"><input type="checkbox" name="{NAME}" value="{VALUE}" checked="checked" {JS_EVENTS} /></td>');
define('THEME_LIST_ITEM_LISTBOX_U1_BEGIN',       '<td class="tdx1" align="left"><select name="{NAME}" style="width:{WIDTH}">');
define('THEME_LIST_ITEM_LISTBOX_U1_END',         '</select></td>');
define('THEME_LIST_ITEM_LISTBOX_U2_BEGIN',       '<td class="tdx2" align="left"><select name="{NAME}" style="width:{WIDTH}">');
define('THEME_LIST_ITEM_LISTBOX_U2_END',         '</select></td>');
define('THEME_LIST_ITEM_LISTBOX_ITEM',           '<option value="{VALUE}">{TEXT}</option>');
define('THEME_LIST_ITEM_LISTBOX_ITEM_CUR',       '<option value="{VALUE}" selected="selected">{TEXT}</option>');
define('THEME_LIST_ITEM_INPUT_TEXT_U1',          '<td class="tdx1" align="left"><input type="text" name="{NAME}" value="{VALUE}" maxlength="{MAX}" style="width:{WIDTH}" /></td>');
define('THEME_LIST_ITEM_INPUT_TEXT_U2',          '<td class="tdx1" align="left"><input type="text" name="{NAME}" value="{VALUE}" maxlength="{MAX}" style="width:{WIDTH}" /></td>');
define('THEME_LIST_ANCHOR',                      '<a href="{URL}">{TEXT}</a>');
define('THEME_LIST_ANCHOR_BLANK',                '<a href="{URL}" onclick="this.target=\'_blank\'">{TEXT}</a>');

///////////////////////////////////////////////////////////////////////////////
// Управление темой.
///////////////////////////////////////////////////////////////////////////////

/*
  Начало вывода кода.
  
  IN $subtitle   - string, подзаголовок страницы.
  IN $js_script  - string, допольнителный JavaScript скрипт, или 0, если он не нужен.
  IN $popup_menu - string, данные для всплывающего меню, или 0, если оно не нужно.
  IN $body_events - string, JavaScript-события для документа, или 0, если оно не нужно.
*/
function ThemeBegin($subtitle, $js_script, $popup_menu, $body_events)
{
  global $_MAINMENU,  //Структура главного меню.
         $_USER_DATA; //Все столбцы таблицы cp_users текущего юзера.
  
  //Добавление JavaScript.
  $javascript = '';
  $body_js_events = $body_events === 0 ? '' : $body_events;
  
  if($js_script != '')$javascript .= str_replace('{SCRIPT}', $js_script, THEME_JAVASCRIPT_BODY);
  if($popup_menu != '')
  {
    $javascript .= str_replace('{SCRIPT}', $popup_menu, THEME_JAVASCRIPT_BODY).str_replace('{PATH}', THEME_PATH.'/popupmenu.js', THEME_JAVASCRIPT_EXTERNAL);
    $body_js_events .= ' onclick="jsmHideLastMenu()"';
  }
  
  //Добавление главного меню.
  $mainmenu = '';  
  foreach($_MAINMENU as $item)
  {
    if($item[0] === 0)$mainmenu .= str_replace('{TITLE}', $item[1], THEME_MAINMENU_SUBHEADER);
    else $mainmenu .= str_replace(array('{URL}', '{TEXT}'), array(QUERY_STRING_BLANK_HTML.$item[0], $item[1]), strcmp(CURRENT_MODULE, $item[0]) === 0 ? THEME_MAINMENU_ITEM_CURRENT : THEME_MAINMENU_ITEM);
  }
  $mainmenu .= THEME_MAINMENU_SEPARATOR.str_replace(array('{URL}', '{TEXT}'), array(QUERY_STRING_BLANK_HTML.'logout', LNG_MM_LOGOUT), THEME_MAINMENU_ITEM);
  
  header('Content-Type: '.THEME_CONTENT_TYPE.'; charset=utf-8');
  HTTPNoCacheHeaders();
  
  echo str_replace(array('{TITLE}', '{SUBTITLE}', '{THEME_HTTP_PATH}', '{JAVASCRIPT}', '{BODY_JS_EVENTS}', '{MAINMENU}', '{INFO_TITLE}', '{INFO_USERNAME_TITLE}', '{INFO_USERNAME}',   '{INFO_DATE_TITLE}', '{INFO_DATE}',                         '{INFO_TIME_TITLE}', '{INFO_TIME}'),
                   array(LNG_TITLE,  $subtitle,     THEME_PATH,           $javascript,      $body_js_events,   $mainmenu,    LNG_INFO,       LNG_INFO_USERNAME,       htmlentities_ex($_USER_DATA['name']), LNG_INFO_DATE,       htmlentities_ex(gmdate(LNG_FORMAT_DATE, CURRENT_TIME)), LNG_INFO_TIME,       htmlentities_ex(gmdate(LNG_FORMAT_TIME, CURRENT_TIME))),
                   file_get_contents(THEME_PATH.'/header.html'));
}

/*
  Конец вывода кода.
*/  
function ThemeEnd()
{
  echo file_get_contents(THEME_PATH.'/footer.html');
}

/*
  Вывода кода для небольших страниц.
  
  IN $subtitle    - string, подзаголовок страницы.
  IN $data        - string, содержимое сраницы.
  IN $js_script   - string, допольнителный JavaScript скрипт, или 0, если он не нужен.
  IN $popup_menu  - string, данные для всплывающего меню, или 0, если оно не нужено.
  IN $body_events - string, JavaScript-события для документа, или 0, если оно не нужно.
*/
function ThemeSmall($subtitle, $data, $js_script, $popup_menu, $body_events)
{
  //Добавление JavaScript.
  $javascript = '';
  $body_js_events = $body_events === 0 ? '' : $body_events;
  
  if($js_script != '')$javascript .= str_replace('{SCRIPT}', $js_script, THEME_JAVASCRIPT_BODY);
  if($popup_menu != '')
  {
    $javascript .= str_replace('{SCRIPT}', $popup_menu, THEME_JAVASCRIPT_BODY).str_replace('{PATH}', THEME_PATH.'/popupmenu.js', THEME_JAVASCRIPT_EXTERNAL);
    $body_js_events .= ' onclick="jsmHideLastMenu()"';
  }

  header('Content-Type: '.THEME_CONTENT_TYPE.'; charset=utf-8');  
  HTTPNoCacheHeaders();
  
  echo str_replace(array('{SUBTITLE}', '{THEME_HTTP_PATH}', '{JAVASCRIPT}', '{BODY_JS_EVENTS}', '{BODY}'),
                   array($subtitle,     THEME_PATH,           $javascript,      $body_js_events,   $data),
                   file_get_contents(THEME_PATH.'/small.html'));
}

/*
  Вывод сообщения об MySQL ошибки и выход.
*/
function ThemeMySQLError()
{
  ThemeSmall('MySQL error', mysql_error_ex(), 0, 0, 0);
  die();
}

/*
  Вывод сообщения об ошибки и выход.
  
  IN $string - string, сообщение об ошибки.
*/
function ThemeFatalError($string)
{
  ThemeSmall('Fatal error', $string, 0, 0, 0);
  die();
}


/*
  Вывод списка номеров страниц.
  
  IN $list         - array, массив массивов номеров страниц.
  IN $js_to_first - string, JavaScript на первую страницу, или 0.
  IN $js_to_prev  - string, JavaScript на предидущию страницу, или 0.
  IN $js_to_last  - string, JavaScript на последнию страницу, или 0.
  IN $js_to_next  - string, JavaScript на следующию страницу, или 0.
  
  Return           - string, список номеров страниц.
*/
function ThemePageList($list, $js_to_first, $js_to_prev, $js_to_last, $js_to_next)
{ 
  $data = '<table class="tbl1" style="width:100%"><tr><td align="center">'.LNG_PAGELIST_TITLE.'&#160;';
  if($js_to_first !== 0)$data .= '[<a href="#" onclick="'.$js_to_first.'">'.LNG_PAGELIST_FIRST.'</a>]';
  if($js_to_prev  !== 0)
  {
    if($js_to_first !== 0)$data .= '&#160;';
    $data .= '[<a href="#" onclick="'.$js_to_prev.'">'.LNG_PAGELIST_PREV.'</a>]';
  }
  
  foreach($list as $v)
  {
    if($v[0] === 0)$data .= '&#160;..&#160;';
    else if($v[1] === 0)$data .= '&#160;<b>['.$v[0].']</b>&#160;';
    else $data .= '&#160;<a href="#" onclick="'.$v[1].'">'.$v[0].'</a>&#160;';
  }
  
  if($js_to_next !== 0)$data .= '[<a href="#" onclick="'.$js_to_next.'">'.LNG_PAGELIST_NEXT.'</a>]';
  if($js_to_last !== 0)
  {
    if($js_to_next !== 0)$data .= '&#160;';
    $data .= '[<a href="#" onclick="'.$js_to_last.'">'.LNG_PAGELIST_LAST.'</a>]';
  }
  $data .= '</td></tr></table>';
  
  return $data;
}
?>