//Room: fangzhangshi.c

inherit ROOM;

void create ()
{
	set ("short", "������");
	set ("long", @LONG
�����Һ������أ����г���һ��ľ齺�һ������֮�⣬�پͱ�����
������Ϸ��ż������ڷ𾭵��鼮������һ���ƾɵ�ľ�㡣ľ��ϵ�
�м����޲�����������ͨ�����۱��
LONG);
	set("exits", 
	([ //sizeof() == 1
		"west" : __DIR__"baodian",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/huitong" : 1,
	]));
	
	setup();
}
