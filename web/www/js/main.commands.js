function commandSendForm(event)
{
    event.preventDefault();

    httpPostAsync(this.action, new FormData(this), function(responseText) {
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
        else if (result.result == "сommand_not_found")
        {
            showModalInfoDialog("Error", "The command is not executed. Command not found")
        }
        else if (result.result == "bad_request")
        {
            showModalInfoDialog("Error", "The command is not executed. Invalid parameters" + (result.message ? ". " + result.message : ""))
        }
        else if (result.result == "no_response")
        {
            showModalInfoDialog("Error", "The command is not executed. No reply was received from the device")
        }
    });

    return false;
}