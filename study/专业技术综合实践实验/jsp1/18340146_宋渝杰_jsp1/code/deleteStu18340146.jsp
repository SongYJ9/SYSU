<%@ page language="java" import="java.util.*, java.sql.*" contentType="text/html; charset=utf-8"%>
<% 
	request.setCharacterEncoding("utf-8");
	String msg = "";
	String connectString = "jdbc:mysql://localhost:3306/teaching"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8";
	String num = request.getParameter("num");
	String name = request.getParameter("name");
	String pid = request.getParameter("pid");
    try {
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString, "user", "123"); 
		Statement stmt = con.createStatement();
        String sql = String.format("delete from stu where id=%s", pid);
		int cnt = stmt.executeUpdate(sql);
		if (cnt > 0)
			msg = "Delete Success!";
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		msg = e.getMessage();
	}
%>

<!DOCTYPE HTML>
<html>
<head>
	<style>
		.container {
			width: 600px;
			margin: auto;
			text-align: center;
		}
	</style>
	<title>删除学生记录</title>
</head>

<body>
	<div class="container">
		<h1>删除学生记录</h1>
		<%=msg%><br><br>
		<a href='browseStu18340146.jsp'>返回</a>
	</div>
</body>
</html>
