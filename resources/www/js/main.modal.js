function showModalSwitchOutput(d)
{
	document.getElementById("modal_div").innerHTML = getSwitchModalDialog(d);

	document.getElementById("modal_close_button").addEventListener("click", hideModal);
	document.getElementById("swith_output_modal_cancel_button").addEventListener("click", hideModal);
	document.getElementById("swith_output_modal_yes_button").addEventListener("click", sendOutputValue);

	setTimeout(function run() {
		document.getElementsByClassName("modal fade")[0].classList.toggle("show");
		document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
		document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
	}, 200);
}

function getSwitchModalDialog(d)
{
	return '<div tabindex="-1" style="position: relative; z-index: 1050;">'
			+ '<div class="w2">'
				+ '<div class="Chart modal fade" role="dialog" tabindex="-1" style="display: block;">'
					+ '<div class="modal-dialog modal-sm" role="document">'
						+ '<div class="modal-content">'
							+ '<div class="modal-header">'
								+ '<h5 class="modal-title"> Output ' + d.name + '</h5>'
								+ '<button type="button" class="close" id="modal_close_button" aria-label="Close"><span aria-hidden="true">×</span>'
								+ '</button>'
							+ '</div>'
							+ '<div class="modal-body">'
								+ '<div class="row">'
									+ '<div class="col-12 col-md-12">'
										+ '<span>Set value</span>'
										+ '<select id="outputSelect" class="form-control">'
											+ '<option>Disable</option>'
											+ '<option>Enable</option>'
										+ '</select>'
									+ '</div>'
								+ '</div>'
							+ '</div>'
							+ '<div class="modal-footer">'
								+ '<a class="mr-1 ml-auto btn btn-info" id="swith_output_modal_yes_button" href="commands?'
									+ 'command=setOutputValue'
									+ '&sensorAddress=' + d.sensorAddress 
									+ '&relayId=' + d.name
									+ '&value=' + (d.value == 1 ? '0' : '1')
									+'">Yes</a>'
								+ '<button class="btn btn-secondary" id="swith_output_modal_cancel_button">No</button>'
							+ '</div>'
					+ '</div>'
				+ '</div>'
			+ '</div>'
			+ '<div class="modal-backdrop fade"></div>'
		+ '</div>';
}

function sendOutputValue(event)
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

	var value = $('#outputSelect').val() == 'Enable' ? '1' : '0';
	formData.append('value', value);

	hideModal();

	setTimeout(function run() {
		httpPostAsync(action, formData, function(responseText) {
			var result = JSON.parse(responseText);

			if (result.result == "success")
			{
				showModalInfoDialog("Information", "Commands completed successfully")
			}
			else if (result.result == "error_crc")
			{
				showModalInfoDialog("Error", "The command is not executed. CRC error")
			}
			else if (result.result == "error")
			{
				showModalInfoDialog("Error", "The command is not executed.")
			}
			else if (result.result == "timeout")
			{
				showModalInfoDialog("Error", "The command is not executed. Time out")
			}
		});
	}, 300);

    return false;
}


function showModalInfoDialog(title, text)
{
	document.getElementById("modal_div").innerHTML = getModalInfoDialogHtml(title, text);

	document.getElementById("modal_close_button").addEventListener("click", hideModal);
	document.getElementById("modal_info_ok_button").addEventListener("click", hideModal);

	setTimeout(function run() {
		document.getElementsByClassName("modal fade")[0].classList.toggle("show");
		document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
		document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
	}, 200);
}

function getModalInfoDialogHtml(title, text)
{
	return '<div tabindex="-1" style="position: relative; z-index: 1050;">'
			+ '<div class="w2">'
				+ '<div class="Chart modal fade" role="dialog" tabindex="-1" style="display: block;">'
					+ '<div class="modal-dialog modal-sm" role="document">'
						+ '<div class="modal-content">'
							+ '<div class="modal-header">'
								+ '<h5 class="modal-title">' + title + '</h5>'
								+ '<button type="button" class="close" id="modal_close_button" aria-label="Close"><span aria-hidden="true">×</span>'
								+ '</button>'
							+ '</div>'
							+ '<div class="modal-body">'
								+ '<div class="row">'
									+ '<div class="col-12 col-md-12">'
										+ '<span>' + text + '</span>'
									+ '</div>'
								+ '</div>'
							+ '</div>'
							+ '<div class="modal-footer">'
								+ '<button class="ml-auto btn btn-info" id="modal_info_ok_button">Ok</button>'
							+ '</div>'
					+ '</div>'
				+ '</div>'
			+ '</div>'
			+ '<div class="modal-backdrop fade"></div>'
		+ '</div>';
}

function showModalCloudConnectEditDialog(d)
{
	var action = "";
	if (d.type == "cloudConnect")
	{
		action = "sensors/cloudConnectInfo?id=";
	}
	else if (d.type == "sensorConnect")
	{
		action = "sensors/sensorConnectInfo?id=";
	}

	httpGetAsync(action + d.id, function(responseText) {
		var result = JSON.parse(responseText);

		document.getElementById("modal_div").innerHTML = getCCEditModalDialogHtml(d, result);

		document.getElementById("modal_close_button").addEventListener("click", hideModal);
		document.getElementById("cc_edit_modal_cancel_button").addEventListener("click", hideModal);
		//document.getElementById("cc_edit_modal_save_button").addEventListener("click", null);
		document.getElementById("cc_modal_edit_form").addEventListener("submit", sendCloudConnectInfo);

		setTimeout(function run() {
			document.getElementsByClassName("modal fade")[0].classList.toggle("show");
			document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
			document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
		}, 200);
	});	
}

function getCCEditModalDialogHtml(d, info)
{
	var title = "";
	var action = "";
	if (d.type == "cloudConnect")
	{
		title = "New Cloud Connect";
		action = "sensors/cloudConnectInfo";
	}
	else if (d.type == "sensorConnect")
	{
		title = "New Sensor Connect";
		action = "sensors/sensorConnectInfo";
	}
		
	return '<div tabindex="-1" style="position: relative; z-index: 1050;">'
			+ '<div class="w2">'
				+ '<div class="Chart modal fade" role="dialog" tabindex="-1" style="display: block;">'
					+ '<div class="modal-dialog modal-sm-2" role="document">'
						+ '<div class="modal-content">'
							+ '<div class="modal-header">'
								+ '<h5 class="modal-title">' + title + '</h5>'
								+ '<button type="button" class="close" id="modal_close_button" aria-label="Close"><span aria-hidden="true">×</span>'
								+ '</button>'
							+ '</div>'
							+ '<div class="modal-body">'
								+ '<form class id="cc_modal_edit_form" method="POST" action="' + action + '">'
									+ '<input type="hidden" name="id" value="' + d.id + '">'
									+ '<div class="row">'
										+ '<div class="col-12">'
											+ '<div class="form-group">'
												+ '<label for="name" class=" form-control-label">Name</label>'
												+ '<input type="text" name="name" id="name" class="form-control" value="' + (info.name ? info.name : d.name) + '">'
											+ '</div>'
										+ '</div>'
										+ '<div class="col-12">'
											+ '<div class="form-group">'
												+ '<label for="description" class=" form-control-label">Description</label>'
												+ '<textarea name="description" id="description" class="form-control">' + (info.description ? info.description : '') + '</textarea>'
											+ '</div>'
										+ '</div>'
									+ '</div>'
								+ '</form>'
							+ '</div>'
							+ '<div class="modal-footer">'
								+ '<button class="mr-1 ml-auto btn btn-info" id="cc_edit_modal_save_button" form="cc_modal_edit_form">Save</button>'
								+ '<button class="btn btn-secondary" id="cc_edit_modal_cancel_button">Cancel</button>'
							+ '</div>'
					+ '</div>'
				+ '</div>'
			+ '</div>'
			+ '<div class="modal-backdrop fade"></div>'
		+ '</div>';
}

function sendCloudConnectInfo(event)
{
	event.preventDefault();

	httpPostAsync(this.action, new FormData(this), function(responseText) {
		var result = JSON.parse(responseText);
		//setTreeNodeNameById(result.id, result.name);
		var myEvent = new CustomEvent("setTreeNodeNameById", { 'detail': result });
		document.dispatchEvent(myEvent);
		
		hideModal();
	});

	return false;
}

function sendSensorInfo(event)
{
	event.preventDefault();

	var element = document.getElementById("control_points_content");
	var elementChildrens = element.children;
	for (var i=0, child; child=elementChildrens[i]; i++) 
	{
		var inputs = child.getElementsByTagName("input");
		inputs[0].name = "controlPointFrom" + i;
		inputs[1].name = "controlPointTo" + i;
	}

	httpPostAsync(this.action, new FormData(this), function(responseText) {
		var result = JSON.parse(responseText);
		//setTreeNodeNameById(result.id, result.name);
		var myEvent = new CustomEvent("setTreeNodeNameById", { 'detail': result });
		document.dispatchEvent(myEvent);
		
		hideModal();
	});

	return false;
}

function addControlPoint()
{
	var element = document.getElementById("control_points_content");
	var nevIndex = element.children.length + 1;

	if (nevIndex == 10)
	{
		document.getElementById("sensor_edit_modal_add_button").style.display = 'none';
	}

	var div = document.createElement('div');
	div.className = "row form-group";
	div.innerHTML = `
					<div class="col col-sm-5">
						<input type="number" step="0.01" name="controlPointFrom" id="controlPointFrom" class="form-control" value="">
					</div>
					<div class="col col-sm-5">
						<input type="number" step="0.01" name="controlPointTo" id="controlPointTo" class="form-control" value="">
					</div>
					<div class="col col-sm-1">
						<button type="button" class="btn btn-link" name="remove_button"><i class="icons icon-close"></i></button>
					</div>
					`;

	div.getElementsByClassName("btn btn-link")[0].addEventListener("click", removeControlPoint);
	
	element.appendChild(div);
}

function removeControlPoint()
{
	var element = document.getElementById("control_points_content");
	element.removeChild(this.parentElement.parentElement);

	if (element.children.length < 10)
	{
		document.getElementById("sensor_edit_modal_add_button").style.display = 'block';
	}
}

function showModalSensorEditDialog(d)
{
	httpGetAsync("sensors/sensorTaring?id=" + d.id, function(responseText) {
		document.getElementById("modal_div").innerHTML = responseText;

		document.getElementById("modal_close_button").addEventListener("click", hideModal);
		document.getElementById("sensor_edit_modal_cancel_button").addEventListener("click", hideModal);
		document.getElementById("sensor_edit_modal_add_button").addEventListener("click", addControlPoint);
		document.getElementById("sensor_modal_edit_form").addEventListener("submit", sendSensorInfo);

		var removeButtons = document.getElementById("control_points_content").getElementsByClassName("btn btn-link");
		[].forEach.call(removeButtons, function (el) {
			el.addEventListener("click", removeControlPoint);
		});

		setTimeout(function run() {
			document.getElementsByClassName("modal fade")[0].classList.toggle("show");
			document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
			document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
		}, 200);
	});	
}

function showModalChangePasswordDialog()
{
	event.preventDefault();

	document.getElementById("modal_div").innerHTML = getModalChangePasswordDialogHtml();

	document.getElementById("modal_close_button").addEventListener("click", hideModal);
	document.getElementById("password_modal_cancel_button").addEventListener("click", hideModal);
	document.getElementById("password_edit_form").addEventListener("submit", saveNewPassword);
	

	setTimeout(function run() {
		document.getElementsByClassName("modal fade")[0].classList.toggle("show");
		document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
		document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
	}, 200);

	return false;
}

function saveNewPassword() 
{
	event.preventDefault();

	var tth = this;

	setTimeout(function run() {
		httpPostAsync("/settings/change-password", new FormData(tth), function(responseText) {
			var result = JSON.parse(responseText);

			if (result.result === "success") {
				showModalInfoDialog("Change password", "Change password success");
			}
			else {
				showModalInfoDialog("Change password", result.message);
			}
		});
	}, 200);

	hideModal();
	return false;
}

function getModalChangePasswordDialogHtml()
{
	return '<div tabindex="-1" style="position: relative; z-index: 1050;">'
			+ '<div class="w2">'
				+ '<div class="Chart modal fade" role="dialog" tabindex="-1" style="display: block;">'
					+ '<div class="modal-dialog modal-sm-2" role="document">'
						+ '<div class="modal-content">'
							+ '<div class="modal-header">'
								+ '<h5 class="modal-title">Change password</h5>'
								+ '<button type="button" class="close" id="modal_close_button" aria-label="Close"><span aria-hidden="true">×</span>'
								+ '</button>'
							+ '</div>'
							+ '<div class="modal-body">'
								+ '<form class id="password_edit_form" method="POST" action="/settings/change-password">'
									+ '<div class="row">'
										+ '<div class="col-12">'
											+ '<div class="form-group">'
												+ '<label for="name" class=" form-control-label">Old password</label>'
												+ '<input type="password" name="oldPassword" id="oldPassword" class="form-control" form="password_edit_form">'
											+ '</div>'
										+ '</div>'
										+ '<div class="col-12">'
											+ '<div class="form-group">'
												+ '<label for="name" class=" form-control-label">Password</label>'
												+ '<input type="password" name="password" id="password" class="form-control" form="password_edit_form">'
											+ '</div>'
										+ '</div>'
										+ '<div class="col-12">'
											+ '<div class="form-group">'
												+ '<label for="description" class=" form-control-label">Repeat password</label>'
												+ '<input type="password" name="repeatPassword" id="repeatPassword" class="form-control" form="password_edit_form">'
											+ '</div>'
										+ '</div>'
									+ '</div>'
								+ '</form>'
							+ '</div>'
							+ '<div class="modal-footer">'
								+ '<button class="mr-1 ml-auto btn btn-info" id="password_save_button" form="password_edit_form">Change</button>'
								+ '<button class="btn btn-secondary" id="password_modal_cancel_button">Cancel</button>'
							+ '</div>'
					+ '</div>'
				+ '</div>'
			+ '</div>'
			+ '<div class="modal-backdrop fade"></div>'
		+ '</div>';
}