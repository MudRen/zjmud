// Room:/d/changan/tulu2.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
����һ�����������·������̫������һ����į�ĸо���·
������ɢɢ�ķֲ��ż�ƬС��أ�żȻҲ�ܿ��ü�һЩ���̡�����
һƬ�Ļļš�
LONG);
	set("exits",  ([  /*  sizeof()  ==  2  */
		"northup"   : __DIR__"tulu3",
		"southwest" : __DIR__"tulu1",
	]));
	set("outdoors", "changan");
	setup();
}
