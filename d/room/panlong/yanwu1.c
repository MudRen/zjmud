// yanwu1.c ������������

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "������");	     /* EXAMPLE */
//**    set("short", "ROOM_NAME������");
	set("long", @LONG
���������ӵ�����������ʱ��Щ�����������ᣬ��һ�����֣���
��������������
LONG );

	set("default_long", "����ROOM_NAME������������ʱ��Щ����������"/* EXAMPLE */
			    "�ᣬ��һ�����֣�����������������" );    /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"west" : __DIR__"yishiting",
	]));

//**    set("objects", ([
//**	    "/clone/weapon/zhubang" : 1,
//**	    "/clone/weapon/zhujian" : 1,
//**	    "/clone/weapon/mudao"   : 1,
//**    ]));

	set("no_sleep_room", 1);
	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
