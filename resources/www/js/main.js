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
  
window.onload = function() {
	var navDropdownLinks = document.getElementsByClassName("nav-link nav-dropdown-toggle");	
	
	[].forEach.call(navDropdownLinks, function (el) {
		el.addEventListener("click", navDropdownClick);
	});
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

function tryingToRemoveCar()
{
	try {
		showСonfirmRemoveCarDialog(event.target.value)
	}
	catch (err) {
		console.log(err)
	}

	return false;
}

function removeCar()
{
	event.preventDefault();
	
	var p = this.href.split('?');
    var action = p[0];
	var params = p[1].split('&');
	
	var formData = new FormData();

	for (var i in params) {
        var tmp= params[i].split('=');
        var key = tmp[0], value = tmp[1];
        formData.append(key, value);
	}

	hideModal();

	setTimeout(function run() {
		httpPostAsync(action, formData, function(responseText) {
			var result = JSON.parse(responseText);

			if (result.result === "success") {
				showModalInfoDialog("Информация", "Запись успешно добавлена");
				location.reload();
			}
			else if (result.result == "error")
			{
				showModalInfoDialog("Ошибка", result.message)
			}
		});
	}, 300);

    return false;
}

function editCar()
{
	return false;
}