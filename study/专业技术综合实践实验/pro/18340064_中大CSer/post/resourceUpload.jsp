<%@ page language="java" import="java.util.*, java.io.*, javax.servlet.*, java.text.*, java.sql.*, org.apache.commons.io.*" contentType="text/html; charset=utf-8"%>
<%@ page import="org.apache.commons.fileupload.*" %>
<%@ page import="org.apache.commons.fileupload.disk.*" %>
<%@ page import="org.apache.commons.fileupload.servlet.*" %>
<%request.setCharacterEncoding("utf-8");%>

<%@ page language="java" import="java.util.*" contentType="text/html; charset=utf-8" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <title>post</title>
    <style>
        form {
            padding-left: 20px;
        }
        p {
            font-size: 22px;
            font-family: "微软雅黑";
            text-align: center;
        }
        span {
            vertical-align: top;
            font-size: 20px;
            font-family: "微软雅黑";
        }
        #title, #date, #member, #link, #wage {
            width: 650px;
            height: 25px;
            font-size: 18px;
            font-family: "微软雅黑";
        }
        #deadline {
            width: 610px;
            height: 28px;
            font-size: 18px;
            font-family: "微软雅黑";
        }
        #submit {
            margin-left: 350px;
            height: 35px;
            width: 100px;
            font-size: 20px;
            background-color: #867AB7;
            color: #FFFFFF;
            border-radius: 4px;
            border: 1px solid #797979;
            opacity: 0.8;
        }
    </style>

    <script>
    function setName() {
        var div = document.getElementById("user");
        div.value = localStorage.getItem("Name");   
    }
    </script>
</head>

<body>
    <%if (!request.getMethod().equalsIgnoreCase("post")) { %>
    <form action="resourceUpload.jsp" method="post" enctype="multipart/form-data">
        <p>资源分享</p>
        <span>模块：</span>
        专业技术<input type="radio" name="Module" value="1" checked="checked"/>
		计算机网络<input type="radio" name="Module" value="2" /><br><br>
        <input type="text" name="user" id="user" value="" hidden>
        <span>文件：</span><input type="file" name="file" size="50"><br><br>
        <input id="submit" type="submit" value="发布" onclick="setName()">
    </form>
    <%}else{
        boolean isMultipart = ServletFileUpload.isMultipartContent(request);
        String filename = "";
        String fname = "";
        String fpath = "";
        String address = "file/";
        String[] formField = new String[2]; // 一个存type，一个存userName
        if (isMultipart) { 
            FileItemFactory factory = new DiskFileItemFactory();
            ServletFileUpload upload = new ServletFileUpload(factory);
            List items = upload.parseRequest(request);
            for (int i = 0; i < items.size(); i++) {
                FileItem fi = (FileItem) items.get(i);
                if (fi.isFormField()) {
                    formField[i] = fi.getString("utf-8");
                }
                else {
                    DiskFileItem dfi = (DiskFileItem) fi;
                    filename = FilenameUtils.getName(dfi.getName());
                    fname = filename;
                    fpath = address + fname;
                    if (!dfi.getName().trim().equals("")) {
                        String fileName = application.getRealPath("Resources/file")
                                + System.getProperty("file.separator")
                                + FilenameUtils.getName(filename);
                        dfi.write(new File(fileName));
                    }
                }
            }
        }
        /*
        response.setStatus(HttpServletResponse.SC_MOVED_PERMANENTLY);
        String newLocn="../index.html";
        response.setHeader("Location", newLocn);
        */
        String connectString = "jdbc:mysql://localhost:3306/cser18340064"
                        + "?autoReconnect=true&useUnicode=true"
                        + "&characterEncoding=UTF-8";
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection(connectString, "user", "123");
            Statement stmt = con.createStatement();
            String sql = String.format("insert into ffile values('%s', '%s', '%s')", 
                        fname, fpath, formField[0]);
            int cnt = stmt.executeUpdate(sql);
            if (cnt > 0) {
                if (!formField[1].equalsIgnoreCase("admin")) {
                    out.print("文件上传成功!贡献值+1 !");
                    sql = String.format("update uuser set ucontribution = ucontribution + 1 where uname = '%s'", 
                                formField[1]);
                    stmt.executeUpdate(sql);
                } else {
                    out.print("文件上传成功!");
                }
            }
            else 
                out.print("文件上传失败!请重试。");

            stmt.close();
            con.close();
        }
        catch (Exception e) {
            out.print(e.getMessage());
        }
        
    }
    %>

</body>
</html>