### 一些使用教程和关键点：

**环境：**win10 + Visual Studio 2019 C# + MySQL 8.0

src 文件夹为 C# 源代码文件

report.pdf 为小组报告

数据库.exe 为可执行程序

**登录账号密码：**你的 mysql 账号密码（比如说账号：root，密码：123456，具体密码请查看你自己的mysql）

**第一次使用：**请输入以下 mysql 代码，建立数据库和数据

```sql
create database tsxs;
use tsxs;

create table book
(bname varchar(10),
bprice numeric(6,1) default 0,
bnum int default 0,
primary key(bname));

create table supplier
(sname varchar(10),
bname varchar(10),
sprice numeric(6,1) default 0,
primary key(sname,bname),
foreign key(bname) references book(bname));

create table record
(stime varchar(25),
bname varchar(10),
species int not null,
bprice numeric(6,1) default 0,
bnum int default 0,
primary key(stime),
foreign key(bname) references book(bname));

insert into book values('高等数学', 32.5, 100);
insert into book values('低等数学', 30, 80);
insert into book values('组合数学', 38, 120);
insert into book values('数学分析', 44.5, 110);
insert into book values('离散数学', 16.5, 190);
insert into supplier values('供应商A', '高等数学', 20);
insert into supplier values('供应商A', '低等数学', 22);
insert into supplier values('供应商A', '组合数学', 24);
insert into supplier values('供应商A', '数学分析', 26);
insert into supplier values('供应商A', '离散数学', 28);
insert into supplier values('供应商B', '高等数学', 18);
insert into supplier values('供应商B', '低等数学', 26);
insert into supplier values('供应商B', '组合数学', 22);
insert into supplier values('供应商B', '数学分析', 20);
insert into supplier values('供应商B', '离散数学', 14);
insert into supplier values('供应商C', '高等数学', 32);
insert into supplier values('供应商C', '低等数学', 28);
insert into supplier values('供应商C', '组合数学', 16);
insert into supplier values('供应商C', '数学分析', 25);
insert into supplier values('供应商C', '离散数学', 24.5);
insert into record values('2020-12-21-00-00-00', '高等数学', 1, 32.5, 10);
insert into record values('2020-12-21-00-00-01', '低等数学', 1, 30, 10);
insert into record values('2020-12-21-00-00-02', '组合数学', 1, 38, 10);
insert into record values('2020-12-21-00-00-03', '数学分析', 1, 44.5, 10);
insert into record values('2020-12-21-00-00-04', '离散数学', 1, 16.5, 10);
insert into record values('2020-12-21-00-00-05', '高等数学', 0, 32.5, 2);
insert into record values('2020-12-21-00-00-06', '低等数学', 0, 30, 4);
insert into record values('2020-12-21-00-00-07', '组合数学', 0, 38, 3);
insert into record values('2020-12-21-00-00-08', '数学分析', 0, 44.5, 2);
insert into record values('2020-12-21-00-00-09', '离散数学', 0, 16.5, 2);
```

**统计模块注意事项：**由上面数据可知，统计的数据都在 2020 年 12 月，因此现在（2021 年 1 月或更晚）在统计模块是没有数据的。因此想查看统计结果，请选择日期为 2020 年 12 月~