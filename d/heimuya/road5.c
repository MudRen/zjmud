// road5.c
// by Xiang

inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
������һ������·�ϡ������Ѿ������������ˣ�����һ����
������������������Ļ������£�û��һ˿���ĵ���ɫ��������
��������ˮ�����졣
LONG );
	set("outdoors", "heimuya");
	set("exits", ([
		"northeast" : "/d/huanghe/weifen",
		"south"     : __DIR__"road6",
	]));

	set("objects", ([
		__DIR__"npc/seller" : 1,
	]));
	setup();
}
