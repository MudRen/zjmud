// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
����һ���ųǱ����Ĵ��������壬�����г���Ѫ�ȵ�ζ������Խ��Խ���¡�����
LONG
	);
	set("exits", ([
		"north" : __DIR__"room1",
	]));
	setup();
}
