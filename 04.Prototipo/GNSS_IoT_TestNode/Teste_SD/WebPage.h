/*
 * WebPage.h
 *
 * Created: 14/08/2021 17:24:04
 *  Author: scorr
 */ 

/*! \file WebPage.h */

/*! \brief HTML Page Content                                            */
#ifndef WEBPAGE_H_
#define WEBPAGE_H_

// Header
const String html_init = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name='viewport' content='width=device-width, initial-scale=1.0'/>
<link rel=\"icon\" href=\"data:,\">
<meta charset='utf-8'>
<meta http-equiv="refresh" content="5">
<style>
html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
 .button { background-color: #4CAF50; border: none; border-radius: 15px; color: white; padding: 10px 10px;
 text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}
 .button2 {background-color: #555555; border: none; border-radius: 15px; color: white; padding: 10px 10px;
	 text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}
body {font-size:100%;}
#main {display: table; margin: auto;  padding: 30px 30px 30px 30px; }
#content { border: 2px solid blue; border-radius: 15px; padding: 10px 10px 10px 10px;}
h2 {text-align:center; margin: 10px 0px 10px 0px;}
p { text-align:center; margin: 5px 0px 10px 0px; font-size: 120%;}
#time_P { margin: 10px 0px 15px 0px;}
blc { display:inline-block; }
@media,
{
	blc  { display: inline; margin-right:10px; text-align:center;}
	blc2 { display: inline; margin-right:10px; line-height: 10px; text-align:center;}
	blc3 { display: inline; margin-left:10px; line-height: 10px; text-align:center;}
}
</style>

<script>
function updateTime()
{
	var d = new Date();
	var t = "";
	t = d.toLocaleTimeString();
	document.getElementById('P_time').innerHTML = t;
}

function updateTemp()
{
	ajaxLoad('getTemp');
}

var ajaxRequest = null;
if (window.XMLHttpRequest)  { ajaxRequest =new XMLHttpRequest(); }
else                        { ajaxRequest =new ActiveXObject("Microsoft.XMLHTTP"); }

function ajaxLoad(ajaxURL)
{
	if(!ajaxRequest){ alert('AJAX is not supported.'); return; }
	
	ajaxRequest.open('GET',ajaxURL,true);
	ajaxRequest.onreadystatechange = function()
	{
		if(ajaxRequest.readyState == 4 && ajaxRequest.status==200)
		{
			var ajaxResult = ajaxRequest.responseText;
			var tmpArray = ajaxResult.split("|");
			document.getElementById('upweb').innerHTML = tmpArray[0];
		}
	}
	ajaxRequest.send();
}

var myVar1 = setInterval(updateTemp, 5000);
var myVar2 = setInterval(updateTime, 1000);

</script>


<title>IoT Test Node</title>

)=====";

const char* html_header = "</head>"
						 "<body>"
						 "<div id='main'>"
						 "<h2>IoT Test Node</h2>"
						 "<hr>";
// HTML STATUS Colors
const char* html_ON = "lime";
const char* html_OFF = "green";
const char* html_state_idle = "green";
const char* html_state_acquisition = "lime";
const char* html_state_error = "brown";
const char* html_state_buffering = "purple";


/************************************************************************/
/* FIRST BLOCK                                                          */
/************************************************************************/
// HTML WiFi STATUS
const char* html_wifi1 = " <br style=\"line-height:5px\"> "
							"<div id='content'>"
								"<div> "
									"<blc>"
										" <blc style=\"width:14px; height: 14px; -webkit-border-radius: 7px;"
										" -moz-border-radius: 7px; border-radius: 7px;background: ";
const char* html_wifi2 =				" ;\"> </blc> "
										" <blc>WIFI</blc> "
										" </blc> ";

// HTML GPS STATUS
const char* html_gps1 =				"<blc>"
										"<blc style=\"width:14px; height: 14px; -webkit-border-radius: 7px; "
										"-moz-border-radius: 7px; border-radius: 7px;background: ";
const char* html_gps2 =					" ;\"> </blc> "
										" <blc2>GPS</blc2> "
									"</blc>";

// HTML SD STATUS
const char* html_sd1 =				"<blc>"
										"<blc style=\"width:14px; height: 14px; -webkit-border-radius: 7px; "
										"-moz-border-radius: 7px; border-radius: 7px;background: ";
const char* html_sd2 =					" ;\"> </blc> "
										"<blc>SD_CARD</blc> "
									"</blc> "
								"</div>";





/************************************************************************/
/* SECOND BLOCK                                                         */
/************************************************************************/
// HTML SAT STATUS
const char* html_sat1 =			"<div>"
									"<blc> "
										"<blc style=\"width:14px; height: 14px; -webkit-border-radius: 7px; "
										"-moz-border-radius: 7px; border-radius: 7px;background: ";
const char* html_sat2 =					" ;\"> </blc> "
										" <blc2>Sat :[";
// Display here the number of satellites
const char* html_sat3 =					"] </blc2>"
									"</blc>";

// HTML LOCALIZATION STATUS 
const char* html_loc1 =				"<blc> "
										"<blc style=\"width:14px; height: 14px; -webkit-border-radius: 7px; "
										"-moz-border-radius: 7px; border-radius: 7px;background: ";
const char* html_loc2 =					" ;\"> </blc> "
										" <blc2>Loc</blc2> "
									"</blc>";

// HTML TIME STATUS 
const char* html_time1 =			"<blc>"
										"<blc style=\"width:14px; height: 14px; -webkit-border-radius: 7px; "
										"-moz-border-radius: 7px; border-radius: 7px;background: ";
const char* html_time2 =				" ;\"> </blc> "
										"<blc2>Time</blc2>"
									"</blc>";

// HTML DATE STATUS
const char* html_date1 =			"<blc>"
										"<blc style=\"width:14px; height: 14px; -webkit-border-radius: 7px; "
										"-moz-border-radius: 7px; border-radius: 7px;background: ";
const char* html_date2 =				" ;\"> </blc> "
										"<blc2>Date</blc2> "
									"</blc> "
								"</div> "
							"</div> ";


/************************************************************************/
/* THIRD BLOCK                                                          */
/************************************************************************/
// STATE MACHINE STATUS
const char* html_state_machine1 ="<br style=\"line-height:5px\"> "
								"<div id='content'>"
									"<div> "
										"<blc>"
											"<blc style=\"width:14px; height: 14px; -webkit-border-radius: 7px; "
											"-moz-border-radius: 7px; border-radius: 7px;background: ";
const char* html_state_machine2 =			" ;\"> </blc> "
											" <blc>STATE: ";
const char* html_state_machine3 =			"</blc> "
										"</blc> "
									"</div> "
								"</div> "
								"<hr> ";
// HTML NUMBER OF SAMPLES

const char* html_num_sample1  = "<br style=\"line-height:5px\"> "
								"<div id='content'>"
									"<div> "
										"<blc>"
											"<blc>Number of Samples: ";
const char* html_num_sample2  =				"</blc> "
										"</blc> "
									"</div> "
								"</div> "
								"<hr> ";

// HTML ORIGINAL FILE SIZE STATUS
const char* html_ori_size1 = " <br style=\"line-height:5px\"> "
							  "<div id='content'>"
								"<div> "
									"<blc>"
										"<blc>ORI: ";
const char* html_ori_size2 =			" Bytes</blc> "
									"</blc> ";

// HTML COMPRESSED FILE SIZE STATUS
const char* html_comp_size1 =		"<blc> "
										"<blc2>| CMP: ";
const char* html_comp_size2 =			" Bytes</blc2> "
									"</blc> "
								"</div> "
							"</div> "
							"<hr> ";

/************************************************************************/
/* FOURTH BLOCK                                                         */
/************************************************************************/

// HTML FOOTER TIMER
const char* html_footer_time_init = "<div id='content'>"
										"<div> "
											"<blc>"
												"<blc3>Time: ";
const char* html_footer_time_end =				"</blc3> "
											"</blc> ";

// HTML FOOTER DATE
const char* html_footer_date_init =			"<blc> "
												"<blc3>Date: " ;
const char* html_footer_date_end =				"</blc3> "
											"</blc> "
									"</div>"
								"</div>";


// Footer
const String html_closing = R"=====(
</div>
</body>
</html>
)=====";



#endif /* WEBPAGE_H_ */