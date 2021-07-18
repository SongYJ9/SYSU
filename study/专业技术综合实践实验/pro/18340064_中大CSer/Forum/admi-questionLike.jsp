<%@ page language="java" import="java.util.*, java.sql.*" contentType="text/html; charset=utf-8"%>
<%
	request.setCharacterEncoding("utf-8");
	String connectString = "jdbc:mysql://localhost:3306/cser18340064"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8";
	String Pid = request.getParameter("ID");

	try {
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString, "user", "123");
		Statement stmt = con.createStatement();
		String sql;
		sql = String.format("update post set plike = plike + 1 where pid = '%s'", Pid);
		int cnt = stmt.executeUpdate(sql);
		if (cnt > 0)
			out.print("{\"Status\": 200, \"Msg\": \"Successful!\"}");
		else
			out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>