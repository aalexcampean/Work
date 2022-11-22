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
import java.util.Arrays;
import java.util.List;
public class AddPostController extends HttpServlet{
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        DBManager dbManager = new DBManager();

        int userId = ((User) request.getSession().getAttribute("user")).getId();
        String topic = (String)request.getSession().getAttribute("selectedTopic");
        request.getSession().setAttribute("topicsString",dbManager.getTopics());

        String title = (String) request.getParameter("title");
        String content = (String) request.getParameter("content");
        int topicId = dbManager.getTopicId(topic);
        request.getSession().setAttribute("topicId",topicId);
        dbManager.addPost(topicId,userId,title,content);

        response.sendRedirect("topic_page.jsp");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        DBManager dbManager = new DBManager();
        dbManager.deletePost(Integer.parseInt(request.getParameter("idToDelete")));
        response.sendRedirect("topic_page.jsp");
    }

}
