// Room: /d/shaolin/yidao1.c
inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
һ����������Ĵ�������������������������ӵ�
���̣����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·��������·��������������������֡�
LONG );
	set("exits", ([
		"south" : __DIR__"yidao",
		"north" : __DIR__"yidao2",
	]));
	set("outdoors", "nanyang");
	setup();
}

