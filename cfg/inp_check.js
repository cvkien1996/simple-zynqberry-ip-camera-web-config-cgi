function validateIPAddress(inputText)
{
	var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
	
	if(inputText.match(ipformat))
	{
		return true;
	}
	
	return false;
}

function validatePort(port){
	if(port <= 0 || port > 50000)
		return false;
	return true;
}

function validateDate(arg1, arg2, arg3, date_format){
	var day, month, year;

	if(date_format == "dd/mm/yyyy"){
		day = arg1;
		month = arg2;
		year = arg3;
	} else if(date_format == "mm/dd/yyyy"){
		day = arg2;
		month = arg1;
		year = arg3;
	} else if(date_format == "yyyy/mm/dd"){
		day = arg3;
		month = arg2;
		year = arg1;
	}
	
	if (year < 1000 || year > 3000 || month <= 0 || month > 12)
		return false;
	
	var monthLength = [ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ];
	
	if(year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        monthLength[1] = 29;
	
	if (day <= 0 || day > monthLength[month - 1])
		return false;
	
	return true;
}

function changeDateFormat(pre_format, cur_format){
	
	var opt1 = document.forms["CONFIG_FORM"]["date_current_1"];
	var opt2 = document.forms["CONFIG_FORM"]["date_current_2"];
	var opt3 = document.forms["CONFIG_FORM"]["date_current_3"];
	
	if(pre_format == "dd/mm/yyyy" && cur_format == "mm/dd/yyyy"){
		var temp = opt1.value;
		opt1.value = opt2.value;
		opt2.value = temp;
	} else if(pre_format == "dd/mm/yyyy" && cur_format == "yyyy/mm/dd"){
		var temp = opt1.value;
		opt1.value = opt3.value;
		opt3.value = temp;
	} else if(pre_format == "mm/dd/yyyy" && cur_format == "dd/mm/yyyy"){
		var temp = opt1.value;
		opt1.value = opt2.value;
		opt2.value = temp;
	} else if(pre_format == "mm/dd/yyyy" && cur_format == "yyyy/mm/dd"){
		var temp = opt1.value;
		opt1.value = opt2.value;
		opt2.value = temp;
		
		var temp = opt1.value;
		opt1.value = opt3.value;
		opt3.value = temp;
	} else if(pre_format == "yyyy/mm/dd" && cur_format == "dd/mm/yyyy"){
		var temp = opt1.value;
		opt1.value = opt3.value;
		opt3.value = temp;
	} else if(pre_format == "yyyy/mm/dd" && cur_format == "mm/dd/yyyy"){
		var temp = opt1.value;
		opt1.value = opt3.value;
		opt3.value = temp;
		
		var temp = opt1.value;
		opt1.value = opt2.value;
		opt2.value = temp;
	}
}

function validateForm(){
	var cam_resolution = document.forms["CONFIG_FORM"]["cam_resolution"].value;
	var cam_fps = document.forms["CONFIG_FORM"]["cam_fps"].value;
	var cam_bitrate = document.forms["CONFIG_FORM"]["cam_bitrate"].value;
	
	var net_is_dhcp = document.forms["CONFIG_FORM"]["net_is_dhcp"].value;
	var net_ip = document.forms["CONFIG_FORM"]["net_ip"].value;
	var net_subnet = document.forms["CONFIG_FORM"]["net_subnet"].value;
	var net_gateway = document.forms["CONFIG_FORM"]["net_gateway"].value;
	var net_mac = document.forms["CONFIG_FORM"]["net_mac"].value;
	var net_rtspport = document.forms["CONFIG_FORM"]["net_rtspport"].value;
	var net_httpport = document.forms["CONFIG_FORM"]["net_httpport"].value;
	
	var date_format = document.forms["CONFIG_FORM"]["date_format"].value;
	var date_timezone = document.forms["CONFIG_FORM"]["date_timezone"].value;
	var date_current_1 = document.forms["CONFIG_FORM"]["date_current_1"].value;
	var date_current_2 = document.forms["CONFIG_FORM"]["date_current_2"].value;
	var date_current_3 = document.forms["CONFIG_FORM"]["date_current_3"].value;
	var date_time = document.forms["CONFIG_FORM"]["date_time"].value;
	
	var user_name = document.forms["CONFIG_FORM"]["user_name"].value;
	var user_pw = document.forms["CONFIG_FORM"]["user_pw"].value;

	if (cam_resolution == "" ||
		cam_fps == "" ||
		cam_bitrate == "" ||
		net_is_dhcp == "" ||
		net_ip == "" ||
		net_subnet == "" ||
		net_gateway == "" ||
		net_mac == "" ||
		net_rtspport == "" ||
		net_httpport == "" ||
		date_format == "" ||
		date_timezone == "" ||
		date_current_1 == "" ||
		date_current_2 == "" ||
		date_current_3 == "" ||
		date_time == "" ||
		user_name == "" ||
		user_pw == "")
	{
		document.getElementById("error_log").innerHTML = "Please fill in all field before submit";
		return false;	
	}
	
	if (!(validateIPAddress(net_ip) &&
		validateIPAddress(net_subnet) && 
		validateIPAddress(net_gateway)))
	{
		document.getElementById("error_log").innerHTML = "You have entered an invalid IP address!";
		return false;
	}
	
	if (!(validatePort(net_rtspport) && validatePort(net_httpport)))
	{
		document.getElementById("error_log").innerHTML = "You have entered an invalid port number!";
		return false;
	}
	
	if (!(validateDate(date_current_1, date_current_2, date_current_3, date_format)))
	{
		document.getElementById("error_log").innerHTML = "You have entered invalid date!";
		return false;
	}
	
	return true;
}

function doSave(){
	/* Reset */
	document.getElementById("error_log").innerHTML = "";
	
	console.log("Save");
	return validateForm();
}

function doCancel(){
	/* Reset */
	document.getElementById("error_log").innerHTML = "";
	console.log("Cancel");
	return true;
}

function doLogout(){
	console.log("Logout");
	return true;
}