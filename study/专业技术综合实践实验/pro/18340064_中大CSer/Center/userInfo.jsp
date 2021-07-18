<%@ page language="java" import="java.util.*, java.sql.*" contentType="text/html; charset=utf-8"%>
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
		String sql = String.format("select * from uuser where uname = \"%s\"", Name);
		ResultSet rs = stmt.executeQuery(sql);
		if (rs.next()) {
			ans += "{\"Contribution\": " + rs.getString("ucontribution") + 
						", \"Submit\": " + rs.getString("ucommit") + 
						", \"Pass\": " + rs.getString("upass") + 
						", \"Download\": " + rs.getString("udownload") + 
						", \"Favor\": " + rs.getString("ufavor") + 
						", \"ImagePath\": \"" + rs.getString("uimagePath") + "\"" +
						", \"Post\": [";
			String sql2 = String.format("select * from post where pname = \"%s\" order by pdate desc", Name);
			ResultSet rs2 = stmt.executeQuery(sql2);
			int c = 0;
			while (rs2.next()) {
				if (c != 0) ans += ", ";
				c++;
				ans += "{\"Title\": \"" + rs2.getString("ptitle") + 
							"\", \"Content\": \"" + rs2.getString("pcontent") + 
							"\", \"Date\": \"" + rs2.getString("pdate") + 
							"\", \"Comment\": \"" + rs2.getString("pcomment") + 
							"\", \"Like\": \"" + rs2.getString("plike") + 
							"\", \"Favor\": \"" + rs2.getString("pfavor") + 
							"\", \"ID\": \"" + rs2.getString("pid") + 
							"\", \"Type\": \"" + rs2.getString("ptype") + "\"}";
			}
			rs2.close();
			ans += "], \"Status\": 200, \"Msg\": \"Successful!\"}";
			out.print(ans);
		}
		else {
			out.print("{\"Status\": 400, \"Msg\": \" " + Name + "\"}");
		}
		rs.close();
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>