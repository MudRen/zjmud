//Room: xiaojia-qianyuan.c

inherit ROOM;
void create ()
{
	set ("short", "����ǰԺ");
	set ("long", @LONG
û�����!�Ǻ�!
LONG);
	set("exits", 
	([ //sizeof() == 2
		"west" : __DIR__"liande-dadao5",
		"east" : __DIR__"xiaojiadt",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/guanjia" : 1,
	]));

	set("outdoors", "changan");
	setup();
}
