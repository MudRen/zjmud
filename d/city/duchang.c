// Room: /city/duchang.c
inherit ROOM;
void create()
{
	set("short", "�ĳ�");
	set("long", @LONG
�����Ƕĳ��Ĵ��ã����ܵķ����ﴫ����ߺ������ĶĲ�����
�����Ƕġ���С���ķ��䡣ǽ�����۴�����һ�����ӡ�
LONG );
	set("item_desc", ([
		"�����ӡ�" : "��¥�Ĺ��������ڲ��Խ׶Ρ�\n",
	]));
	set("objects", ([
		CLASS_D("shenlong")+"/pang" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"daxiao",
		"up"   : __DIR__"duchang2",
		"east" : __DIR__"nandajie1",
	]));
	setup();
}

