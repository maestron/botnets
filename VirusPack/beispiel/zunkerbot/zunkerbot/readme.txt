[ZUnker 1.4.5]

Package Contents :
. folder with your files.
. file for the installation of SQL tables.
. You script (zc.php).
. redmi.

Setting
: For the panel must have the following
: MySQL 4.1. + (Not below JAMin 4.1);

PHP 4.3 + (RNR works as a module P.S. almost all hostingah it works that way.) .

After copying files to the directory server, you will need to create a framework for this to create a lo (or you can use phpMyAdmin, MyCC or others;

If you have a different name then need to change line

$ BOT_DBNAME = 'lo'; Mycommon.php file), run the file in unker.sql sql-zaprose () Set a password for your user and connect to MySQL, for the edit mycommon.php, and the following lines :

/ / For the user (by that name you will logs on the cover.)
$ user = 'root';
$ pass ='123 ';

/ / To connect to the database
$ BOT_DBHOST = 'localhost';
$ BOT_DBLOGIN = 'root';
$ BOT_DBPASS ='';

when installed on Linus-server ensure that the right to RNR files set properly.

If not, or scripts can be executed correctly put right, equal 644. (chmod / zu - R 0644 where. " this is your current derektoriya).

Jobs : After the visit to the bar. http://vash-xost.com/zu zalogintes using your login and password.

Menu :
[statistics] -statistika

[Global] object bot (loaderam), new country.
ranking countries, the number of Buddy, their persistence, version update.

[Downloaded files] on busy files, sorted by country.

[Time statistics] by the time of [Downloaded files] to skachanyh files.

(these statistics only show the number skachanyh loaderom files for the year-month-day, hour).

[Bot `s raports] - to conclude stir.
[Messages sent] on otoslanym reported.
[control] - upravlyalka bots. Appointment assignments search.
[Unker] - management functions loadera

[Zupacha]

[Control] - management rassilki Zupacha [Template Editor-editor template distribution Zupacha

[help] - this file. conv. signs. botnet, a network kompyuterov-serverov.

... ... ...

F.A.Q

-Kakaya difference between Suffix and Preffix Editor templates?

A : In fact, there is the opportunity to address select the type prikripleniya your message (from a template, etc.) Preffix letter at the beginning and end of the letter Suffix, respectively.

For IM only type prikripleniya Preffix.
Bulletin create a template for IM and create for appointment as it works when you ask for the job?

A : After the posting of the template, make the attribution of that template in the job;

Bot retrieves a list of messages and makes rassyl, and he makes SLUCHAYNUYU sample of these reports. If you make a change in the pattern already assigned task, this template will again be downloaded IRC.

moment I already have Panel but earlier versions as update it to version 1.3.2?

A : To begin, you will need to create a 3 new tables in a database, code can be placed in a file unker.sql, called it stat_down, stat_bot_rap and task_single then be Rebuild applies downfiles table. Then simply replace all the files on your files new version.

In doing so, remember to edit applies mycommon.php otherwise panel may not work with the eye.

Fauna ask urly for jumps loaderami?
A : Urly set in a large box under "Url` s to load.

" Each new url must be put in a new line, that is, after each, must press Enter if given only one url, Enter rid NOT need.

-Skolko can ask urlov?

A : What you want, in reasonable measures. thing is the word [TASK] instead of country code?

A : This means that the country can not be used for new jobs because already she has an active job to appoint a new task is to remove old.

-Pochemu when I clicked on the job "delete", I have gone stata for files uploaded to the United States.

A : This was done to avoid conflicts with characters instalov and filenames.

- Why, when the Count to Install put a value of 2, urlov put 2 in the figure 4.

A : If you checked Sum. , then the panel will multiply the number urlov at Number instalov thus enjoy equal number for each urla.

- Why when the job is a country All other countries are not doing downloads.

A : The fact is that a download for all countries, the priority is given only to this target. Fauna calculated the percentage living stir?

A : The number of reports a day, the number stir. evaluates range between Kyrgyzstan.

-Today new bots : 1040All New bot today : 56 v 4em raznica?

A : The difference is that the first number of a range of time ie of a range between 34234234 and 3578666 (Unix format, the number of seconds from 1.01.1970), and if the first rap. falls on the range, then considered.

Second is the number (day, month, year), those. chosen to statistics, only boots, which further in the number of the second meter stable wedlock.
it is not dependent server to work with ranges of time.

-Posle click "Clear global"

I ochistilasya table bots, it is critical for botneta?

A : none, living place, all at otreportyat, and the number of rows in the table right track, not only otreportyat dead overshoes and it is logical Smilie vobschem you can see the real situation in botnetom.

Detained want to make single download, which I take CompID?

A : Search Vozpolzuetes form of BOT, it you can otikskat BOT for part CompID or IP, the search results, click on the green cross, Eid bots automatically go down the Insert CompID (Single load).

To do mass loading box * should be empty.

... ... ...

History Versions.

The new 1.4.5 -Ozhivshaya primary stata.
"Now there is no need to click refresh to see new data. you can set the file mycommon.php, parameter $ STAT_REFRESH in milisekundah (ie 5000 is 5 seconds, etc.) .

I note that page is reloaded, updated statistics only.

-Pri typed text in the template below, you can see how the text will look at the work.

There are three examples :
IM (icq, aim etc.) and mail \ forums \ vebpochta of suffixes and prefixes.

-Redaktirovat masovye assignments Loadere.

The new 1.4.4 -Dobavlena opportunity to work with web forums (phpbb, VBulletin) and web page (about airport popular servers).

Your message down to the user's communication method sufiksa or prefix (of your choice). The forums are two ways to add : a new thread, in response to the topic.

The web mail it works when a user sends a message writte in the browser window. -Dobavlen protocol for Spam stir.

Now, for all that send the wrong place, spam user computers you can add a personal message to spam-pismam. Statistics for each web e-mail service and forum.

Statistics on the rassyla communications.
-Sovmestimost last MuSQL new 1.4.3
-Vozmozhnost given client statistics zagruzhenym files and countries [T] minor glitches.

The new 1.4.2
-Shablony for distribution -Perepisan protocol.

Statistics for Zupacha.

The new 1.4.1
-Dobavlenny protocols

: Yahoo! IM Google Talk Aol New AIM 1.4.0
-dobavnenno office for shots "Zupacha"

-upravlyalka written technology ajax.
-Otsylka text on Yahoo!

IM -Krome http autentefikatsii add a simple veb-autentifikatsiyu.

(polezono to those php works as cgi-shlyuz)

New

-sovmestimost 1.3.9 with the latest version loadera; now the minimum version loadera to work with the panel -- 1.0.8. , in the statistics on the use of technology antivirusam ajax.

The new 1.3.5
-statistika on antivirusam. Ratings countries.

The new 1.3.3
-sovmestimost with New php5 1.3.2
-poisk on bots. aside a personal mission to the BOT.

aside ochitit global statistics from the bot [Global].

o interface improvements.

The new 1.3.1
-statistika to conclude Buddy, in time.
-podsvetka page. The new 1.3.0
-statistika time for skachanyh files.

---------------------------------------- -------------------

Conditional duties.

The author of the script has no (legal, physical or moral) responsibility for vozmozhnny prichenneny detriment of the software product. (unless such incidents recorded nebylo) Programny product designed exclusively for educational purposes. Set Uker you use exclusively at your own risk. 
 
 Report to moderator    Logged  
 
 
 
claire 
Newbie

Posts: 2


    Re: ZUnker 1.4.5 Source + Download 
? Reply #1 on: August 11, 2007, 06:51:14 AM ? Quote  

--------------------------------------------------------------------------------
hey this is great thank you, however the subject says 1.4.5 and the downloads are 1.4.3 and 1.4.4.  was that a typo or did i miss a link?  thanks for sharing stuff like this i for one appreciate it! 
 
 Report to moderator    Logged  
 
 
 
