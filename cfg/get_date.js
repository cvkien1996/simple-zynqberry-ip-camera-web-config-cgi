var secTimeInc;

function initDate(){
	var now = new Date();
	var day = now.getDate();
	var month = now.getMonth() + 1;
	var year = now.getFullYear();
	
	var dateformat = document.forms["CONFIG_FORM"]["date_format"].value;
	var opt1 = document.forms["CONFIG_FORM"]["date_current_1"];
	var opt2 = document.forms["CONFIG_FORM"]["date_current_2"];
	var opt3 = document.forms["CONFIG_FORM"]["date_current_3"];
	
	if (!(opt1.value == "" || opt2.value == "" || opt3.value == ""))
		return ;

	if (document.forms["CONFIG_FORM"]["date_time"].value != "")
		return ;
	
	if (dateformat == "dd/mm/yyyy"){
		opt1.value = day;
		opt2.value = month;
		opt3.value = year;
	} else if (dateformat == "mm/dd/yyyy"){
		opt2.value = day;
		opt1.value = month;
		opt3.value = year;
	} else if (dateformat == "yyyy/mm/dd"){
		opt3.value = day;
		opt2.value = month;
		opt1.value = year;
	}
	
	var hour = now.getHours();
	var min = now.getMinutes();
	var sec = now.getSeconds();
	
	if (hour < 10)	hour = '0' + hour;
	if (min < 10) 	min = '0' + min;
	if (sec < 10)	sec = '0' + sec;
	
	var time =  hour + ':' + min + ':' + sec;
	//console.log(time);
	document.forms["CONFIG_FORM"]["date_time"].value = time;
}

function updateDate(){
	var time = document.forms["CONFIG_FORM"]["date_time"].value;
	
	var cur = new Date("2019-01-01 " + time); 
	
	var hour = cur.getHours();
	var min = cur.getMinutes();
	var sec = cur.getSeconds();
	
	sec = sec + 1;
	
	if (sec == 60){
		sec = 0;
		min = min + 1;
		
		if (min == 60){
			min = 0;
			hour = hour + 1;
			
			if (hour == 24)
				hour = 0;
		}
	}
	
	if (hour < 10)	hour = '0' + hour;
	if (min < 10) 	min = '0' + min;
	if (sec < 10)	sec = '0' + sec;
	
	var time =  hour + ':' + min + ':' + sec;
	
	document.forms["CONFIG_FORM"]["date_time"].value = time;
	
	secTimeInc = setTimeout(updateDate, 1000);
}