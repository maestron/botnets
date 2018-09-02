<?php if(!defined('__CP__'))die();
define('LNG_REPORTS', 'Search in database');

define('LNG_REPORTS_BOTSACTION', 'Bots action:');

//Фильтр.
define('LNG_REPORTS_FILTER_TITLE',      'Filter');

define('LNG_REPORTS_FILTER_DATE_P1',    'Search from date (dd.mm):');
define('LNG_REPORTS_FILTER_DATE_P2',    'to date:');
define('LNG_REPORTS_FILTER_DATE_P3',    '');

define('LNG_REPORTS_FILTER_BOTS',       'Bots:');
define('LNG_REPORTS_FILTER_BOTNETS',    'Botnets:');
define('LNG_REPORTS_FILTER_IPS',        'IP-addresses:');
define('LNG_REPORTS_FILTER_COUNTRIES',  'Countries:');
define('LNG_REPORTS_FILTER_QUERY',      'Search string:');
define('LNG_REPORTS_FILTER_REPORTTYPE', 'Type of report:');
define('LNG_REPORTS_FILTER_CS',         'Case sensitive.');
define('LNG_REPORTS_FILTER_GROUPQUERY', 'Exclude retries of contents (for one day only).');
define('LNG_REPORTS_FILTER_NONAMES',    'Show only reports (don\'t show names of bots).');
define('LNG_REPORTS_FILTER_PLAIN',      'Show as text (text/plain).');

define('LNG_REPORTS_FILTER_ALL',        '--');

define('LNG_REPORTS_FILTER_RESET',      'Reset form');
define('LNG_REPORTS_FILTER_SUBMIT',     'Search');
define('LNG_REPORTS_FILTER_REMOVE',     'Remove');
define('LNG_REPORTS_FILTER_REMOVE_Q',   'You really want remove reports using current search filter?');

define('LNG_REPORTS_RESULT', 'Result:');

define('LNG_REPORTS_DATE_EMPTY',     'Selected date not founded.');
define('LNG_REPORTS_DATE_NOREPORTS', 'Reports for this date not founded.');
define('LNG_REPORTS_DATE_ERROR',     'ERROR!');
define('LNG_REPORTS_DATE_REMOVED',   'Removed %u rows.');
define('LNG_REPORTS_DATE_DROPPED',   'Table dropped.');

define('LNG_REPORTS_VIEW_NOT_EXISTS', 'Report not exists.');
define('LNG_REPORTS_VIEW_TITLE',      'View report');
define('LNG_REPORTS_VIEW_TITLE2',     'View report (%s, %s bytes)');
define('LNG_REPORTS_VIEW_BOTID',      'Bot ID:');
define('LNG_REPORTS_VIEW_BOTNET',     'Botnet:');
define('LNG_REPORTS_VIEW_VERSION',    'Version:');
define('LNG_REPORTS_VIEW_OS',         'OS Version:');
define('LNG_REPORTS_VIEW_OSLANG',     'OS Language:');
define('LNG_REPORTS_VIEW_TIME',       'Local time:');
define('LNG_REPORTS_VIEW_TIMEBIAS',   'GMT:');
define('LNG_REPORTS_VIEW_TICK',       'Session time:');
define('LNG_REPORTS_VIEW_RTIME',      'Report time:');
define('LNG_REPORTS_VIEW_COUNTRY',    'Country:');
define('LNG_REPORTS_VIEW_IPV4',       'IPv4:');
define('LNG_REPORTS_VIEW_COMMENTS',   'Comments for bot:');
define('LNG_REPORTS_VIEW_USED',       'In the list of used:');
define('LNG_REPORTS_VIEW_PROCNAME',   'Process name:');
define('LNG_REPORTS_VIEW_SOURCE',     'Source:');
define('LNG_REPORTS_VIEW_TYPE',       'Type:');
define('LNG_REPORTS_VIEW_SIZE',       'Size (bytes):');
define('LNG_REPORTS_VIEW_DOWNLOAD',   'Download file "%s" (%s bytes).');
?>