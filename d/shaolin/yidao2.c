// Room: /d/shaolin/yidao2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
һ����������Ĵ�������������������������ӵ�
���̣����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·������������һ��СԺ����˵����³��������
LONG );
	set("exits", ([
		"south" : __DIR__"yidao1",
		"north" : __DIR__"hanshui1",
		"east"  : "/d/room/xiaoyuan",
	]));
	set("outdoors", "nanyang");
	setup();
}

