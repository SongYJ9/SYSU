<%@ page language="java" import="java.util.*, java.io.*, javax.servlet.*, java.text.*, java.sql.*" contentType="text/html; charset=utf-8"%>
<%
	request.setCharacterEncoding("utf-8");
	String connectString = "jdbc:mysql://localhost:3306/cser18340064"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8";
	String Name = request.getParameter("Name");
	String ans = "";

	try {
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString, "user", "123");
		Statement stmt = con.createStatement();
		String sql = String.format("delete from ffile where fname = \"%s\"", Name);
		int cnt = stmt.executeUpdate(sql);
		if (cnt > 0) {
			java.util.Date dNow = new java.util.Date();
			SimpleDateFormat ft = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			String str_date = ft.format(dNow);
			String sql2 = String.format("insert into operations values('%s', '%s', '%s', '%s')", 
						"admin", "Delete files ^_^", Name, str_date);
			int cnt2 = stmt.executeUpdate(sql2);
			if (cnt2 > 0)
				out.print("{\"Status\": 200, \"Msg\": \"Delete successful!\"}");
			else
				out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
		}
		else 
			out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>