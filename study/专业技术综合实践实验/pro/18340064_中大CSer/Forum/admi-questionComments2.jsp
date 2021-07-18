<%@ page language="java" import="java.util.*, java.io.*, javax.servlet.*, java.text.*, java.sql.*" contentType="text/html; charset=utf-8"%>
<%
	request.setCharacterEncoding("utf-8");
	String connectString = "jdbc:mysql://localhost:3306/cser18340064"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8";
	String ID = request.getParameter("ID");
	String Name = request.getParameter("Name");
	String Content = request.getParameter("Content");

	try {
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString, "user", "123");
		Statement stmt = con.createStatement();
		java.util.Date dNow = new java.util.Date();
		SimpleDateFormat ft = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String str_date = ft.format(dNow);
		String sql = String.format("insert into comments values('%s', '%s', '%s', '%s')", 
					Name, Content, str_date, ID);
		int cnt = stmt.executeUpdate(sql);
		if (cnt > 0) {
			sql = String.format("update post set pcomment = pcomment + 1 where pid = '%s'", ID);
			int cnt2 = stmt.executeUpdate(sql);
			if (cnt2 > 0)
				out.print("{\"Status\": 200, \"Msg\": \"Successful!\"}");
			else
				out.print("{\"Status\": 400, \"Msg\": \"Error1!\"}");
		}
		else 
			out.print("{\"Status\": 400, \"Msg\": \"Error2!\"}");
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>