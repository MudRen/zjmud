// tingtao.c ���������θ�

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "���θ�");
	set("long", @LONG
��������һ�ǵ����θ�������紵��Ҷ�������������ķǳ���
�У����������Ŀ�������ʵ����һ�������书�ĺ�ȥ����
LONG );

	set("default_long", "��������һ�ǵ����θ�������紵��Ҷ����" /* EXAMPLE */
			    "���������ķǳ����У����������Ŀ�������ʵ" /* EXAMPLE */
			    "����һ�������书�ĺ�ȥ����");	     /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"west" : __DIR__"zhulin",
	]));

	set("sleep_room", 1);
	setup();

//**    set("research_improve", 15);  //15% improved
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
