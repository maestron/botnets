<?php

class Browser {

	function identification($a_browser = false, $a_version = false, $name = false){

		$browser_list = array('msie', 'firefox', 'safari', 'opera', 'chrome');
		$user_browser = strtolower($_SERVER['HTTP_USER_AGENT']);
		$this_version = $this_browser = '';

		foreach ($browser_list as $row){
			$row = ($a_browser !== false) ? $a_browser : $row;
			$n = stristr($user_browser, $row);
			if (!$n || !empty($this_browser)) continue;
			$this_browser = $row;
			$j = strpos($user_browser, $row) + strlen($row) + 1;
			for (; $j <= strlen($user_browser); $j++){
				$s = trim(substr($user_browser, $j, 1));
				if ($s != ";"){
					$this_version .= $s;
				}
				if ($s === '') break;
			}
		}

		if ($a_browser !== false){
			$ret = false;
			if (strtolower($a_browser) == $this_browser){
				$ret = true;
				if ($a_version !== false && !empty($this_version)){
					$a_sign = explode(' ', $a_version);
					if (version_compare($this_version, $a_sign[1], $a_sign[0]) === false){
						$ret = false;
					}
				}
			}
			return $ret;
		}

		$this_platform = 'OTHER';
		$this_platformversion = 'OTHER';
		if (strpos($user_browser, 'linux')){
			$this_platform = 'LINUX';
		} elseif (strpos($user_browser, 'macintosh') || strpos($user_browser, 'mac platform x')){
			$this_platform = 'MAC';
		} elseif (strpos($user_browser, 'windows') || strpos($user_browser, 'win32')){
			if (strstr($user_browser, 'nt 6.1')){
				$this_platform = 'WIN7';
			} elseif (strstr($user_browser, 'nt 6.0') || strstr($user_browser, 'vista')){
				$this_platform = 'VISTA';
			} elseif (strstr($user_browser, 'nt 5.1') || strstr($user_browser, 'xp')){
				$this_platform = 'XP';
			} elseif (strstr($user_browser, 'nt 5.2') || strstr($user_browser, '2003')){
				$this_platform = '2003';
			} elseif (strstr($user_browser, 'nt 5') || strstr($user_browser, '2000')){
				$this_platform = '2000';
			} elseif ((strstr( $user_browser, '9x 4.9')) || ( strstr($user_browser, 'me'))){
				$this_platform = 'ME';
			} elseif (strstr($user_browser, '98')) {
				$this_platform = '98';
			} elseif (strstr($user_browser, '95')){
				$this_platform = '95';
			}
		}

		if ($name !== false){
			return $this_browser . ' ' . $this_version;
		}
   
		return array(
			"browser"					=> strtoupper($this_browser),
			"browser_version"	=> $this_version,
			"platform"					=> $this_platform,
			"platform_version"	=> $this_platformversion
		);

	}

}


/*
print_r(_browser()); // return array of browser data
var_dump(_browser('firefox')); // return true if using firefox
var_dump(_browser('msie', '>= 7.0')); // return true if using IE 7.0 or above else false
var_dump(_browser('firefox', '< 3.0.5')); // return true if using below firefox 3.0.5 (can check minor version)
var_dump(_browser(false, false, true)); // return string of name of browser and version
var_dump(_browser('gecko'));
var_dump(_browser('firefox', 'le 1.5'));// version_compared function is used so you can use the same operator syntax
echo '</pre>';
*/

?>