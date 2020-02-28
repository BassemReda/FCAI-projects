/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2005                    */
/* Created on:     5/4/2018 5:19:21 PM                          */
/*==============================================================*/


if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('CUSTOMER') and o.name = 'FK_CUSTOMER_SUPERVISE_ADMIN')
alter table CUSTOMER
   drop constraint FK_CUSTOMER_SUPERVISE_ADMIN
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('INORDER') and o.name = 'FK_INORDER_INORDER_MOVIE')
alter table INORDER
   drop constraint FK_INORDER_INORDER_MOVIE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('INORDER') and o.name = 'FK_INORDER_INORDER2_ORDER')
alter table INORDER
   drop constraint FK_INORDER_INORDER2_ORDER
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('KIND') and o.name = 'FK_KIND_KIND_MOVIE')
alter table KIND
   drop constraint FK_KIND_KIND_MOVIE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('KIND') and o.name = 'FK_KIND_KIND2_TYPE')
alter table KIND
   drop constraint FK_KIND_KIND2_TYPE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('MOVIE') and o.name = 'FK_MOVIE_MANAGES_ADMIN')
alter table MOVIE
   drop constraint FK_MOVIE_MANAGES_ADMIN
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('"ORDER"') and o.name = 'FK_ORDER_CANORDER_CUSTOMER')
alter table "ORDER"
   drop constraint FK_ORDER_CANORDER_CUSTOMER
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('PENALTY') and o.name = 'FK_PENALTY_CANHAVE_ORDER')
alter table PENALTY
   drop constraint FK_PENALTY_CANHAVE_ORDER
go

if exists (select 1
            from  sysobjects
           where  id = object_id('ADMIN')
            and   type = 'U')
   drop table ADMIN
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('CUSTOMER')
            and   name  = 'SUPERVISES_FK'
            and   indid > 0
            and   indid < 255)
   drop index CUSTOMER.SUPERVISES_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('CUSTOMER')
            and   type = 'U')
   drop table CUSTOMER
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('INORDER')
            and   name  = 'INORDER2_FK'
            and   indid > 0
            and   indid < 255)
   drop index INORDER.INORDER2_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('INORDER')
            and   name  = 'INORDER_FK'
            and   indid > 0
            and   indid < 255)
   drop index INORDER.INORDER_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('INORDER')
            and   type = 'U')
   drop table INORDER
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('KIND')
            and   name  = 'KIND2_FK'
            and   indid > 0
            and   indid < 255)
   drop index KIND.KIND2_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('KIND')
            and   name  = 'KIND_FK'
            and   indid > 0
            and   indid < 255)
   drop index KIND.KIND_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('KIND')
            and   type = 'U')
   drop table KIND
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('MOVIE')
            and   name  = 'MANAGES_FK'
            and   indid > 0
            and   indid < 255)
   drop index MOVIE.MANAGES_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('MOVIE')
            and   type = 'U')
   drop table MOVIE
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('"ORDER"')
            and   name  = 'CANORDER_FK'
            and   indid > 0
            and   indid < 255)
   drop index "ORDER".CANORDER_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('"ORDER"')
            and   type = 'U')
   drop table "ORDER"
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('PENALTY')
            and   name  = 'CANHAVE_FK'
            and   indid > 0
            and   indid < 255)
   drop index PENALTY.CANHAVE_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('PENALTY')
            and   type = 'U')
   drop table PENALTY
go

if exists (select 1
            from  sysobjects
           where  id = object_id('TYPE')
            and   type = 'U')
   drop table TYPE
go

/*==============================================================*/
/* Table: ADMIN                                                 */
/*==============================================================*/
create table ADMIN (
   ASSN                 int                  not null,
   PHONENUM             varchar(50)          null,
   NAME                 varchar(50)          not null,
   PASWORD              varchar(20)          not null,
   constraint PK_ADMIN primary key nonclustered (ASSN)
)
go

/*==============================================================*/
/* Table: CUSTOMER                                              */
/*==============================================================*/
create table CUSTOMER (
   SSN                  varchar(1024)        not null,
   ASSN                 int                  not null,
   PHONENUMBER          varchar(1024)        null,
   NAME                 varchar(50)          not null,
   EMAIL                varchar(100)         null,
   ADDRESS              varchar(100)         null,
   constraint PK_CUSTOMER primary key nonclustered (SSN)
)
go

/*==============================================================*/
/* Index: SUPERVISES_FK                                         */
/*==============================================================*/
create index SUPERVISES_FK on CUSTOMER (
ASSN ASC
)
go

/*==============================================================*/
/* Table: INORDER                                               */
/*==============================================================*/
create table INORDER (
   MID                  int                  not null,
   ORDERID              int                  not null,
   constraint PK_INORDER primary key (MID, ORDERID)
)
go

/*==============================================================*/
/* Index: INORDER_FK                                            */
/*==============================================================*/
create index INORDER_FK on INORDER (
MID ASC
)
go

/*==============================================================*/
/* Index: INORDER2_FK                                           */
/*==============================================================*/
create index INORDER2_FK on INORDER (
ORDERID ASC
)
go

/*==============================================================*/
/* Table: KIND                                                  */
/*==============================================================*/
create table KIND (
   MID                  int                  not null,
   TYPEID               int                  not null,
   constraint PK_KIND primary key (MID, TYPEID)
)
go

/*==============================================================*/
/* Index: KIND_FK                                               */
/*==============================================================*/
create index KIND_FK on KIND (
MID ASC
)
go

/*==============================================================*/
/* Index: KIND2_FK                                              */
/*==============================================================*/
create index KIND2_FK on KIND (
TYPEID ASC
)
go

/*==============================================================*/
/* Table: MOVIE                                                 */
/*==============================================================*/
create table MOVIE (
   MID                  int                  not null,
   ASSN                 int                  not null,
   AMOUNTAVAIL          int                  null,
   NAME                 varchar(50)          not null,
   RATE                 float                null,
   PRICE                float                null,
   DURATION             int                  null,
   constraint PK_MOVIE primary key nonclustered (MID)
)
go

/*==============================================================*/
/* Index: MANAGES_FK                                            */
/*==============================================================*/
create index MANAGES_FK on MOVIE (
ASSN ASC
)
go

/*==============================================================*/
/* Table: "ORDER"                                               */
/*==============================================================*/
create table "ORDER" (
   ORDERID              int                  not null,
   SSN                  varchar(1024)        not null,
   TOTALPRICE           int                  null,
   constraint PK_ORDER primary key nonclustered (ORDERID)
)
go

/*==============================================================*/
/* Index: CANORDER_FK                                           */
/*==============================================================*/
create index CANORDER_FK on "ORDER" (
SSN ASC
)
go

/*==============================================================*/
/* Table: PENALTY                                               */
/*==============================================================*/
create table PENALTY (
   ORDERID              int                  null,
   ORDERDATE            datetime             not null,
   RETURNDATE           datetime             not null,
   EXACTDATE            datetime             null,
   PRICE                float                not null
)
go

/*==============================================================*/
/* Index: CANHAVE_FK                                            */
/*==============================================================*/
create index CANHAVE_FK on PENALTY (
ORDERID ASC
)
go

/*==============================================================*/
/* Table: TYPE                                                  */
/*==============================================================*/
create table TYPE (
   TYPEID               int                  not null,
   TYPENAME             varchar(50)          not null,
   constraint PK_TYPE primary key nonclustered (TYPEID)
)
go

alter table CUSTOMER
   add constraint FK_CUSTOMER_SUPERVISE_ADMIN foreign key (ASSN)
      references ADMIN (ASSN)
go

alter table INORDER
   add constraint FK_INORDER_INORDER_MOVIE foreign key (MID)
      references MOVIE (MID)
go

alter table INORDER
   add constraint FK_INORDER_INORDER2_ORDER foreign key (ORDERID)
      references "ORDER" (ORDERID)
go

alter table KIND
   add constraint FK_KIND_KIND_MOVIE foreign key (MID)
      references MOVIE (MID)
go

alter table KIND
   add constraint FK_KIND_KIND2_TYPE foreign key (TYPEID)
      references TYPE (TYPEID)
go

alter table MOVIE
   add constraint FK_MOVIE_MANAGES_ADMIN foreign key (ASSN)
      references ADMIN (ASSN)
go

alter table "ORDER"
   add constraint FK_ORDER_CANORDER_CUSTOMER foreign key (SSN)
      references CUSTOMER (SSN)
go

alter table PENALTY
   add constraint FK_PENALTY_CANHAVE_ORDER foreign key (ORDERID)
      references "ORDER" (ORDERID)
go

