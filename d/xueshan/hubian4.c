//      hubian4.c ����С·
inherit ROOM;

void create()
{
	set("short", "����С·");
	set("long", @LONG
����ʥ���ߵ�С·��·�೤��û��, ���̿�ϲ��
LONG );
	set("outdoors", "xueshan");
	set("exits", ([
		"north" : __DIR__"shanjiao",
		"south" : __DIR__"hubian3",
	]));
	setup();
}
