<?php if(!defined('__CP__'))die();
define('LNG_REPORTS', 'Поиск в базе данных');

define('LNG_REPORTS_BOTSACTION', 'Действие над ботами:');

//Фильтр.
define('LNG_REPORTS_FILTER_TITLE',      'Фильтр');

define('LNG_REPORTS_FILTER_DATE_P1',    'Искать с даты (дд.мм):');
define('LNG_REPORTS_FILTER_DATE_P2',    'по дату:');
define('LNG_REPORTS_FILTER_DATE_P3',    '');

define('LNG_REPORTS_FILTER_BOTS',       'Боты:');
define('LNG_REPORTS_FILTER_BOTNETS',    'Ботнеты:');
define('LNG_REPORTS_FILTER_IPS',        'IP-адреса:');
define('LNG_REPORTS_FILTER_COUNTRIES',  'Страны:');
define('LNG_REPORTS_FILTER_QUERY',      'Строка поиска:');
define('LNG_REPORTS_FILTER_REPORTTYPE', 'Тип отчета:');
define('LNG_REPORTS_FILTER_CS',         'С учетом регистра.');
define('LNG_REPORTS_FILTER_GROUPQUERY', 'Исключить повтор отчетов (в пределах одного дня).');
define('LNG_REPORTS_FILTER_NONAMES',    'Отображать только отчеты (не отображать имена ботов).');
define('LNG_REPORTS_FILTER_PLAIN',      'Вывод в текстовом режиме (text/plain).');

define('LNG_REPORTS_FILTER_ALL',        '--');

define('LNG_REPORTS_FILTER_RESET',      'Сброс формы');
define('LNG_REPORTS_FILTER_SUBMIT',     'Поиск');
define('LNG_REPORTS_FILTER_REMOVE',     'Удалить');
define('LNG_REPORTS_FILTER_REMOVE_Q',   'Вы действительно хотите удалить отчета по текущему фильтру?');

define('LNG_REPORTS_RESULT', 'Результат:');

define('LNG_REPORTS_DATE_EMPTY',     'Указанная дата не найдена.');
define('LNG_REPORTS_DATE_NOREPORTS', 'По указанному фильтру отчетов на эту дату не найдено.');
define('LNG_REPORTS_DATE_ERROR',     'ОШИБКА!');
define('LNG_REPORTS_DATE_REMOVED',   'Удалено %u записей.');
define('LNG_REPORTS_DATE_DROPPED',   'Таблица уничтожена.');

define('LNG_REPORTS_VIEW_NOT_EXISTS', 'Отчет не найден.');
define('LNG_REPORTS_VIEW_TITLE',      'Просмотр отчета');
define('LNG_REPORTS_VIEW_TITLE2',     'Просмотр отчета (%s, %s байт)');
define('LNG_REPORTS_VIEW_BOTID',      'Bot ID:');
define('LNG_REPORTS_VIEW_BOTNET',     'Ботнет:');
define('LNG_REPORTS_VIEW_VERSION',    'Версия:');
define('LNG_REPORTS_VIEW_OS',         'Версия ОС:');
define('LNG_REPORTS_VIEW_OSLANG',     'Язык ОС:');
define('LNG_REPORTS_VIEW_TIME',       'Локальное время:');
define('LNG_REPORTS_VIEW_TIMEBIAS',   'GMT:');
define('LNG_REPORTS_VIEW_TICK',       'Время сессии:');
define('LNG_REPORTS_VIEW_RTIME',      'Время отчета:');
define('LNG_REPORTS_VIEW_COUNTRY',    'Страна:');
define('LNG_REPORTS_VIEW_IPV4',       'IPv4:');
define('LNG_REPORTS_VIEW_COMMENTS',   'Комментарий к боту:');
define('LNG_REPORTS_VIEW_USED',       'В списке использованных:');
define('LNG_REPORTS_VIEW_PROCNAME',   'Процесс:');
define('LNG_REPORTS_VIEW_SOURCE',     'Источник:');
define('LNG_REPORTS_VIEW_TYPE',       'Тип:');
define('LNG_REPORTS_VIEW_SIZE',       'Размер (байты):');
define('LNG_REPORTS_VIEW_DOWNLOAD',   'Скачать файл "%s" (%s байт).');
?>