// Room:/d/changan/tulu4.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
����һ�����������·������̫��·�ϵ�����Ҳ���࣬���
�ǵش�ƫԶ��Ե�ʣ�����û��ʲô���̡�
LONG);
	set("exits",  ([  /*  sizeof()  ==  2  */
		"northdown" : "/d/huanghe/yongdeng",
		"southwest" : __DIR__"tulu3",
	]));
	set("outdoors", "changan");
	setup();
}
