// xiaoyuan.c �����Ӵ�Ժ

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
	set("short", "��Ժ");	     /* EXAMPLE */
//**    set("short", "ROOM_NAME��Ժ");
	set("long", @LONG
����һ��������Ժ�䣬���Ÿ�����ľ������������͸������Ͷ�²��
Ӱ�ӡ���һ����·ͨ�����档
LONG );

	set("default_long", "����һ��������Ժ�䣬���Ÿ�����ľ��������"   /* EXAMPLE */
			    "����͸������Ͷ�²��Ӱ�ӡ�һ����·ͨ����"   /* EXAMPLE */
			    "�棬�ȵ÷ǳ�ƽ���ģ������Ǿ�������������"); /* EXAMPLE */
									 /* EXAMPLE */

	set("exits", ([
		"north"  : __DIR__"qianting",
		"out"    : "/d/room/xiaoyuan",
	]));

	set("outdoors", "OUTDOORS");
	set("no_sleep_room", 1);
	set("valid_startroom", 1);
	setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_OWNER_id", "ROOM_OWNER_ID");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
