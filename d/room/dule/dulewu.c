// dulewu.c ���־�С��

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "С��");	     /* EXAMPLE */
//**    set("short", "ROOM_NAMEС��");
	set("long", @LONG
���Ӳ��󣬿����ĵط�����һ�Ŵ�������һ��������ֻ�Σ��ǳ��򵥡�
����ֻ�и��ڼ�į���˲�ס�������ּ��ӵ����ӡ�
LONG );

	set("default_long", "���Ӳ��󣬿����ĵط�����һ�Ŵ���"   /**/
			    "����һ��������ֻ�Σ��ǳ��򵥡�"     /**/
			    "����������һ������ƽ����į���ˡ�"); /**/
								 /**/
	setup();

	set("exits", ([			 /* EXAMPLE */
		"south" : __DIR__"xiaoyuan",    /* EXAMPLE */
	]));				    /* EXAMPLE */
						/* EXAMPLE */
//**    set("KEY_DOOR", ([
//**	    "exit" : "south",
//**	    "room" : __DIR__"xiaoyuan",
//**    ]));
//**
//**    set("sleep_room", 1);
//**    set("loving_room", 1);
	set("no_fight", 1);
	 set("no_clean_up",1);
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_position", "ROOM_POSITION");
}
int clean_up()
{
	return 0;
}