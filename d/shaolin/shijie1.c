// Room: /d/shaolin/shijie1.c
inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
��������ɽ��´������ɽɽ�š�һ��������ʯ����ͬ������
���Ѷ��ϣ�ֱû�ƶˡ���ɽȺ���������ɫ��ɽ�����˸������
����С֮�⡣�����м���������С���������ƺ�������������
Щʲô��
LONG );
	set("exits", ([
		"east"    : "/d/songshan/taishique",
		"west"    : __DIR__"xiaojing1",
		"northup" : __DIR__"shijie2",
	]));
	set("objects",([
		__DIR__"npc/xiao-fan" : 1,
		__DIR__"npc/tiao-fu" : 2,
	]));
	set("outdoors", "shaolin");
	setup();
}

