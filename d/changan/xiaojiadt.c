//Room: xiaojiadt.c

inherit ROOM;

void create()
{
	set("short", "���Ҵ���");
	set("long", @LONG
�����������أ����г���һ������֮�⣬���Ǽ��޼Ҿߣ����ް�
�裬ֻ��ǽ�Ϲ���һ���޴�Ĺ��ʻ�������һ����ǣ�ɽ��ˮ�ƣ�����
׺��̨ͤ¥��԰����������ǽ��ϵ�һ�����ǡ�
LONG);
	set("exits", ([ /* sizeof() == 3 */
		"west" : __DIR__"xiaojia-qianyuan",
		"north" : __DIR__"xiaojia-pianting",
		"south" : __DIR__"xiaojia-sleep"
	]));
	set("objects", ([
		__DIR__"npc/yuanwai" : 1,
	]) );

	set("NONPC",1);
	setup();
}
