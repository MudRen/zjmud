//Room: nan-chengmen.c

inherit ROOM;

void create ()
{
	set ("short", "�����ϳ���");
	set ("long", @LONG
�����ǵ��ϳ��š�����Ļ��ǺӼ������������ҳǸ�ǽ����һ��
���أ����Ī��֮�ƣ����ڻ�פ������Ӫʿ����Զ����Ӫ���࣬�����
�����ľ�����֮�ƣ�������¥��ֻ����¥�ߴ������ڱ����������ţ�ʿ
������������ȥ��Զ���Ǳ���Ҫ���书��
LONG);
	set("exits", ([ /* sizeof() == 2 */ 
		"southwest" : "/d/quanzhen/guandao1",
		"north" : __DIR__"nanan-daokou",
	]));
	set("objects", ([ //sizeof() == 3
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/guanbing": 2,
	]));

	set("outdoors", 1);
	setup();
}
