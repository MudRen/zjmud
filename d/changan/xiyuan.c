//Room: xiyuan.c

inherit ROOM;

void create ()
{
	set ("short", "ϷԺ");
	set ("long", @LONG
���������İ����������˴���һ�����ɵ����е���ɫ��Ϸ̨��Ϸ̨
���߹�����յ�����ĵ�����ǰ������Щ���ʣ�������һЩ���Ͳ����Ϳ�
�������Ρ�
LONG);
	set("exits", ([
		"south" : __DIR__"liande-beikou",
	]));
	set("objects", ([
		__DIR__"npc/xizi" : 1,
	]));

	setup();
}


