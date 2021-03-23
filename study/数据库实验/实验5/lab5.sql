create database jxgl;

use jxgl;

# 建表
create table student
(sno varchar(7),
sname varchar(5),
sage numeric(2,0),
ssex varchar(1),
sdept varchar(5),
primary key(sno));

create table course
(cno varchar(4),
cname varchar(6),
cpno varchar(4),
ccredit numeric(1,0),
primary key(cno));

create table sc
(sno varchar(7),
cno varchar(4),
grade int,
primary key(sno,cno),
foreign key(sno) references student(sno),
foreign key(cno) references course(cno));

# 加入课本数据
insert into student values('2005001','钱横',18,'男','Cs');
insert into student values('2005002','王林',19,'女','Cs');
insert into student values('2005003','李民',20,'男','Is');
insert into student values('2005004','赵欣然',16,'女','Ma');
insert into student values('2005005','刘备',25,'男','Wa');
insert into course values('1','数据库系统','5',4);
insert into course values('2','数学分析',null,2);
insert into course values('3','信息系统导论','1',3);
insert into course values('4','操作系统原理','6',3);
insert into course values('5','数据结构','7',4);
insert into course values('6','数据处理基础',null,4);
insert into course values('7','C语言','6',3);
insert into sc values('2005001','1',87);
insert into sc values('2005002','1',82);
insert into sc values('2005003','1',92);
insert into sc values('2005004','1',82);
insert into sc values('2005005','1',null);
insert into sc values('2005001','2',67);
insert into sc values('2005002','2',95);
insert into sc values('2005001','3',90);
insert into sc values('2005003','3',88);
insert into sc values('2005001','4',90);
insert into sc values('2005001','5',78);
insert into sc values('2005001','7',55);

select sno,sname 
from student 
where sage > 23 and ssex = '男';

select sname 
from student 
where ssex = '女' and sno in 
	(select sno 
	from sc);

select cno 
from course 
where cno not in 
	(select cno 
    from sc 
    where sno = '2005002');

select sno 
from sc 
group by sno 
having count(sno) >= 2;

select cno,cname 
from course 
where cno in 
	(select cno 
	from sc 
	group by cno 
    having count(sno) = 
		(select count(sno) 
        from student));

select avg(grade)
from sc
where sno in 
	(select sno
	from sc
	where cno in 
		(select cno
		from course
		where ccredit = 3)
	group by sno
	having count(cno) = 
		(select count(cno)
		from course
		where ccredit = 3));

#2
select count(cno)
from course
where cno in 
	(select cno
    from sc);
    
select avg(sage)
from student
where sno in 
	(select sno
    from sc
    where cno = 4);
    
select cno,avg(grade)
from sc
where cno in 
	(select cno
    from course
    where ccredit = 3)
group by cno;

select cno,count(sno) as c
from course natural join sc
group by cno
having count(sno) > 3
order by c desc,cno;

select sname
from student
where sno > (select sno from student where sname = '王林') and sage < (select sage from student where sname = '王林');

select sname,sage
from student
where sname like '王%';

select sno,cno
from sc
where grade is null;

select sname,sage
from student
where ssex = '男' and sage > 
	(select avg(sage)
    from student
    where ssex = '女');

select sname,sage
from student
where ssex = '男' and sage > all
	(select sage 
    from student
    where ssex = '女');
    
select sum(grade) as s
from sc
where grade >= 60
group by sno
having count(cno) > 4
order by s desc;