<%--
Created by IntelliJ IDEA.
User: andyc
Date: 18/05/2022
Time: 14:21
To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="web.assignment8.domain.User" %>
<%@ page import="java.sql.DriverManager" %>
<%@ page import="java.sql.Connection" %>
<%@ page import="java.sql.Statement" %>
<%@ page import="java.sql.ResultSet" %>

<html>
<head>
    <script language="javascript">
        function deleteRecord(id){
            var doIt=confirm('Do you want to delete the record?');
            if(doIt){
                var f=document.forms[2];
                // console.log(f);
                f.method="post";
                f.action='../TopicPageController?id='+id;
                f.submit();
            }
            else{

            }
        }
    </script>
    <title>Topic</title>
    <style>
        .table {
            display: flex;
        }
        body{
            background-color: rgba(0, 255, 129, 0.44);
        }
        table,td,th{
            border: 1px solid salmon;
            border-collapse: collapse;
            margin: 10px;
            padding: 20px;

            background-color: #96D4D4;
        }
    </style>
</head>
<body>
<div>
    <%
        out.println("<h3>Welcome to the topic " + (String) request.getSession().getAttribute("selectedTopic") + ", " + ((User) request.getSession().getAttribute("user")).getUsername() + "! </h3>");
    %>
    <form action="AddPostController" method="get">
        <input type="text" placeholder="Post title:" name="title" required>
        <input type="text" placeholder="Post content:" name="content" required>
        <input type="submit" id="postSubmit" value="Post!">
    </form>
    <form action="LogoutController" method="get">
        <input type="submit" id="logout" value="Logout">
    </form>

    <%
        Statement st = null;
        Connection con = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            con = (Connection) DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/forum", "root", "");
            st = con.createStatement();
            ResultSet rs = st.executeQuery("select id,title,content,author from posts where topic=" + request.getSession().getAttribute("topicId") + ";");

    %>
    <table style="text-align:center; width: 500px;">
    <thead>
    <tr>
        <th>TITLE</th>
        <th>CONTENT</th>
        <th>DELETE</th>
    </tr>
    </thead>
    <tbody>
    <%while (rs.next()) {
    %>
    <tr>
        <td><%=rs.getString("title")%></td>
        <td><%=rs.getString("content")%></td>
        <td><%if(rs.getInt("author")==((User) request.getSession().getAttribute("user")).getId()){%>

<%--&lt;%&ndash;            <%=((User) request.getSession().getAttribute("user")).getUsername()%>&ndash;%&gt;action="TopicPageController"--%>
            <form  method="post" style="margin:auto;display:block;">
                <input type="hidden" name="idToDelete" value="<%=rs.getInt("id")%>" />
                <input type="button" name="delete" id="deletePost" value="Delete" onclick="deleteRecord(<%=rs.getInt("id")%>);" >
            </form>

        <%}%></td>

    </tr>
    <%}%>
    </tbody>
</table><br>
    <%} catch (Exception e) {
        out.print(e.getMessage());%><br><%
    } finally {
        st.close();
        con.close();
    }
%>

</div>
</body>
</html>
