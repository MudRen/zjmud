// Room: /d/shaolin/yidao4.c
inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
һ����������Ĵ�������������������������ӵ�
���̣����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·��������·����
����������������֡�
LONG );
	set("exits", ([
		"south" : __DIR__"nanyang",
		"north" : __DIR__"ruzhou",
	]));
	set("outdoors", "nanyang");
	setup();
}
