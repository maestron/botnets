<?php if(!defined('__CP__'))die();

define('LNG_TITLE',          'CP');
define('LNG_YES',            'Да');
define('LNG_NO',             'Нет');
define('LNG_ACCESS_DEFINED', 'Доступ запрещен.');
define('LNG_ACTION_APPLY',   '&#62;&#62;');

//Форматы данных.
define('LNG_FORMAT_DATE',   'd.m.Y');
define('LNG_FORMAT_TIME',   'H:i:s');
define('LNG_FORMAT_DT',     'd.m.Y H:i:s');
define('LNG_FORMAT_NOTIME', '--:--:--');

//Список ботнетов.
define('LNG_BOTNET_ALL',   '[Все]');
define('LNG_BOTNET_APPLY', '&#62;&#62;');

//Список страниц.
define('LNG_PAGELIST_TITLE', 'Страницы:');
define('LNG_PAGELIST_NEXT',  'Вперед');
define('LNG_PAGELIST_PREV',  'Назад');
define('LNG_PAGELIST_FIRST', '&#171;');
define('LNG_PAGELIST_LAST',  '&#187;');

//Меню действий.
define('LNG_MBA_SEPARATOR',         '--------------------------------------');

define('LNG_MBA_FULLINFO',        'Полная информация');
define('LNG_MBA_FULLINFOSS',      'Полная информация + скриншот');
define('LNG_MBA_TODAY_DBREPORTS', 'Отчеты за сегодня');
define('LNG_MBA_WEEK_DBREPORTS',  'Отчеты за последние 7 дней');
define('LNG_MBA_FILES',           'Файлы');

define('LNG_MBA_REMOVE',          'Удалить из базы данных');
define('LNG_MBA_REMOVE_REPORTS',  'Удалить из базы данных, включая отчеты');

define('LNG_MBA_PORT_SOCKS',      'Проверить сокс');
define('LNG_MBA_NEWSCRIPT',       'Создать скрипт');

define('LNG_BA_FULLINFO_TITLE',       'Полная информация о ботах');
define('LNG_BA_FULLINFO_EMPTY',       '-- Информация отсутствует --');
define('LNG_BA_FULLINFO_BOTID',       'Bot ID:');
define('LNG_BA_FULLINFO_BOTNET',      'Ботнет:');
define('LNG_BA_FULLINFO_VERSION',     'Версия:');
define('LNG_BA_FULLINFO_OS',          'Версия ОС:');
define('LNG_BA_FULLINFO_OSLANG',      'Язык ОС:');
define('LNG_BA_FULLINFO_TIMEBIAS',    'GMT:');
define('LNG_BA_FULLINFO_COUNTRY',     'Страна:');
define('LNG_BA_FULLINFO_IPV4',        'IPv4:');
define('LNG_BA_FULLINFO_LATENCY',     'Лаг:');
define('LNG_BA_FULLINFO_PORT_S1',     'Socks/LC порт:');
define('LNG_BA_FULLINFO_TFIRST',      'Время первого отчета:');
define('LNG_BA_FULLINFO_TLAST',       'Время последнего отчета:');
define('LNG_BA_FULLINFO_TONLINE',     'Время в онлайн:');
define('LNG_BA_FULLINFO_INSTALL',     'В списке инсталлов:');
define('LNG_BA_FULLINFO_USED',        'В списке использованных:');
define('LNG_BA_FULLINFO_COMMENTS',    'Комментарий:');
define('LNG_BA_FULLINFO_SCREENSHOT',  'Скриншот:');
define('LNG_BA_FULLINFO_ACTION_SAVE', 'Сохранить');

define('LNG_BA_REMOVE_TITLE',    'Удаление ботов из БД');
define('LNG_BA_REMOVE_Q1',       'Вы действительно хотите удалить выбранных ботов из БД (%u шт.)?');
define('LNG_BA_REMOVE_Q2',       'Вы действительно хотите удалить выбранных ботов из БД (%u шт.), включая отчеты?');
define('LNG_BA_REMOVE_ABORTED',  'Удаление отменено пользователем.');
define('LNG_BA_REMOVE_REMOVED',  'Удалено %u записей.');
define('LNG_BA_REMOVE_FREMOVED', 'Удалено.');
define('LNG_BA_REMOVE_FERROR',   'ОШИБКА.');

define('LNG_BA_PORT_SOCKS_TITLE',     'Проверка соксов');
define('LNG_BA_PORT_SOCKS_CHECKING',  'ПРОВЕРКА...');
define('LNG_BA_PORT_SOCKS_SUCCESS',   'ДОСТУПЕН');
define('LNG_BA_PORT_SOCKS_FAILED',    'НЕ ДОСТУПЕН');
define('LNG_BA_PORT_SOCKS_ERROR',     'ОШИБКА!');

//Информация.
define('LNG_INFO',          'Информация:');
define('LNG_INFO_USERNAME', 'Пользователь:');
define('LNG_INFO_DATE',     'GMT дата:');
define('LNG_INFO_TIME',     'GMT время:');

//Главное меню.
define('LNG_MM_STATS',             'Статистика:');
define('LNG_MM_STATS_MAIN',        'Общая');
define('LNG_MM_STATS_OS',          'ОС');

define('LNG_MM_BOTNET',            'Ботнет:');
define('LNG_MM_BOTNET_BOTS',       'Боты');
define('LNG_MM_BOTNET_SCRIPTS',    'Скрипты');

define('LNG_MM_REPORTS',           'Отчеты:');
define('LNG_MM_REPORTS_DB',        'Поиск в базе данных');
define('LNG_MM_REPORTS_FILES',     'Поиск в файлах');

define('LNG_MM_SYSTEM',            'Система:');
define('LNG_MM_SYSTEM_INFO',       'Информация');
define('LNG_MM_SYSTEM_OPTIONS',    'Параметры');
define('LNG_MM_SYSTEM_USER',       'Пользователь');
define('LNG_MM_SYSTEM_USERS',      'Пользователи');

define('LNG_MM_LOGOUT',            'Выход');

//Типы отчетов.
define('LNG_BLT_UNKNOWN',           'Неизвестный формат');
define('LNG_BLT_PROTECTED_STORAGE', 'Protected Storage');
define('LNG_BLT_IE_COOKIES',        'Кукисы IE');
define('LNG_BLT_FILE',              'Файл');
define('LNG_BLT_HTTPX_REQUEST',     'HTTP или HTTPS запрос');
define('LNG_BLT_HTTP_REQUEST',      'HTTP запрос');
define('LNG_BLT_HTTPS_REQUEST',     'HTTPS запрос');
define('LNG_BLT_LOGIN_FTP',         'FTP данные');
define('LNG_BLT_LOGIN_POP3',        'POP3 данные');
define('LNG_BLT_GRABBED_X',         'Любые захваченные данные');
define('LNG_BLT_GRABBED_UI',        'Захваченные данные [UI]');
define('LNG_BLT_GRABBED_HTTP',      'Захваченные данные [HTTP(S)]');
define('LNG_BLT_GRABBED_WSOCKET',   'Захваченные данные [WinSocket]');
define('LNG_BLT_GRABBED_OTHER',     'Захваченные данные [Other]');
?>