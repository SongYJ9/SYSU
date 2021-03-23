# 建立数据库
create database dingbao;
use dingbao;

# 建表
create table paper
(pno varchar(6),
pna varchar(6),
ppr numeric(3,1),
primary key(pno));
create table customer
(cno varchar(4),
cna varchar(6),
adr varchar(20),
primary key(cno));
create table cp
(cno varchar(4),
pno varchar(6),
num int default (1),
primary key(cno,pno),
foreign key(cno) references customer(cno),
foreign key(pno) references paper(pno));

# 加入数据
insert into paper values('000001','人民日报',12.5);
insert into paper values('000002','解放军报',14.5);
insert into paper values('000003','光明日报',10.5);
insert into paper values('000004','青年报',11.5);
insert into paper values('000005','杨子日报',18.5);
insert into customer values('0001','李涛','无锡市解放东路123号');
insert into customer values('0002','钱金浩','无锡市人民西路234号');
insert into customer values('0003','邓杰','无锡市惠河路432号');
insert into customer values('0004','朱海红','无锡市中山东路432号');
insert into customer values('0005','李涛','无锡市中山东路532号');
insert into cp values('0001','000001',2);
insert into cp values('0001','000002',4);
insert into cp values('0001','000005',6);
insert into cp values('0002','000001',2);
insert into cp values('0002','000003',2);
insert into cp values('0002','000005',2);
insert into cp values('0003','000003',2);
insert into cp values('0003','000004',4);
insert into cp values('0004','000001',1);
insert into cp values('0004','000003',3);
insert into cp values('0004','000005',2);
insert into cp values('0005','000003',4);
insert into cp values('0005','000002',1);
insert into cp values('0005','000004',3);
insert into cp values('0005','000005',5);
insert into cp values('0005','000001',4);

# 建立视图
CREATE VIEW `C_P_N` AS
select customer.cno, customer.cna, paper.pno, paper.pna, num
from customer natural join paper natural join cp;

# 修改视图
alter view `C_P_N` AS
select customer.cno, customer.cna, paper.pno, paper.pna, num, ppr
from customer natural join paper natural join cp;

# 通过视图查询
select * from dingbao.c_p_n where pna = '人民日报';

# 通过视图更新数据
update `C_P_N` set num = 100 where cno = '0001' and pno = '000001';
update `C_P_N` set pna = '人民日报2' where pno = '000001';
# update `C_P_N` set pno = '000006' where pna = '人民日报2'; error

# 删除视图
drop view `C_P_N`;

# drop database dingbao;