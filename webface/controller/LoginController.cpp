#include "LoginController.h"

#include <QTime>

#include "webface/RequestMapper.h"

#include "core/Util.h"
#include "core/Settings.h"

LoginController::LoginController()
{

}

void LoginController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray metod = request.getMethod();
    if (metod == "POST")
    {
        HttpSession session = RequestMapper::sessionStore->getSession(request, response, true);
        QByteArray username = request.getParameter("username");
        QByteArray password = request.getParameter("password");

        if (session.contains("username"))
        {
            response.redirect("/");
            return;
        }
        else
        {
            if (Util::sha1(password) == Settings::instance().adminPassword() &&
                    username == Settings::instance().adminLogin())
            {
                session.set("username", username);
                session.set("logintime", QTime::currentTime());
                session.set("type", "all");

                response.redirect("/");
                return;
            }
            else if (Util::sha1(password) == Settings::instance().operatorPassword() &&
                     username == Settings::instance().operatorLogin())
             {
                 session.set("username", username);
                 session.set("logintime", QTime::currentTime());
                 session.set("type", "readOnly");

                 response.redirect("/");
                 return;
             }
            else
            {
                QByteArray language = request.getHeader("Accept-Language");
                response.setHeader("Content-Type", "text/html; charset=UTF-8");

                Template t = RequestMapper::templateCache->getTemplate("login", language);
                t.setVariable("message_error", tr("Incorrect username or password"));
                response.write(t.toUtf8(), true);
			}
        }
    }
    else
    {
        QByteArray language = request.getHeader("Accept-Language");
        response.setHeader("Content-Type", "text/html; charset=UTF-8");

        Template t = RequestMapper::templateCache->getTemplate("login", language);
        t.setVariable("message_error", "");
        response.write(t.toUtf8(), true);
    }

    /*HttpSession session = RequestMapper::sessionStore->getSession(request, response, true);
    QByteArray username = request.getParameter("username");
    QByteArray password = request.getParameter("password");

    //qDebug("username=%s",username.constData());
    //qDebug("password=%s",password.constData());

    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
    response.write("<html><body>");

    if (session.contains("username")) {
        QByteArray username=session.get("username").toByteArray();
        QTime logintime = session.get("logintime").toTime();
        response.write("You are already logged in.<br>");
        response.write("Your name is: " + username+"<br>");
        response.write("You logged in at: " + logintime.toString("HH:mm:ss").toLatin1()+"<br>");
    }
    else {
        if (username == "admin" and password == "admin") {
            response.write("Yes, correct");
            session.set("username", username);
            session.set("logintime", QTime::currentTime());
        }
        else
        {
            response.write("<form method='POST' action='/login'>");
            if (!username.isEmpty())
            {
                response.write("No, that was wrong!<br><br>");
            }
            response.write("Please log in:<br>");
            response.write("Name:  <input type='text' name='username'><br>");
            response.write("Password: <input type='password' name='password'><br>");
            response.write("<input type='submit'>");
            response.write("</form");
        }
    }

    response.write("</body></html>",true);*/
}
