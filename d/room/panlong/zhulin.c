// zhulin.c ����������

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "����");
	set("long", @LONG
�������źô�һƬ���֣��ǳ��ľ�����һ�������Ҷɳɳ���졣
LONG );

	set("default_long", "�������źô�һƬ���֣��ǳ��ľ�����һ���" /* EXAMPLE */
			    "����Ҷɳɳ���죬��ʱROOM_OWNER��ȥ���θ�" /* EXAMPLE */
			    "Ĭ�����������������书��");	       /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"west" : __DIR__"huayuan",
		"east" : __DIR__"tingtao",
	]));

	set("outdoors", "OUTDOORS");
	set("sleep_room", 1);
	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
