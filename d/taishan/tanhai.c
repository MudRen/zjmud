// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "̽��ʯ");
	set("long", @LONG
����һ���ɽ�����ͻ���ľ�ʯ����Լ�����࣬��ֱָ������
��ʯ��������ƾ������Ұ�������������о��ߵ�ɫ���ˣ���ͨ��һ��
�������ʵ����̽��ʯ��
LONG );
	set("exits", ([
		"westdown" : __DIR__"riguan",
		"east" : __DIR__"dongtian",
	]));
	set("no_clean_up", 0);
	set("outdoors", "taishan");
	setup();
}

