// Room: /d/shaolin/yidao4.c
inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵ�
���̣����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·��������·����
����������������֡�
LONG );
	set("exits", ([
		"south" : __DIR__"yidao2",
		"north" : __DIR__"taishanjiao",
	]));
	set("objects",([
		__DIR__"npc/dao-ke" : 1,
	]));
	set("outdoors", "taishan");
	setup();
}

