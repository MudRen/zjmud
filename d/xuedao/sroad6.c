// sroad6.c
inherit ROOM;
void create()
{
	set("short", "��ѩɽ��");
	set("long", @LONG
����ѩ�أ�����̹ǡ���������������ˣ���Ȼ���ܲ�ס�ˡ�
LONG );
	set("exits", ([
		"northdown" : __DIR__"sroad5",
		"westup"    : __DIR__"sroad7",
	]));
	set("outdoors", "xuedao");
	setup();
}
