//Room: jiulou.c

inherit ROOM;

void create()
{
	set("short", "����¥");
	set("long", @LONG
����¥���ܱ��ߣ��ƻϸ������Ǹ�����¥��¥�����л��ȣ�������
�����������š���������שǽƤ��������С����ɺ��ʮ�����š�¥
�����У�����һ�������ĺ��ң���������������֡�����¥������
�����ɣ������۾����鶯���ɡ�
LONG);
	set("exits", ([
		"south" : __DIR__"qixiang1",
		"up" : __DIR__"jiulou2",
	]));
	set("objects", ([
		__DIR__"npc/xiaoer2" : 1,
	]));

	setup();
}
