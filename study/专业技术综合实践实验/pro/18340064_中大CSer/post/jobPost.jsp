<%@ page language="java" import="java.util.*, java.io.*, javax.servlet.*, java.text.*, java.sql.*" contentType="text/html; charset=utf-8"%>
<%
	request.setCharacterEncoding("utf-8");
	String connectString = "jdbc:mysql://localhost:3306/cser18340064"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8";
	String Name = request.getParameter("Name");
    String Title = request.getParameter("Title");
    String Date = request.getParameter("Date");
    String Deadline = request.getParameter("Deadline");
    String Member = request.getParameter("Member");
    String Wage = request.getParameter("Wage");
    String Link = request.getParameter("Link");

	try {
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString, "user", "123");
		Statement stmt = con.createStatement();
		String sql = String.format("select * from reviewjobinfo order by jid desc");
		ResultSet rs = stmt.executeQuery(sql);
		if (rs.next()) {
			java.util.Date dNow = new java.util.Date();
			SimpleDateFormat ft = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			String str_date = ft.format(dNow);
			String sql2 = String.format("insert into reviewjobinfo values('%d', '%s', '%s', '%s', '%s', '%s', '%s')", 
						Integer.parseInt(rs.getString("jid"))+1, Title, Date, Deadline, Member, Wage, Link);
			int cnt = stmt.executeUpdate(sql2);
			if (cnt > 0)
				out.print("{\"Status\": 200, \"Msg\": \"Delete successful!\"}");
			else 
				out.print("{\"Status\": 400, \"Msg\": \"Error!1\"}");
		}
		else {
			java.util.Date dNow = new java.util.Date();
			SimpleDateFormat ft = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			String str_date = ft.format(dNow);
			String sql2 = String.format("insert into reviewjobinfo values('%d', '%s', '%s', '%s', '%s', '%s', '%s')", 
						1, Title, Date, Deadline, Member, Wage, Link);
			int cnt = stmt.executeUpdate(sql2);
			if (cnt > 0)
				out.print("{\"Status\": 200, \"Msg\": \"Delete successful!\"}");
			else 
				out.print("{\"Status\": 400, \"Msg\": \"Error!1\"}");
		}
		rs.close();
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>