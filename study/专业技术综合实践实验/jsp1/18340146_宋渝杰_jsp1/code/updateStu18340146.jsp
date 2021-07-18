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
        if (request.getParameter("reset") != null) {
            num = name = "";
        }
		else if (request.getParameter("sub") == null) {
            String sql = String.format("select * from stu where id=%s", pid);
			ResultSet rs = stmt.executeQuery(sql);
			if (rs.next()) {
				num = rs.getString("num");
				name = rs.getString("name");	
			}
		}
		else {
            String sql = String.format("update stu set num='%s', name='%s' where id='%s'", num, name, pid);
			int cnt = stmt.executeUpdate(sql);
			if (cnt > 0)
				msg = "更新成功!";
			stmt.close();
			con.close();
		}	
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
	<title>修改学生记录</title>
</head>

<body>
	<div class="container">
		<h1>修改学生记录</h1>
		<form action="updateStu18340146.jsp?pid=<%=pid%>" method="post" name="f">
			学号：<input id="num" name="num" type="text" value="<%=num%>"><br><br>
			姓名：<input id="name" name="name" type="text" value="<%=name%>"><br><br>
			<input type="submit" name="sub" value="修改">
			<input type="submit" name="reset" value="清空"><br><br>
		</form>
		<%=msg%><br><br>
		<a href='browseStu18340146.jsp'>返回</a>
	</div>
</body>
</html>
