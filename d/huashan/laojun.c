// laojun.c

inherit ROOM;

void create()
{
	set("short", "�Ͼ���");
	set("long", @LONG
��������Ҫ�������£�������������ЪϢ���Ͼ�����һ������೤��
ɽ�����ഫΪ̫���Ͼ����ˣ�����·��ͨ��������ϴ���ţ�����������
��������Ϊ��ɽͨ����
LONG );
	set("exits", ([ /* sizeof() == 2 */
	    "westdown" : __DIR__"pingxinshi",
	    "southup"  : __DIR__"husun",
	]));
	set("objects", ([
	     __DIR__"npc/lao-denuo": 1,
	]));

	set("outdoors", "xx" );

	set("valid_startroom","1");
	setup();
}
 
int valid_leave(object me, string dir)
{
	object guarder;

	if (! objectp(guarder = present("lao denuo", this_object())))
		return 1;

	if (dir == "southup")
		return guarder->permit_pass(me, dir);

	return 1;
}
