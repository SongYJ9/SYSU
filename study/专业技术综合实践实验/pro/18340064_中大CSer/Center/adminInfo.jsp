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
		String sql = String.format("select * from administraion where aname = \"%s\"", Name);
		ResultSet rs = stmt.executeQuery(sql);
		if (rs.next()) {
			ans += "{\"ImagePath\": \"" + rs.getString("aimagePath") + "\"" +
						", \"ResourcesManagement\": " + rs.getString("resourcesManagement") +
						", \"GuideManagement\": " + rs.getString("guideManagement") +
						", \"InfoManagement\": " + rs.getString("infoManagement") +
						", \"ForumManagement\": " + rs.getString("forumManagement") +
						", \"Operations\": [";
			String sql2 = String.format("select * from operations where oname = \"%s\" order by odate desc", Name);
			ResultSet rs2 = stmt.executeQuery(sql2);
			int c = 0;
			while (rs2.next()) {
				if (c != 0) ans += ", ";
				c++;
				ans += "{\"Name\": \"" + rs2.getString("oname") + 
							"\", \"Operation\": \"" + rs2.getString("operation") + 
							"\", \"Detail\": \"" + rs2.getString("odetail") + 
							"\", \"Date\": \"" + rs2.getString("odate") + "\"}";
			}
			rs2.close();
			ans += "], \"Status\": 200, \"Msg\": \"Successful!\"}";
			out.print(ans);
		}
		else {
			out.print("{\"Status\": 400, \"Msg\": \"" + Name + "\"}");
		}
		rs.close();
		stmt.close();
		con.close();
	}
	catch (Exception e) {
		out.print(e.getMessage());
	}
%>