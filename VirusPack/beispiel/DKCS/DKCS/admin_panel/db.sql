#
# Структура таблицы `stat`
#

CREATE TABLE stat (
  nick varchar(50) NOT NULL default '',
  ip varchar(15) default NULL,
  time varchar(20) default NULL,
  command varchar(255) default NULL,
  info text,
  country varchar(255) default NULL
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Структура таблицы `tasks`
#

CREATE TABLE tasks (
  nick varchar(50) NOT NULL default '',
  command varchar(255) NOT NULL default '',
  bnum int(11) NOT NULL default '0',
  executed int(11) NOT NULL default '0',
  country varchar(255) default NULL
) TYPE=MyISAM;