//      tulu1.c ��·
inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
����һ�������۵���·������ȴҲ��խ����ɢ�ĸ���
��¶���������̵�Ƶ������������ѩɽ������ԭ�ıؾ�֮
·��
LONG );
	set("outdoors", "xueshan");
	set("exits", ([
		"east" : __DIR__"caoyuan",
		"west" : __DIR__"tulu2",
	]));
	setup();
}

