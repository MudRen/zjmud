// houyuan.c �����Ӻ�Ժ

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "��Ժ");
	set("long", @LONG
���������ӵĺ�Ժ������һ����ɽ����Ȼ�������ǳ���ΰ������
һˮ�أ���ɽ���ߣ���Ȼ��Ϣ��������������֮����������Ӷ����׼
��ʳ��ĳ�����
LONG );

	set("default_long", "����ROOM_NAME�ĺ�Ժ������һ����ɽ����Ȼ��"/* EXAMPLE */
			    "�����ǳ���ΰ������һˮ�أ���ɽ���ߣ���Ȼ" /* EXAMPLE */
			    "��Ϣ��������������֮���������ǳ�����");   /* EXAMPLE */
								       /* EXAMPLE */

	set("exits", ([
		"south" : __DIR__"zhongting",
		"north" : __DIR__"huayuan",
		"east"  : __DIR__"lianwu",
		"west"  : __DIR__"chufang",
	]));

	set("outdoors", "OUTDOORS");
	set("no_sleep_room", 1);
	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
