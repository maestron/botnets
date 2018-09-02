<?php

define("FULL_RECORD_LENGTH",50);
include("geoip.inc");
include("geoipregionvars.php");

class geoiprecord {
  var $country_code;
  var $country_code3;
  var $country_name;
  var $region;
  var $city;
  var $postal_code;
  var $latitude;
  var $longitude;
  var $area_code;
  var $dma_code;
}

class geoipdnsrecord {
  var $country_code;
  var $country_code3;
  var $country_name;
  var $region;
  var $regionname;
  var $city;
  var $postal_code;
  var $latitude;
  var $longitude;
  var $areacode;
  var $dmacode;
  var $isp;
  var $org;
}

function getrecordwithdnsservice($str){
  $record = new geoipdnsrecord;
  $keyvalue = split(";",$str);
  foreach ($keyvalue as $keyvalue2){
    list($key,$value) = split("=",$keyvalue2);
    if ($key == "co"){
      $record->country_code = $value;
    }
    if ($key == "ci"){
      $record->city = $value;
    }
    if ($key == "re"){
      $record->region = $value;
    }
    if ($key == "ac"){
      $record->areacode = $value;
    }
    if ($key == "dm"){
      $record->dmacode = $value;
    }
    if ($key == "is"){
      $record->isp = $value;
    }
    if ($key == "or"){
      $record->org = $value;
    }
    if ($key == "zi"){
      $record->postal_code = $value;
    }
    if ($key == "la"){
      $record->latitude = $value;
    }
    if ($key == "lo"){
      $record->longitude = $value;
    }
  }
  $number = $GLOBALS['GEOIP_COUNTRY_CODE_TO_NUMBER'][$record->country_code];
  $record->country_code3 = $GLOBALS['GEOIP_COUNTRY_CODES3'][$number];
  $record->country_name = $GLOBALS['GEOIP_COUNTRY_NAMES'][$number];
  if ($record->region != "") {
    if (($record->country_code == "US")|($record->country_code == "CA")){
      $record->regionname = $GLOBALS['ISO'][$record->country_code][$record->region];
    } else {
      $record->regionname = $GLOBALS['FIPS'][$record->country_code][$record->region];
    }
  }
  return $record;
}

function _get_record($gi,$ipnum){
  $seek_country = _geoip_seek_country($gi,$ipnum);
  if ($seek_country == $gi->databaseSegments) {
    return NULL;
  }
  $record_pointer = $seek_country + (2 * $gi->record_length - 1) * $gi->databaseSegments;

  fseek($gi->filehandle, $record_pointer, SEEK_SET);
  $record_buf = fread($gi->filehandle,FULL_RECORD_LENGTH);
  $record = new geoiprecord;
  $record_buf_pos = 0;
  $char = ord(substr($record_buf,$record_buf_pos,1));
  $record->country_code = $GLOBALS['GEOIP_COUNTRY_CODES'][$char];
  $record->country_code3 = $GLOBALS['GEOIP_COUNTRY_CODES3'][$char];
  $record->country_name = $GLOBALS['GEOIP_COUNTRY_NAMES'][$char];
  $record_buf_pos++;
  $str_length = 0;
  
  //get region
  $char = ord(substr($record_buf,$record_buf_pos+$str_length,1));
  while ($char != 0){
    $str_length++;
    $char = ord(substr($record_buf,$record_buf_pos+$str_length,1));
  }
  if ($str_length > 0){
    $record->region = substr($record_buf,$record_buf_pos,$str_length);
  }
  $record_buf_pos += $str_length + 1;
  $str_length = 0;

  //get city
  $char = ord(substr($record_buf,$record_buf_pos+$str_length,1));
  while ($char != 0){
    $str_length++;
    $char = ord(substr($record_buf,$record_buf_pos+$str_length,1));
  }
  if ($str_length > 0){
    $record->city = substr($record_buf,$record_buf_pos,$str_length);
  }
  $record_buf_pos += $str_length + 1;
  $str_length = 0;

  //get postal code
  $char = ord(substr($record_buf,$record_buf_pos+$str_length,1));
  while ($char != 0){
    $str_length++;
    $char = ord(substr($record_buf,$record_buf_pos+$str_length,1));
  }
  if ($str_length > 0){
    $record->postal_code = substr($record_buf,$record_buf_pos,$str_length);
  }
  $record_buf_pos += $str_length + 1;
  $str_length = 0;
  $latitude = 0;
  $longitude = 0;
  for ($j = 0;$j < 3; ++$j){
    $char = ord(substr($record_buf,$record_buf_pos++,1));
    $latitude += ($char << ($j * 8));
  }
  $record->latitude = ($latitude/10000) - 180;

  for ($j = 0;$j < 3; ++$j){
    $char = ord(substr($record_buf,$record_buf_pos++,1));
    $longitude += ($char << ($j * 8));
  }
  $record->longitude = ($longitude/10000) - 180;

  if (GEOIP_CITY_EDITION_REV1 == $gi->databaseType){
    $dmaarea_combo = 0;
    if ($record->country_code == "US"){
      for ($j = 0;$j < 3;++$j){
        $char = ord(substr($record_buf,$record_buf_pos++,1));
        $dmaarea_combo += ($char << ($j * 8));
      }
      $record->dma_code = floor($dmaarea_combo/1000);
      $record->area_code = $dmaarea_combo%1000;
    }
  }
  return $record;
}

function GeoIP_record_by_addr ($gi,$addr){
  if ($addr == NULL){
     return 0;
  }
  $ipnum = ip2long($addr);
  return _get_record($gi, $ipnum);
}
?>
