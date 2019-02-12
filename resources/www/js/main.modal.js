function showAddCarModalDialog()
{
	httpGetAsync("/car-list/add-car", function(responseText) {
		document.getElementById("modal_div").innerHTML = responseText;

		document.getElementById("modal_close_button").addEventListener("click", hideModal);
		document.getElementById("add_car_modal_cancel_button").addEventListener("click", hideModal);
		document.getElementById("add_car__form").addEventListener("submit", saveNewCar);

		setTimeout(function run() {
			document.getElementsByClassName("modal fade")[0].classList.toggle("show");
			document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
			document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
		}, 200);
	});	
}

function saveNewCar() 
{
	event.preventDefault();

	if (document.getElementById("car_number").value == "") {
		return;
	}

	if (document.getElementById("owner_surname").value == "") {
		return;
	}

	if (document.getElementById("owner_name").value == "") {
		return;
	}

	var tth = this;

	setTimeout(function run() {
		httpPostAsync("/car-list/add-car", new FormData(tth), function(responseText) {
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
	}, 200);

	hideModal();
	return false;
}

function showEditCarModalDialog(id)
{
	httpGetAsync("/car-list/edit-car?id=" + id, function(responseText) {
		document.getElementById("modal_div").innerHTML = responseText;

		document.getElementById("modal_close_button").addEventListener("click", hideModal);
		document.getElementById("edit_car_modal_cancel_button").addEventListener("click", hideModal);
		document.getElementById("edit_car_form").addEventListener("submit", saveEditedCar);

		setTimeout(function run() {
			document.getElementsByClassName("modal fade")[0].classList.toggle("show");
			document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
			document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
		}, 200);
	});	
}

function saveEditedCar()
{
	event.preventDefault();

	if (document.getElementById("car_number").value == "") {
		return;
	}

	if (document.getElementById("owner_surname").value == "") {
		return;
	}

	if (document.getElementById("owner_name").value == "") {
		return;
	}

	var tth = this;

	setTimeout(function run() {
		httpPostAsync("/car-list/edit-car", new FormData(tth), function(responseText) {
			var result = JSON.parse(responseText);

			if (result.result === "success") {
				showModalInfoDialog("Информация", "Запись успешно обновлена");
				location.reload();
			}
			else if (result.result == "error")
			{
				showModalInfoDialog("Ошибка", result.message)
			}
		});
	}, 200);

	hideModal();
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

function showСonfirmRemoveCarDialog(id)
{
	document.getElementById("modal_div").innerHTML = getСonfirmRemoveCarModalDialog(id);

	document.getElementById("modal_close_button").addEventListener("click", hideModal);
	document.getElementById("swith_output_modal_cancel_button").addEventListener("click", hideModal);
	document.getElementById("swith_output_modal_yes_button").addEventListener("click", removeCar);

	setTimeout(function run() {
		document.getElementsByClassName("modal fade")[0].classList.toggle("show");
		document.getElementsByClassName("modal-backdrop fade")[0].classList.toggle("show");
		document.getElementsByClassName("app header-fixed sidebar-fixed aside-menu-fixed aside-menu-hidden")[0].classList.toggle("modal-open");
	}, 200);

	return false;
}

function getСonfirmRemoveCarModalDialog(id)
{
	return '<div tabindex="-1" style="position: relative; z-index: 1050;">'
			+ '<div class="w2">'
				+ '<div class="Chart modal fade" role="dialog" tabindex="-1" style="display: block;">'
					+ '<div class="modal-dialog modal-sm" role="document">'
						+ '<div class="modal-content">'
							+ '<div class="modal-header">'
								+ '<h5 class="modal-title"> Внимание</h5>'
								+ '<button type="button" class="close" id="modal_close_button" aria-label="Close"><span aria-hidden="true">×</span>'
								+ '</button>'
							+ '</div>'
							+ '<div class="modal-body">'
								+ '<div class="row">'
									+ '<div class="col-12 col-md-12">'
										+ '<span>Вы действительно хотите удалить выбранню запись?</span>'
									+ '</div>'
								+ '</div>'
							+ '</div>'
							+ '<div class="modal-footer">'
								+ '<a class="mr-1 ml-auto btn btn-danger" id="swith_output_modal_yes_button" href="/car-list/remove-car?'
									+ 'id=' + id
									+'">Удалить</a>'
								+ '<button class="btn btn-secondary" id="swith_output_modal_cancel_button">Отмена</button>'
							+ '</div>'
					+ '</div>'
				+ '</div>'
			+ '</div>'
			+ '<div class="modal-backdrop fade"></div>'
		+ '</div>';
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
	try {
		showEditCarModalDialog(event.target.value)
	}
	catch (err) {
		console.log(err)
	}

	return false;
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
				showModalInfoDialog("Изменение пароля", "Пароль успешно изменён");
			}
			else {
				showModalInfoDialog("Изменение пароля", result.message);
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
								+ '<h5 class="modal-title">Изменение пароля</h5>'
								+ '<button type="button" class="close" id="modal_close_button" aria-label="Close"><span aria-hidden="true">×</span>'
								+ '</button>'
							+ '</div>'
							+ '<div class="modal-body">'
								+ '<form class id="password_edit_form" method="POST" action="/settings/change-password">'
									+ '<div class="row">'
										+ '<div class="col-12">'
											+ '<div class="form-group">'
												+ '<label for="name" class=" form-control-label">Старый пароль</label>'
												+ '<input type="password" name="oldPassword" id="oldPassword" class="form-control" form="password_edit_form">'
											+ '</div>'
										+ '</div>'
										+ '<div class="col-12">'
											+ '<div class="form-group">'
												+ '<label for="name" class=" form-control-label">Новый пароль</label>'
												+ '<input type="password" name="password" id="password" class="form-control" form="password_edit_form">'
											+ '</div>'
										+ '</div>'
										+ '<div class="col-12">'
											+ '<div class="form-group">'
												+ '<label for="description" class=" form-control-label">Повторите новый пароль</label>'
												+ '<input type="password" name="repeatPassword" id="repeatPassword" class="form-control" form="password_edit_form">'
											+ '</div>'
										+ '</div>'
									+ '</div>'
								+ '</form>'
							+ '</div>'
							+ '<div class="modal-footer">'
								+ '<button class="mr-1 ml-auto btn btn-info" id="password_save_button" form="password_edit_form">Изменить</button>'
								+ '<button class="btn btn-secondary" id="password_modal_cancel_button">Отмена</button>'
							+ '</div>'
					+ '</div>'
				+ '</div>'
			+ '</div>'
			+ '<div class="modal-backdrop fade"></div>'
		+ '</div>';
}