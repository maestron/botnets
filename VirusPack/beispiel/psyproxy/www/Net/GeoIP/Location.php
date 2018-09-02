<?php
// +----------------------------------------------------------------------+
// | PHP version 5                                                        |
// +----------------------------------------------------------------------+
// | Copyright (C) 2004 MaxMind LLC                                       |
// +----------------------------------------------------------------------+
// | This library is free software; you can redistribute it and/or        |
// | modify it under the terms of the GNU Lesser General Public           |
// | License as published by the Free Software Foundation; either         |
// | version 2.1 of the License, or (at your option) any later version.   |
// |                                                                      |
// | This library is distributed in the hope that it will be useful,      |
// | but WITHOUT ANY WARRANTY; without even the implied warranty of       |
// | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
// | Lesser General Public License for more details.                      |
// |                                                                      |
// | You should have received a copy of the GNU Lesser General Public     |
// | License along with this library; if not, write to the Free Software  |
// | Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 |
// | USA, or view it online at http://www.gnu.org/licenses/lgpl.txt.      |
// +----------------------------------------------------------------------+
// | Authors: Jim Winstead <jimw@apache.org> (original Maxmind version)   |
// |          Hans Lellelid <hans@xmpl.org>                               |
// +----------------------------------------------------------------------+
//
// $Id: Location.php,v 1.1 2004/07/01 12:51:13 hlellelid Exp $

/**
 * This class represents a location record as returned by Net_GeoIP::lookupLocation().
 * 
 * This class is primarily a collection of values (the public properties of the class), but
 * there is also a distance() method to calculate the km distance between two points.
 * 
 * @author Hans Lellelid <hans@xmpl.org>
 * @version $Revision: 1.1 $
 * @package Net_GeoIP
 * @see Net_GeoIP::lookupLocation()
 */
class Net_GeoIP_Location
{

    public $countryCode;
    public $countryName;
    public $region;
    public $city;
    public $postalCode;
    public $latitude;
    public $longitude;
    public $areaCode;
    public $dmaCode;
          
    /**
     * Calculate the distance in km between two points.
     * @param Net_GeoIP_Location $loc The other point to which distance will be calculated.
     * @return float The number of km between two points on the globe.
     */
    public function distance(Net_GeoIP_Location $loc)
	{        
        // ideally these should be class constants, but class constants 
		// can't be operations.
        $RAD_CONVERT = M_PI / 180;
        $EARTH_DIAMETER = 2 * 6378.2;
        
        $lat1 = $this->latitude;
        $lon1 = $this->longitude;
        $lat2 = $loc->latitude;
        $lon2 = $loc->longitude;

        // convert degrees to radians
        $lat1 *= $RAD_CONVERT;
        $lat2 *= $RAD_CONVERT;

        // find the deltas
        $delta_lat = $lat2 - $lat1;
        $delta_lon = ($lon2 - $lon1) * $RAD_CONVERT;

        // Find the great circle distance
        $temp = pow(sin($delta_lat/2), 2) + cos($lat1) * cos($lat2) * pow(sin($delta_lon/2), 2);
        return $EARTH_DIAMETER * atan2(sqrt($temp),sqrt(1-$temp));
    }
                
}