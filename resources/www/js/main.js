function formLoginInputChanged(element) {
	if (element.value.length >= 3) {
		element.classList.remove('is-invalid');
	} 
	document.getElementById("error_message").innerHTML = "";
}

function formPasswordInputChanged(element) {
    if (element.value.length >= 5) {
		element.classList.remove('is-invalid');
	} 
	document.getElementById("error_message").innerHTML = "";
}

function validForm() {
	document.getElementById("error_message").innerHTML = "";
    var username = document.getElementsByName("username")[0];
	var password = document.getElementsByName("password")[0];

	var validLogin = login.value.length >= 3
    var validPassword = password.value.length >= 5

	if (!validLogin) {
        username.classList.add('is-invalid');
	}

	if (!validPassword) {
		password.classList.add('is-invalid');
	}

	return validLogin && validPassword
}

function navDropdownClick(e) {
	e.preventDefault();
	e.target.parentElement.classList.toggle('open');
}

function vote(element) {
	console.log(element.href);
    /*// (1) создать объект для запроса к серверу
    var req = getXmlHttp()  
       
        // (2)
    // span рядом с кнопкой
    // в нем будем отображать ход выполнения
    //var statusElem = document.getElementById('vote_status') 
    
    req.onreadystatechange = function() {  
        // onreadystatechange активируется при получении ответа сервера
 
        if (req.readyState == 4) { 
            // если запрос закончил выполняться
 
            //statusElem.innerHTML = "Запись выбрана"; // показать статус (Not Found, ОК..)
 
            if(req.status == 200) { 
                 // если статус 200 (ОК) - выдать ответ пользователю
                alert("Эта запись -  "+req.responseText);
 
            }
            // тут можно добавить else с обработкой ошибок запроса
        }
 
    }
 
       // (3) задать адрес подключения
    req.open('GET', 'settings.html', true);  
 
    // объект запроса подготовлен: указан адрес и создана функция onreadystatechange
    // для обработки ответа сервера
     
        // (4)
    req.send(null);  // отослать запрос
  
        // (5)
    //statusElem.innerHTML = 'Подбор записи.' */
    httpGetAsync("./settings.html", function(responseText) {
    	var containerFluid = document.getElementsByClassName("container-fluid")[0];
    	containerFluid.innerHTML  = responseText;


    	//alert("Эта запись -  " + responseText); 
    	//alert("Эта запись -  " + extractContent(responseText)); 
    });

    return false;
}

function setMenuItemNoActive()
{
	var navLinks = document.getElementById("nav_bar").getElementsByClassName("nav-link");	
	[].forEach.call(navLinks, function (el) {
		el.classList.remove('active');
	});
}

/*function loadContent(event) 
{
	event.preventDefault();

	setMenuItemNoActive();
	this.classList.add('active');

	httpGetAsync(this.href, function(responseText) {
		var containerFluid = document.getElementsByClassName("container-fluid")[0];
		containerFluid.innerHTML  = '<div class="animated fadeIn">' + responseText + '</div>';
        executeScriptFromInnerHTML(containerFluid); 
        setTitleFromInnerHTML(containerFluid); 
        window.scrollTo(0, 0);   
	});

    return false;
}*/

function executeScriptFromInnerHTML(element)
{
    var scripts = element.getElementsByTagName("script");
    var script;
    for (var i = 0; script = scripts[i]; i++)
    {
        eval(script.innerHTML); 
    }
}

function httpGetAsync(theUrl, callback)
{
    var request = new XMLHttpRequest();
    request.onreadystatechange = function() { 
        if (request.readyState == 4 && request.status == 200)
            callback(request.responseText);
    }
    request.open("GET", theUrl, true); // true for asynchronous 
    request.send(null);
}

function httpPostAsync(theUrl, postData, callback)
{
	var request = new XMLHttpRequest();
	request.onreadystatechange = function() { 
        if (request.readyState == 4 && request.status == 200)
            callback(request.responseText);
    }

    request.open("POST", theUrl, true); // true for asynchronous 
    request.send(postData);
}

function guid()
{
	function s4() {
		return Math.floor((1 + Math.random()) * 0x10000)
			.toString(16)
			.substring(1);
	}

	return s4() + s4() + '-' + s4() + '-' + s4() + '-' + s4() + '-' + s4() + s4() + s4();
}

function getRandomColor() {
	var letters = '0123456789ABCDEF';
	var color = '#';
	for (var i = 0; i < 6; i++) {
		color += letters[Math.floor(Math.random() * 16)];
	}
	return color;
}
  

/*Подписка на события сервера*/
var eventSource;
var eventRssiSource;
/*Подписка на события сервера*/

window.onload = function() {
	var navDropdownLinks = document.getElementsByClassName("nav-link nav-dropdown-toggle");	
	
	[].forEach.call(navDropdownLinks, function (el) {
		el.addEventListener("click", navDropdownClick);
	});
	
	//обновление данных для дерева
	if (typeof updateData == 'function')
	{
		eventSource = new EventSource('./sensors/tree');
		eventSource.onopen = function(e) {
			console.log("Соединение открыто");
		};

		eventSource.onerror = function(e) {
			if (this.readyState == EventSource.CONNECTING) {
				console.log("Соединение порвалось, пересоединяемся...");
			} else {
				console.log("Ошибка, состояние: " + this.readyState);
			}
		};

		//eventSource.addEventListener('sensorData', function(e) {
		//	console.log( 'Пришёл ' + e.data );
		//	updateData(e.data);
		//});

		eventSource.addEventListener('sensorData', function(e) {
			//console.log(e.data);
			updateData(JSON.parse(e.data));
		});
	}

	//обновление данных для дерева rssi
	if (typeof updateRssiData == 'function')
	{
		eventRssiSource = new EventSource('./network/tree');
		eventRssiSource.onopen = function(e) {
			console.log("Соединение открыто");
		};

		eventRssiSource.onerror = function(e) {
			if (this.readyState == EventSource.CONNECTING) {
				console.log("Соединение порвалось, пересоединяемся...");
			} else {
				console.log("Ошибка, состояние: " + this.readyState);
			}
		};

		eventRssiSource.addEventListener('rssiData', function(e) {
			updateRssiData(JSON.parse(e.data));
		});
	}

	/*navLinks = document.getElementById("nav_bar").getElementsByClassName("nav-link");	
	[].forEach.call(navLinks, function (el) {
		if (el.href.indexOf('measurements') > -1)
		{
			el.click();
			return;
		}
		else
		{
			console.log(el.href);
		}
	});*/
	//document.getElementById('elementID').click();

	/*var d = { 
		"name":"1",
		"value": 1
	}
	showModalSwitchOutput(d);*/
}


/*Модальное окно*/

function showModalChart(d)
{
	currentSensorChartId = d.id;
	document.getElementById("modal_div").innerHTML = getModaldialog(d.name);
	createChart();
	document.getElementById("modal_close_button").addEventListener("click", hideModal);
	document.getElementById("realTime_0008B1").addEventListener("click", toggleChartRealtime);
	setTimeout(function run() {
		document.getElementsByClassName("modal fade")[0].classList.toggle("show");
		document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
		document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
	}, 200);
}

function hideModal()
{
	document.getElementsByClassName("modal fade")[0].classList.toggle("show");
	document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
	document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
	setTimeout(function run() {
		document.getElementById("modal_div").innerHTML = "";
		chart = null;
	}, 200);
}

function getModaldialog(title)
{
	return '<div tabindex="-1" style="position: relative; z-index: 1050;">'
			+ '<div class="w2">'
				+ '<div class="Chart modal fade" role="dialog" tabindex="-1" style="display: block;">'
					+ '<div class="modal-dialog" role="document">'
						+ '<div class="modal-content">'
							+ '<div class="modal-header">'
								+ '<h5 class="modal-title">' + title + '&nbsp;&nbsp;<h5 id="chart-title-value" class="modal-title"></h5></h5>'
								+ '<button type="button" class="close" id="modal_close_button" aria-label="Close"><span aria-hidden="true">×</span>'
								+ '</button>'
							+ '</div>'
							+ '<div class="modal-body">'
								+ '<div class="row">'
								//+ '<div class="col-9"></div>'
									+ '<div class="col-1">'
										+ '<ul class="ListIntervalModal ml-auto list-group">'
											+ '<li class="list-group-item-action list-group-item btn-real-time active" id="realTime_0008B1">'
												+ '<i class="icons icon-refresh"></i>'
											+ '</li>'
											//+ '<li class="list-group-item-action list-group-item">Hour</li>'
											//+ '<li class="list-group-item-action list-group-item">Day</li>'
											//+ '<li class="list-group-item-action list-group-item">Week</li>'
											//+ '<li class="list-group-item-action list-group-item">Month</li>'
											//+ '<li class="list-group-item-action list-group-item">Year</li>'
											//+ '<li class="list-group-item-action list-group-item">Max</li>'
											//+ '<li class="custom-interval active list-group-item-action list-group-item"><button type="button" class="btn-update-chart btn btn-info">'
											//	+ '<i class="icon-reload icons"></i></button>'
											//+ '</li>'
										+ '</ul>'
									+ '</div>'
								+ '</div>'
								+ '<div class="row">'
									+ '<div id="chartdiv"></div>'
								+ '</div>'
							+ '</div>'
					+ '</div>'
				+ '</div>'
			+ '</div>'
			+ '<div class="modal-backdrop fade"></div>'
		+ '</div>';
}

var chart;
var currentSensorChartId = 0;
function createChart()
{
	var chartData = [ { 'dateTime': 'null', 'value': 0 } ];//generateChartData();

	chart = AmCharts.makeChart("chartdiv", {
	    "type": "serial",
	    "theme": "light",
	    "categoryField": "dateTime",
	    "dataDateFormat": 'YYYY-MM-DD HH:NN:SS',
	    //"mouseWheelZoomEnabled": true,
	    "dataProvider": chartData,
	    "synchronizeGrid":true,
	    
	    // This will keep the selection at the end across data updates
		"glueToTheEnd": true,

		"numberFormatter": {
            "precision": -1,
            "decimalSeparator": ".",
            "thousandsSeparator": ""
        },

	    "valueAxes": [{
	        "id":"v1",
	        "axisColor": "#000",
	        "axisThickness": 1,
	        "axisAlpha": 1,
	        "position": "left"
	    }, ],
	    "graphs": [{
	        "valueAxis": "v1",
	        "lineColor": "#FF6600",
	        "bullet": "round",
	        "bulletBorderThickness": 1,
	        "hideBulletsCount": 30,
	        //"title": "red line",
	        "valueField": "value",
			"fillAlphas": 0,
			"visibleInLegend": "false"
	    },],
	    "categoryAxis": {
	        "autoRotateCount": 0,
	        "minPeriod": 'ss',
	        "parseDates": true,
	        "position": 'top',
	        "minorGridEnabled": true
	    },
	    "chartCursor": {
	        // pan: true,
	        "valueLineEnabled": true,
	        "valueLineBalloonEnabled": true,
	        "cursorAlpha": 1,
	        "cursorColor": '#258cbb',
	        // limitToGraph: 'g1',
	        "valueLineAlpha": 0.2,
	        "valueZoomable": true,
	        "categoryBalloonDateFormat": 'YYYY-MM-DD HH:NN:SS'
	    },
	    "chartScrollbar": {
	        "color": '#888888',
	        "scrollbarHeight": 50,
	        "backgroundAlpha": .2,
	        "selectedBackgroundAlpha": .4,
	        "selectedBackgroundColor": '#888888',
	        "graphFillAlpha": 0,
	        "autoGridCount": true,
	        "selectedGraphFillAlpha": 0,
	        "graphLineAlpha": .2,
	        "graphLineColor": '#c2c2c2',
	        "selectedGraphLineColor": '#888888',
	        "selectedGraphLineAlpha": 1
	    },
	    "valueScrollbar": {
	        "enabled": true,
	        "oppositeAxis": false,
	        "offset": 50,
	        "scrollbarHeight": 10
	    },

	    // Event listeners
		/*"listeners": [ {
			"event": "rendered",
			"method": function( event ) {
				chartTemp.mouseDown = false;
				chartTemp.containerDiv.onmousedown = function() {
					chartTemp.mouseDown = true;
				}
				chartTemp.containerDiv.onmouseup = function() {
					chartTemp.mouseDown = false;
				}
			}
		}],*/
	});

	chart.mouseDown = false;
	chart.containerDiv.onmousedown = function() {
		chart.mouseDown = true;
	}
	chart.containerDiv.onmouseup = function() {
		chart.mouseDown = false;
	}

	//chart.addListener("dataUpdated", zoomChart);
	//zoomChart();
	statrtTestTimer();
}

// generate some random data, quite different range
function generateChartData() {
    var chartData = [];
    var firstDate = new Date();
    firstDate.setSeconds(firstDate.getSeconds() - 300);

    var value = 1600;

    for (var i = 0; i < 300; i++) {
        // we create date objects here. In your data, you can have date strings
        // and then set format of your dates using chart.dataDateFormat property,
        // however when possible, use date objects, as this will speed up chart rendering.
        var newDate = new Date(firstDate);
        newDate.setSeconds(newDate.getSeconds() + i);

        value += Math.round((Math.random()<0.5?1:-1)*Math.random()*10);
        //hits += Math.round((Math.random()<0.5?1:-1)*Math.random()*10);
        //views += Math.round((Math.random()<0.5?1:-1)*Math.random()*10);

        chartData.push({
            dateTime: newDate,
            value: value,
            //hits: hits,
            //views: views
        });
    }
    return chartData;
}

/*function zoomChart()
{
    chart.zoomToIndexes(chart.dataProvider.length - 100, chart.dataProvider.length - 1);
}

function onChartRendered()
{
	chart.mouseDown = false;
	chart.containerDiv.onmousedown = function() {
		chart.mouseDown = true;
	}
	chart.containerDiv.onmouseup = function() {
		chart.mouseDown = false;
	}
}*/

function statrtTestTimer()
{
	setTimeout(function run() {
		if (chart)
		{
			chartUpdate();
			setTimeout(run, 1000);
		}
	}, 1000);
}

function chartUpdate()
{
	httpGetAsync('./sensors/chart?all=1&id=' + currentSensorChartId, function(responseText) {
		if (chart.mouseDown || !isCharRealTime)
    		return;

		chart.dataProvider = JSON.parse(responseText);
		chart.validateData(); 

		document.getElementById("chart-title-value").innerHTML = ' (' + chart.dataProvider[chart.dataProvider.length - 1].value + chart.dataProvider[chart.dataProvider.length - 1].units + ')';
	});
}

var isCharRealTime = true;

function toggleChartRealtime()
{
	isCharRealTime = !isCharRealTime;
	document.getElementById("realTime_0008B1").classList.toggle("active");
}

