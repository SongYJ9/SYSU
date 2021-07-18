<%@ page language="java" import="java.util.*, java.io.*, javax.servlet.*, java.text.*, java.sql.*" contentType="text/html; charset=utf-8"%>
<%
	request.setCharacterEncoding("utf-8");
	String connectString = "jdbc:mysql://localhost:3306/cser18340064"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8";
	String Name = request.getParameter("Name");
    String Title = request.getParameter("Title");
    String Content = request.getParameter("Content");

	try {
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString, "user", "123");
		Statement stmt = con.createStatement();
		String sql = String.format("select * from post order by pid desc");
		ResultSet rs = stmt.executeQuery(sql);
		if (rs.next()) {
			java.util.Date dNow = new java.util.Date();
			SimpleDateFormat ft = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			String str_date = ft.format(dNow);
			String sql2 = String.format("insert into post values('%d', '%s', '%s', '%s', '%s', 0, 0, 0, 0)", 
						Integer.parseInt(rs.getString("pid"))+1, Name, Title, Content, str_date);
			int cnt = stmt.executeUpdate(sql2);
			if (cnt > 0)
				out.print("{\"Status\": 200, \"Msg\": \"Delete successful!\"}");
			else 
				out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
		}
		else {
			java.util.Date dNow = new java.util.Date();
			SimpleDateFormat ft = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			String str_date = ft.format(dNow);
			String sql2 = String.format("insert into post values('%d', '%s', '%s', '%s', '%s', 0, 0, 0, 0)", 
						1, Name, Title, Content, str_date);
			int cnt = stmt.executeUpdate(sql2);
			if (cnt > 0)
				out.print("{\"Status\": 200, \"Msg\": \"Delete successful!\"}");
			else 
				out.print("{\"Status\": 400, \"Msg\": \"Error!\"}");
		}
		rs.close();
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>