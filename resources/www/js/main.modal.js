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