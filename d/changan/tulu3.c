// Room:/d/changan/tulu3.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
����һ�����������·������̫��·�ϼ���û�����ˣ�����
һƬ�ļš�
LONG);
	set("exits",  ([  /*  sizeof()  ==  2  */
		"northeast" : __DIR__"tulu4",
		"southdown" : __DIR__"tulu2",
	]));
	set("outdoors", "changan");
	setup();
}
