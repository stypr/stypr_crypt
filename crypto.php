<?php
    error_reporting(0);

    function stypr_encrypt($str){
        $strings = $str;
        $MyKey = rand(1,1024);
        unset($tmp);
        for ($i = 0; $i < strlen($strings); $i++)
        {
            ++$n;
            $cal = ($n * $n) ^ hexdec("3E");
            $tmp = $tmp . substr("00000".dechex(decoct(ord(substr($strings, $i, 1)) ^ ($MyKey ^ hexdec("AFE43") ^ hexdec("399AA3") ^ ($cal)))), -6);
        }
        $tmp = strtoupper(strrev(substr("000".dechex($MyKey ^ hexdec("A9F") ^ hexdec("E77E")), -4).$tmp));
        return $tmp;
    }

    function stypr_decrypt($str){
        $strings = strtolower(strrev($str));
        $MyKey = hexdec(substr($strings, 0, 4)) ^ hexdec("A9F") ^ hexdec("E77E");
        $Temps = substr($strings, 4);
        unset($tmp);
        //echo $n;
        for ($i = 0; $i < strlen($Temps); $i+=6)
        {
            ++$n;
	        $cal = ($n * $n) ^ hexdec("3E");
            //echo chr(octdec(hexdec(substr($Temps, $i, 6))) ^ ($MyKey ^ hexdec("AFE43") ^ hexdec("399AA3") ^ $cal)) . "\n";
            $tmp = $tmp . chr(octdec(hexdec(substr($Temps, $i, 6))) ^ ($MyKey ^ hexdec("AFE43") ^ hexdec("399AA3") ^ $cal));
        }
        return $tmp;
    }
    echo(stypr_decrypt(stypr_encrypt("SEXYBACK")));
?>
