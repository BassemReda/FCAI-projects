
--Insert Into Movies and [TYPE]
insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (1,199801,3,'Godfather',9.2,75,175);
 
insert into ADMIN
values (199801,023567,'el za3im george','1234');

insert into [TYPE]
values (11,'crime')

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (2,199801,5,'Blood diamond',8.0,55,153);

insert into [TYPE]
values (12,'advanture')

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (3,199801,4,'Intersteller',8.6,75,175);

insert into [TYPE]
values (13,'Sci-fi')

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (4,199801,4,'Fight club',8.8,90,139);

insert into [TYPE]
values (14,'Drama')

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (5,199801,12,'Exorcist',8.0,120,122);

insert into [TYPE]
values (15,'Horror')

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (6,199801,7,'Black Swan',8.0,100,108);

insert into [TYPE]
values (14,'Drama')

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (7,199801,6,'Requiem For a Dream',9.3,150,102);

insert into [TYPE]
values (14,'Drama')

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (8,199801,13,'Doctor Strange',7.5,100,115);

insert into [TYPE]
values (16,'Drama')

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (9,199801,7,'Se7en',8.6,70,127);

insert into [TYPE]
values (11,'Crime')

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (10,199801,11,'Titanic',7.8,45,205);

insert into [TYPE]
values (17,'Romance')

insert into [TYPE]
values (16,'Action')
-- Insert into KIND
insert into KIND
values (1,11);

insert into KIND
values (2,12);

insert into KIND
values (3,13);

insert into KIND
values (4,14);

insert into KIND
values (5,15);

insert into KIND
values (6,14);

insert into KIND
values (7,14);

insert into KIND
values (8,11);

insert into KIND
values (9,16);

insert into KIND
values (10,17);

--Insert Into Customers
insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(1,199801,021234,'Andrew','aaaa@email.com','12abc')

insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(2,199801,025678,'omar','bbbb@email.com','13abc')

insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(3,199801,029101,'bassem','cccc@email.com','14abc')

insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(4,199801,021121,'george','dddd@email.com','15abc')

insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(5,199801,023141,'mark','eeee@email.com','16abc')

insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(6,199801,025161,'maria','ffff@email.com','17abc')

insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(7,199801,027181,'mina','gggg@email.com','18abc')

insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(8,199801,029202,'neo','hhhh@email.com','19abc')

insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(9,199801,021222,'koko','yyyy@email.com','20abc')

insert into CUSTOMER(ssn,assn,PHONENUMBER,name,email,address)
values(10,199801,023242,'philo','xxxx@email.com','21abc')








select [name] from MOVIE m  , KIND k, [TYPE] t
where m.MID = k.MID 
AND k.TYPEID = t.TYPEID
AND t.TYPENAME = 'Drama'


--------------------------------------------------------
insert into [order] values (1,3,75)
insert into PENALTY values(1,'5/4/2018','10/4/2018','10/4/2018',0)
insert into INORDER values(3,1)

insert into [order] values (2,4,120)
insert into PENALTY values(2,'4/6/2018','4/16/2018','4/17/2018',10)
insert into INORDER values(5,2)

insert into [order] values (3,6,70)
insert into PENALTY values(3,'4/7/2018','4/9/2018','4/8/2018',0)
insert into INORDER values(9,3)

insert into [order] values (4,9,55)
insert into PENALTY values(1,'5/4/2018','5/14/2018','5/14/2018',0)
insert into INORDER values(3,4)

insert into [order] values (5,7,90)
insert into PENALTY values(5,'5/20/2018','5/29/2018','5/30/2018',10)
insert into INORDER values(4,5)


delete from MOVIE 
where MID = 12 
AND MID = 12;

insert into MOVIE(MID,ASSN,AMOUNTAVAIL,[NAME],RATE,PRICE,DURATION)
values (15,199801,7,'Black Swan',8.0,100,108);
insert into KIND values (5,(select TYPEID from TYPE where TYPENAME = 'crime' ))
update MOVIE
set AMOUNTAVAIL = 18
where MID = 1;