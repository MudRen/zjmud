//Room: bei-chengmen.c

inherit ROOM;

void create ()
{
	set ("short", "����������");
	set ("long", @LONG
�����ǵı����š�����Ļ��ǺӼ������������ҳǸ�ǽ����һ��
���أ����Ī��֮�ƣ����ڻ�פ������Ӫʿ����Զ����Ӫ���࣬�����
�����ľ�����֮�ƣ�������¥��ֻ����¥�ߴ������ڱ����������ţ�ʿ
�����   
LONG);
	set("exits", ([ /* sizeof() == 2 */ 
		"north" : __DIR__"tulu1",
		"south" : __DIR__"beian-daokou",
	]));
	set("objects", ([ //sizeof() == 3
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/guanbing" :2,
	]));

	set("outdoors", 1);
	setup();
}
