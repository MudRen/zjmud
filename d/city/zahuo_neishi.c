// Room: /city/zahuo-neishi.c
inherit ROOM;

void create()
{
	set("short", "�ӻ�������");
	set("long", @LONG
�����ӻ��̵����ң�����С�������һ�أ�����һЩ�ճ���Ʒ����
�ƹ�Ļ�������к��Ź������ˡ���˵˽������Ҳ��һЩ��
�صĶ�����
LONG );
	set("exits", ([
		"north" : __DIR__"zahuopu",
	]));
	set("objects", ([
		__DIR__"npc/zhushou": 1,
	]));
	setup();
}

