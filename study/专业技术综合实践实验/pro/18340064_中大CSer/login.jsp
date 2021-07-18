<%@ page language="java" import="java.util.*, java.sql.*" contentType="text/html; charset=utf-8"%>
<%
	request.setCharacterEncoding("utf-8");
	String connectString = "jdbc:mysql://localhost:3306/cser18340064"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8";
	String Name = request.getParameter("Name");
	String Password = request.getParameter("Password");
	String Identity = request.getParameter("Identity");

	try {
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString, "user", "123");
		Statement stmt = con.createStatement();
		if (Identity.equals("false")) {
			String sql = String.format("select * from uuser where uname = \"%s\"", Name);
			ResultSet rs = stmt.executeQuery(sql);
			if (rs.next()) {
				if (rs.getString("upassword").equals(Password))
					out.print("{\"Status\": 200, \"Msg\": \"登陆成功\"}");
				else 
					out.print("{\"Status\": 400, \"Msg\": \"密码错误\"}");
			}
			else {
				out.print("{\"Status\": 400, \"Msg\": \"用户不存在\"}");
			}
			rs.close();
		}
		else {
			String sql = String.format("select * from administraion where aname = \"%s\"", Name);
			ResultSet rs = stmt.executeQuery(sql);
			if (rs.next()) {
				if (rs.getString("apassword").equals(Password))
					out.print("{\"Status\": 200, \"Msg\": \"登陆成功\"}");
				else 
					out.print("{\"Status\": 400, \"Msg\": \"密码错误\"}");
			}
			else {
				out.print("{\"Status\": 400, \"Msg\": \"用户不存在\"}");
			}
			rs.close();
		}
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>