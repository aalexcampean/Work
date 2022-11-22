package web.assignment8.controller;

import web.assignment8.domain.User;
import web.assignment8.model.DBManager;
import javax.servlet.*;
import javax.servlet.http.*;
import org.json.JSONArray;
import org.json.JSONObject;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class LogoutController extends HttpServlet {

    public LogoutController() {
        super();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        int userId = ((User) request.getSession().getAttribute("user")).getId();


        DBManager dbManager = new DBManager();

        dbManager.deleteUserFromSession(userId);

        response.sendRedirect("index.jsp");
    }
}