//Room: dong-chengmen.c

inherit ROOM;

void create ()
{
	set ("short", "����������");
	set ("long", @LONG
�����ǵĶ����š�����Ļ��ǺӼ������������ҳǸ�ǽ����һ��
���أ����Ī��֮�ƣ����ڻ�פ������Ӫʿ����Զ����Ӫ���࣬�����
�����ľ�����֮�ƣ�������¥��ֻ����¥�ߴ������ڱ����������ţ�ʿ
�����   
LONG);
	set("exits", ([ /* sizeof() == 2 */ 
		"east"  :  __DIR__"road4",
		"west" : __DIR__"dongan-daokou",
	]));
	set("objects", ([ //sizeof() == 3
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/guanbing" :2,
	]));

	set("outdoors", 1);
	setup();
}
